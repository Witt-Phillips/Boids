#ifndef BOID_H
#define BOID_H

#include "vector.h"
#include "flock.h"
#include <math.h>

#define SCALE 0.05
#define MAX_SPEED 0.0004
#define MAX_FORCE 0.0000004
#define NOISE 0.000001f
#define OBS_THRESH 0.25
#define COH_THRESH 0.3

class Boid {
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    // Boid settings
    float scale;
    float max_speed;
    float max_force;

    // Constructors
    Boid();
    Boid(float x, float y);
    
    // BASIC INFO
    void print();

    // returns Euclidean distance from this boid to other boid
    float dist(Boid &other);

    float vecDist(Vector2 &other);

    // returns angle of direction calculated from velocity
    float angle();

    // updates position by current velocity, velocity by current acceleration, and sets acceleration to 0.
    void update();

    // combines all rules & some noise to calculate acceleration
    void adjustAcceleration();

    // returns vector generated from avoidance of point x, y
    Vector2 avoid(float x, float y);

    // outputs boid to display
    void draw();

    // Rules: all return Vector2 representing contribution to final direction
    Vector2 cohesion(Flock flock);
    Vector2 separation(Flock flock);
    Vector2 alignment(Flock flock);
    Vector2 genNoise();
    Vector2 avoidWalls();
};

#endif