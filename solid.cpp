#include "solid.h"
#include <random>
#include <iostream>


// Utility
Vector2 RandomCoords(float lower, float upper) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(lower, upper);
    return Vector2(dist(gen), dist(gen));
}

glm::vec3 RandomRGB() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> color_dist(0.0f, 1.0f);
    return glm::vec3(color_dist(gen), color_dist(gen), color_dist(gen));
}

// Solid class
Solid::Solid() {
    this->position = RandomCoords(-1.0f, 1.0f);
    this->color = glm::vec3(1.0, 1.0, 1.0);
}

Solid::Solid(float x, float y) : Solid::Solid() {
    this->position.x = x;
    this->position.y = y;

}

void Solid::update() {
    this->position.add(this->velocity);
    this->velocity.add(this->acceleration);
    this->acceleration.mult(0);
}

float Solid::dist(Solid &other) {
    return sqrt(pow(other.position.x - this->position.x, 2) + pow(other.position.y - this->position.y, 2));
}

void Solid::boundColor() {
    if (this->color[0] > 1) {
        this->color[0] = MIN_COLOR_THRESH;
    } else if (this->color[0] < MIN_COLOR_THRESH) {
        this->color[0] = 1;
    }

    if (this->color[1] > 1) {
        this->color[1] = MIN_COLOR_THRESH;
    } else if (this->color[1] < MIN_COLOR_THRESH) {
        this->color[1] = 1;
    }

    if (this->color[2] > 1) {
        this->color[2] = MIN_COLOR_THRESH;
    } else if (this->color[2] < MIN_COLOR_THRESH) {
        this->color[2] = 1;
    }
}