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

    this->position.x = dist(gen);
    this->position.y = dist(gen);
    this->velocity;
    this->acceleration;

    this->scale         = SCALE;
    this->max_speed     = MAX_SPEED;
    this->max_force     = MAX_FORCE;
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

void Boid::adjustAcceleration() {
    // this->seperate();
    // this->align();
    // this->cohere();
    Vector2 noise = this->genNoise();
    Vector2 wall_avoid = this->avoidWalls();

    this->acceleration.add(noise);
    this->acceleration.add(wall_avoid);
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

Vector2 Boid::avoid(float x, float y) {
    Vector2 pos = Vector2(x, y);
    Vector2 l8rsk8rvctr = sub(this->position, pos);
    l8rsk8rvctr.norm();
    l8rsk8rvctr.div(this->vecDist(pos));
    return l8rsk8rvctr;
}

// RULES -----------------------

Vector2 Boid::cohesion(Flock flock) {
    Vector2 coh_vec = Vector2();
    for (Boid& other : flock.boids) {
        if (this->dist(other) < COH_THRESH) {
            // seek that boid, then add to coh_vec
        }
    }
    return coh_vec;
}

