#include "obstacle.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

Obstacle::Obstacle() : Solid::Solid() {
    this->type = obstacle;
    this->radius = 1;
}

void Obstacle::draw() {
    glPushMatrix(); // Save the current transformation matrix
    
    // Place boid on screen by position
    glTranslatef(this->position.x, this->position.y, 0);

    // Rotate according to boid's direction
    //glRotatef(this->angle() * 180.0 / M_PI - 90, 0, 0, 1);

    // Draw the circle representing the obstacle
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(this->color[0], this->color[1], this->color[2]); // Set the color of the triangle
    glVertex2f(this->position.x, this->position.y); // Center of the circle
    //32 here is the number of segments used to draw the circle
    int segments = 32;
    for(int i = 0; i <= segments; i++) {
        GLfloat angle = 2.0f * M_PI * float(i) / float(segments); // Angle in radians
        glVertex2f(this->position.x + cos(angle) * this->radius, this->position.y + sin(angle) * radius);
    }

    glEnd();
    
    glPopMatrix(); // Restore the previous transformation matrix
}

void Obstacle::print() {
    cout << "PRINTING Obstacle ---------- Format: [x, y]" << endl;
    cout << "Position: [" << this->position.x << ", " << this->position.y << "]" << endl;
    cout << "Radius: " << this->radius << endl;
}