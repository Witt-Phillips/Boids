#include "boid.h"
#include <random>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// default constructor randomly generates a boid in the frame.
Boid::Boid() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    this->scale         = SCALE;
    this->max_speed     = MAX_SPEED;
    this->max_force     = MAX_FORCE;

    this->position.x = dist(gen);
    this->position.y = dist(gen);
    this->velocity.x = dist(gen);
    this->velocity.y = dist(gen);
    this->velocity.limit(this->max_speed);
    this->acceleration;
}

Boid::Boid(float x, float y) : Boid::Boid() {
    this->position.x = x;
    this->position.y = y;
}

void Boid::print() {
    cout << "PRINTING BOID ---------- Format: [x, y]" << endl;
    cout << "Position: [" << this->position.x << ", " << this->position.y << "]" << endl;
    cout << "Velocity: [" << this->velocity.x << ", " << this->velocity.y << "]" << endl;
    cout << "Acceleration: [" << this->acceleration.x << ", " << this->acceleration.y << "]" << endl;
    cout << "Angle: " << this->angle() << endl;
    cout << "Max speed: " << this->max_speed << endl;
    cout << "Max force: " << this->max_force << endl;
}

float Boid::dist(Boid &other) {
    return sqrt(pow(other.position.x - this->position.x, 2) + pow(other.position.y - this->position.y, 2));
}

float Boid::vecDist(Vector2 &other) {
    return sqrt(pow(other.x - this->position.x, 2) + pow(other.y - this->position.y, 2));
}

float Boid::angle() {
    return atan2(this->velocity.y, this->velocity.x);
}

void Boid::update() {
    // Note - acceleration is added to velocity based on info from the current timestep.
    //i.e. perception cycle is limited within each timestep

    this->velocity.add(this->acceleration);
    //cout << "Acceleration added to velocity. New velocity: [" << this->velocity.x << ", " << this->velocity.y << "]" << endl; 

    this->velocity.limit(this->max_speed);
    //cout << "Velocity limited. New velocity: [" << this->velocity.x << ", " << this->velocity.y << "]" << endl; 

    this->position.add(this->velocity);
    //cout << "Position updated. New position: [" << this->position.x << ", " << this->position.y << "]" << endl; 

    this->acceleration.mult(0);
}

void Boid::adjustAcceleration(Flock flock) {
    this->acceleration.add(this->genNoise());
    if (AV_ON) {this->acceleration.add(this->avoidWalls().mult(WALL_WEIGHT));}
    if (COH_ON) {this->acceleration.add(this->cohesion(flock).mult(COH_WEIGHT));}
    if (SEP_ON) {this->acceleration.add(this->separation(flock).mult(SEP_WEIGHT));}
    if (ALI_ON) {this->acceleration.add(this->alignment(flock).mult(ALI_WEIGHT));}
}

Vector2 Boid::genNoise() {
    // generates a small noise vector to add to acceleration
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-NOISE, NOISE);
    Vector2 noise_vec = Vector2(dist(gen), dist(gen));
    return noise_vec;
}

void Boid::draw() {
    glPushMatrix(); // Save the current transformation matrix
    
    // Place boid on screen by position
    glTranslatef(this->position.x, this->position.y, 0);

    // Rotate according to boid's direction
    glRotatef(this->angle() * 180.0 / M_PI - 90, 0, 0, 1);

    // Draw the triangle representing the boid
    glBegin(GL_TRIANGLES);
        glColor3f(0.941, 0.502, 0.502); // Set the color of the triangle
        glVertex2f(0.0, this->scale); // Top vertex
        glVertex2f(-this->scale / 2, -this->scale); // Bottom left vertex
        glVertex2f(this->scale / 2, -this->scale); // Bottom right vertex
    glEnd();
    
    glPopMatrix(); // Restore the previous transformation matrix
}

