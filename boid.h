#ifndef BOID_H
#define BOID_H

#include "vector.h"
#include "flock.h"
#include <math.h>
#include <glm/glm.hpp>
//#include <glm/gtc/normalize.hpp> // glm::normalize

#define FLOCK_SIZE 50
#define SCALE 0.03
#define MAX_SPEED 0.0015
#define MAX_FORCE 0.0000045
#define NOISE 0.00000005
#define OBS_THRESH 0.1
#define COH_THRESH 0.15
#define SEP_THRESH 0.1

#define MAX_COLOR_FORCE 0.007
#define MIN_COLOR_THRESH 0.5

#define COH_WEIGHT 1.2
#define SEP_WEIGHT 1.7
#define ALI_WEIGHT 1
#define WALL_WEIGHT 2

#define NOISE_ON false
#define COH_ON true
#define SEP_ON true
#define ALI_ON true
#define AV_ON false

#define OFF_SCREEN_RANDOMIZE true


class Boid {
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    // Boid settings
    float scale;
    float max_speed;
    float max_force;

    //Color info:
    glm::vec3 color;
    float max_color_force = MAX_COLOR_FORCE;

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
    void adjustAcceleration(Flock flock);

    // returns vector generated from avoidance of point x, y
    Vector2 avoid(float x, float y);

    Vector2 seek(float x, float y);

    // outputs boid to display
    void draw();

    // respawns boid on opposite end of screen if boundary overrun
    void handleEdges();

    // coordinates color by averaging with nearby group mates (with some optional noise)
    void colorCoord(Flock flock);

    // bounds the color values to protect valid drawing
    void boundColor();

    // test to always increase color by 1
    void colorNoise();

    //Central color control
    void adjustColor(Flock flock);

    // Rules: all return Vector2 representing contribution to final direction
    Vector2 cohesion(Flock flock);
    Vector2 separation(Flock flock);
    Vector2 alignment(Flock flock);
    Vector2 genNoise();
    Vector2 avoidWalls();
};

#endif