#ifndef OBJECTS_H
#define OBJECTS_H

#include "vector.h"
#include <glm/glm.hpp>

#define MIN_COLOR_THRESH 0.5

// Utility
Vector2 RandomCoords(float lower, float upper);

glm::vec3 RandomRGB();

// Solid Class
enum solid_type {
    boid,
    obstacle,
    food
};

class Solid {
public:
    // Positional
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    //Descriptive
    glm::vec3 color;
    solid_type type;

    //Methods
    Solid();
    Solid(float x, float y);
    virtual ~Solid() {};

    virtual void draw() = 0; //output object to screen

    virtual void print() = 0; // print solid information
    
    void update(); // update positional information based on velocity and acceleration

    float dist(Solid &other); // returns the distance from one solid to another

    void boundColor();
};

#endif