Vector2 Boid::avoidWalls() {
    
    Vector2 avoid_vec = Vector2();
    bool wall_seen = false;

    if (this->position.x > 1 - OBS_THRESH) {
        // avoid right wall
        avoid_vec.add(this->avoid(1, this->position.y));
        wall_seen = true;
    }
    
    if (this->position.x < -1 + OBS_THRESH) {
        // avoid left wall
        avoid_vec.add(this->avoid(-1, this->position.y));
        wall_seen = true;
    }
    
    if (this->position.y > 1 - OBS_THRESH) {
        // avoid top wall
        avoid_vec.add(this->avoid(this->position.x, 1));
        wall_seen = true;
    }
    
    if (this->position.y < -1 + OBS_THRESH) {
        // avoid bottom wall
        avoid_vec.add(this->avoid(this->position.x, -1));
        wall_seen = true;
    }

    // Reynolds steering
    if (wall_seen) {
        avoid_vec.norm();
        avoid_vec.mult(this->max_speed);
        avoid_vec.sub(this->velocity);
        avoid_vec.limit(this->max_force);
    }

    return avoid_vec;
}

// returns steer away from point
Vector2 Boid::avoid(float x, float y) {
    Vector2 pos = Vector2(x, y);
    Vector2 l8rsk8rvctr = sub(this->position, pos);
    l8rsk8rvctr.norm();
    l8rsk8rvctr.div(this->vecDist(pos));
    return l8rsk8rvctr;
}

// returns steer towards point
Vector2 Boid::seek(float x, float y) {
    Vector2 pos = Vector2(x, y);
    Vector2 to_target = sub(pos, this->position);
    to_target.norm();
    to_target.mult(this->max_speed);

    //we now have a scaled vector pointing towards the target, so can calculate steer (to be added to acceleration)
    to_target.sub(this->velocity);
    to_target.limit(this->max_force);
    return to_target;
}

// RULES -----------------------

// first calculates average position of close but not too-close boids, then gets steering vector to it
Vector2 Boid::cohesion(Flock flock) {
    Vector2 avg_pos = Vector2();
    int count = 0;
    for (Boid& other : flock.boids) {
        float dist = this->dist(other);
        // include > SEP_THRESH CLAUSE?
        if ((dist > 0) && (dist < COH_THRESH)) {
            // seek that boid, then add to coh_vec
            avg_pos.add(other.position);
            count++;
        }
    }

    // returns vector to be added to acceleration based on seeking other boids
    if (count > 0) {
        avg_pos.div(count);
        return this->seek(avg_pos.x, avg_pos.y);
    } else {
        return Vector2();
    }
}

Vector2 Boid::separation(Flock flock) {
    Vector2 sep_vec = Vector2();
    int count = 0;
    for (Boid& other : flock.boids) {
        float dist = this->dist(other);
        // include > SEP_THRESH CLAUSE?
        if ((dist > 0) && (dist < COH_THRESH)) {
            // seek that boid, then add to coh_vec
            sep_vec.add(this->avoid(other.position.x, other.position.y));
            count++;
        }
    }

    // returns vector to be added to acceleration based on seeking other boids
    if (count > 0) {
        sep_vec.div(count);
    }

    if (sep_vec.mag() > 0) {
        sep_vec.norm();
        sep_vec.mult(max_speed);
        sep_vec.sub(this->velocity);
        sep_vec.limit(this->max_force);
        return sep_vec;
    } else {
        return Vector2();
    }
}

Vector2 Boid::alignment(Flock flock) {
    Vector2 align_vec = Vector2();
    bool aligning = false;
    for (Boid& other : flock.boids) {
        float dist = this->dist(other);
        // include > SEP_THRESH CLAUSE?
        if ((dist > 0) && (dist < COH_THRESH)) {
            // seek that boid, then add to coh_vec
            align_vec.add(other.velocity);
            aligning = true;
        }
    }

    // returns vector to be added to acceleration based on seeking other boids
    if (aligning) {
        return this->seek(align_vec.x, align_vec.y);
    } else {
        return Vector2();
    }
}

void Boid::handleEdges(){
    if (this->position.x > 1.1) {
        this->position.x = -1.1;
    } else if (this->position.x < -1.1) {
        this->position.x = 1.1;
    }

    if (this->position.y > 1.1) {
        this->position.y = -1.1;
    } else if (this->position.y < -1.1) {
        this->position.y = 1.1;
    }
}

