#include "boid.h"
#include <random>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

// default constructor randomly generates a boid in the frame.
Boid::Boid() : Solid::Solid() {
    this->type          = boid;
    this->scale         = SCALE;
    this->max_speed     = MAX_SPEED;
    this->max_force     = MAX_FORCE;

    this->velocity = RandomCoords(-1.0f, 1.0f).limit(this->max_speed);
    this->color = RandomRGB();
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

float Boid::angle() {
    return atan2(this->velocity.y, this->velocity.x);
}

void Boid::adjustAcceleration(WorldState state) {
    if (NOISE_ON) {this->acceleration.add(RandomCoords(-NOISE, NOISE));}
    if (COH_ON) {this->acceleration.add(this->cohesion(state).mult(COH_WEIGHT));}
    if (SEP_ON) {this->acceleration.add(this->separation(state).mult(SEP_WEIGHT));}
    if (ALI_ON) {this->acceleration.add(this->alignment(state).mult(ALI_WEIGHT));}
}

void Boid::draw() {
    glPushMatrix(); // Save the current transformation matrix
    
    // Place boid on screen by position
    glTranslatef(this->position.x, this->position.y, 0);

    // Rotate according to boid's direction
    glRotatef(this->angle() * 180.0 / M_PI - 90, 0, 0, 1);

    // Draw the triangle representing the boid
    glBegin(GL_TRIANGLES);
        glColor3f(this->color[0], this->color[1], this->color[2]); // Set the color of the triangle
        glVertex2f(0.0, this->scale); // Top vertex
        glVertex2f(-this->scale / 2, -this->scale); // Bottom left vertex
        glVertex2f(this->scale / 2, -this->scale); // Bottom right vertex
    glEnd();
    
    glPopMatrix(); // Restore the previous transformation matrix
}

// returns steer away from point
// Write over for objects!!
/* Vector2 Boid::avoid(float x, float y) {
    Vector2 pos = Vector2(x, y);
    Vector2 l8rsk8rvctr = sub(this->position, pos);
    l8rsk8rvctr.norm();
    l8rsk8rvctr.div(this->vecDist(pos));
    return l8rsk8rvctr;
} */

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
Vector2 Boid::cohesion(WorldState state) {
    Vector2 steer = Vector2();
    int count = 0;
    
    for (Solid* solid : state.objects) {
        if (solid->type == boid) {
            Boid* boid = dynamic_cast<Boid*>(solid);
            float dist = this->dist(*boid);
            // include > SEP_THRESH CLAUSE?
            if ((dist > 0) && (dist < COH_THRESH)) {
                // seek that boid, then add to coh_vec
                steer.add(boid->position);
                count++;
            }
    }
    }
    
    // returns vector to be added to acceleration based on seeking other boids
    if (count > 0) {
        steer.div(count);
        // get vector *to* avg_pos - steer was previously avg pos
        steer.sub(this->position);
        steer.norm();
        steer.mult(this->max_speed);
        steer.sub(this->velocity);
        steer.limit(this->max_force);
    }

    return steer;
}

Vector2 Boid::separation(WorldState state) {
    Vector2 steer = Vector2();
    int count = 0;
    for (Solid* solid : state.objects) {
        if (solid->type == boid) {
        Boid* boid = dynamic_cast<Boid*>(solid);

        float dist = this->dist(*boid);
        // include > SEP_THRESH CLAUSE?
        if ((dist > 0) && (dist < COH_THRESH)) {
            // seek that boid, then add to coh_vec
            Vector2 diff = sub(this->position, boid->position);
            diff.div(dist);
            steer.add(diff);
            //sep_vec.add(this->avoid(other.position.x, other.position.y));
            count++;
        }
    }
    }

    // returns vector to be added to acceleration based on seeking other boids
    if (count > 0) {
        steer.div(count);
        steer.norm();
        steer.mult(this->max_speed);
        steer.sub(this->velocity);
        steer.limit(this->max_force);
    }

   return steer;
}

Vector2 Boid::alignment(WorldState state) {
    Vector2 align_vec = Vector2();
    int count = 0;
    for (Solid* solid : state.objects) {
        if (solid->type == boid) {
        Boid* boid = dynamic_cast<Boid*>(solid);

        float dist = this->dist(*boid);
        // include > SEP_THRESH CLAUSE?
        if ((dist > 0) && (dist < COH_THRESH)) {
            // seek that boid, then add to coh_vec
            align_vec.add(boid->velocity);
            count++;
        }
    }
    }

    // returns vector to be added to acceleration based on seeking other boids
    if (count > 0) {
        align_vec.div(count);
        align_vec.norm();
        align_vec.mult(this->max_speed);
        align_vec.sub(this->velocity);
        align_vec.limit(this->max_force);
    }

    return align_vec;
}

void Boid::handleEdges(){
    bool went_off = false;
    
    if (this->position.x > 1.1) {
        this->position.x = -1.1;
        went_off = true;
    } else if (this->position.x < -1.1) {
        this->position.x = 1.1;
        went_off = true;
    }

    if (this->position.y > 1.1) {
        this->position.y = -1.1;
        went_off = true;
    } else if (this->position.y < -1.1) {
        this->position.y = 1.1;
        went_off = true;
    }

    if (went_off && OFF_SCREEN_RANDOMIZE) {
        this->color = RandomRGB();
    }
}

// Color shifting

void Boid::colorCoord(WorldState state) {
    glm::vec3 average_color(0.0f, 0.0f, 0.0f);
    int count = 0;

    for (Solid* solid : state.objects) {
        if (solid->type == boid) {
        Boid* boid = dynamic_cast<Boid*>(solid);

        float dist = this->dist(*boid);
        if ((dist > 0) && (dist < COH_THRESH)) {
            average_color += boid->color;
            count++;
        }
    }
    }

    if (count > 0) {
        average_color /= count;
        this->color = glm::mix(this->color, average_color, MAX_COLOR_FORCE);
    }
}

void Boid::colorNoise() {
    glm::vec3 color_noise = RandomRGB();
    this->color = glm::mix(this->color, color_noise, 0.05);
}

void Boid::adjustColor(WorldState state) {
    this->colorCoord(state);
    //this->colorNoise();
}

