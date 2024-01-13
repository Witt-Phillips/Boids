#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "solid.h"

class Obstacle : public Solid {
public:
    float radius;
    Obstacle();

    void draw() override;
    void print() override;
};

#endif

// New loop system
/* Flock will become a WorldState array, and the for loops in the behaviors will discriminate based on type.
 We will have a new "avoidObstacle" behavior that factors in the position of obstacles to avoid (separate from the inherent flocking behavior)*/