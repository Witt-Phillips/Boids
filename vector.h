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

};

/*
Ways to create a vector:

1. Vector2 my_vec;
This will create a vector, my_vec, with values x = 0, y = 0.

2. Vector2 my_vec(some_x, some_y)
my_vec: x = some_x, y = some_y

*/