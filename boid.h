#include "vector.h"
#include <math.h>

#define VIEW_RADIUS 2;
#define MAX_SPEED 10;
#define MAX_FORCE 20;

class Boid {
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    // Boid settings
    float view_radius;
    float max_speed;
    float max_force;

    // Constructors
    Boid();
    Boid(float x, float y);
    
    //METHODS
    void print();

    // returns Euclidean distance from this boid to other boid
    float dist(Boid &other);

    // returns angle of direction calculated from velocity
    float angle();
};