#include "boid.h"
#include <random>
#include <iostream>

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

    this->view_radius   = VIEW_RADIUS;
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
}

float Boid::dist(Boid &other) {
        return sqrt(pow(other.position.x - this->position.x, 2) + pow(other.position.y - this->position.y, 2));
}

float Boid::angle() {
    return atan2(this->velocity.y, this->velocity.x);
}

