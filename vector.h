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

    void print();

    void add(Vector2 &other);

    void sub(Vector2 &other);

    void mult(float scaling_factor);

    void div(float scaling_factor);

    // divide x, y by magnitude
    void norm();

    // if magnitude > max_mag, scales down s.t. this->mag == max_mag
    void limit(float max_mag);

    float mag();
};

/*
Ways to create a vector:

1. Vector2 my_vec;
This will create a vector, my_vec, with values x = 0, y = 0.

2. Vector2 my_vec(some_x, some_y)
my_vec: x = some_x, y = some_y

*/