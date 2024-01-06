#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

// Header file for vector classes
class Vector2 {
public:
    // Parameters
    float x;
    float y;
    
    // Constructors
    Vector2();
    Vector2(float x, float y);
    
    // Methods

    // returns magnitude
    float mag();

    void print();

    void add(Vector2 other);

    void sub(Vector2 other);

    Vector2 mult(float scaling_factor);

    Vector2 div(float scaling_factor);

    // divide x, y by magnitude
    void norm();

    // if magnitude > max_mag, scales down s.t. this->mag == max_mag
    void limit(float max_mag);

};

// Generalized
Vector2 add(Vector2 vec1, Vector2 vec2);

Vector2 sub(Vector2 vec1, Vector2 vec2);

#endif

/*
Ways to create a vector:

1. Vector2 my_vec;
This will create a vector, my_vec, with values x = 0, y = 0.

2. Vector2 my_vec(some_x, some_y)
my_vec: x = some_x, y = some_y

*/