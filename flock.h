#ifndef FLOCK_H
#define FLOCK_H

#include "vector.h"
#include "solid.h"
#include <vector>

class Boid;
class Obstacle;

class WorldState {
public:
    std::vector<Solid*> objects;
    int num_boids;
    int num_obstacles;
    int num_food;
    int num_total;

    WorldState();
    WorldState(size_t nboids, size_t nobstacles);
    ~WorldState();

    void genBoid();
    void addBoid(Boid* other);

    void genObstacle();
    void addObstacle(Obstacle* other);

    void print();

    void timestep();
};

#endif