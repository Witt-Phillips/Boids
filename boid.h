#include "vector.h"
#include <math.h>

#define SCALE 0.05
#define MAX_SPEED 0.0004
#define MAX_FORCE 0.0000004
#define NOISE 0.000003f
#define OBS_THRESH 0.25

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

    // SIMULATION

    // updates position by current velocity, velocity by current acceleration, and sets acceleration to 0.
    // (Represents advancing one timestep in the simulation.)
    void update();

    // combines all rules & some noise to calculate acceleration
    void adjustAcceleration();

    // based on NOISE macro, adds some amount of randomness to acceleration.
    Vector2 genNoise();

    Vector2 avoidWalls();

    Vector2 avoid(float x, float y);

    // GRAPHICS

    void draw();
};