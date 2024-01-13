#ifndef BOID_H
#define BOID_H

#include "vector.h"
#include "flock.h"
#include "solid.h"
#include <math.h>
#include <glm/glm.hpp>

#define FLOCK_SIZE 50
#define SCALE 0.03
#define MAX_SPEED 0.0015
#define MAX_FORCE 0.0000045
#define NOISE 0.00000005
#define OBS_THRESH 0.1
#define COH_THRESH 0.15
#define SEP_THRESH 0.1

#define MAX_COLOR_FORCE 0.007

#define COH_WEIGHT 1.2
#define SEP_WEIGHT 1.7
#define ALI_WEIGHT 1

#define NOISE_ON false
#define COH_ON true
#define SEP_ON true
#define ALI_ON true

#define OFF_SCREEN_RANDOMIZE true

class Boid : public Solid {
public:
    // Boid settings
    float scale;
    float max_speed;
    float max_force;
    float max_color_force = MAX_COLOR_FORCE;

    // Constructors
    Boid();
    Boid(float x, float y);
    
    // BASIC INFO
    void print();

    // returns angle of direction calculated from velocity
    float angle();

    // combines all rules & some noise to calculate acceleration
    void adjustAcceleration(WorldState state);

    // returns vector generated from avoidance of point x, y
    Vector2 avoid(float x, float y);

    Vector2 seek(float x, float y);

    // outputs boid to display
    void draw() override;

    // respawns boid on opposite end of screen if boundary overrun
    void handleEdges();

    // coordinates color by averaging with nearby group mates (with some optional noise)
    void colorCoord(WorldState state);

    // test to always increase color by 1
    void colorNoise();

    //Central color control
    void adjustColor(WorldState state);

    // Rules: all return Vector2 representing contribution to final direction
    Vector2 cohesion(WorldState state);
    Vector2 separation(WorldState state);
    Vector2 alignment(WorldState state);
};

#endif