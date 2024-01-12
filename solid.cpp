#include "solid.h"
#include <random>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    this->velocity = Vector2();
    this->acceleration = Vector2();
    this->color = glm::vec3(1.0, 1.0, 1.0);
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

/* void obstacle::draw() {
    glPushMatrix(); // Save the current transformation matrix
    
    // Place boid on screen by position
    glTranslatef(this->position.x, this->position.y, 0);

    // Rotate according to boid's direction
    //glRotatef(this->angle() * 180.0 / M_PI - 90, 0, 0, 1);

    // Draw the triangle representing the boid
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(this->color[0], this->color[1], this->color[2]); // Set the color of the triangle
    glVertex2f(this->position.x, this->position.y); // Center of the circle
    //32 here is the number of segments used to draw the circle
    int segments = 32;
    for(int i = 0; i <= segments; i++) {
        GLfloat angle = 2.0f * M_PI * float(i) / float(segments); // Angle in radians
        glVertex2f(this->position.x + cos(angle) * radius, this->position.y + sin(angle) * radius);
    }

    glEnd();
    
    glPopMatrix(); // Restore the previous transformation matrix
} */