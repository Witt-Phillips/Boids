#ifndef FLOCK_H
#define FLOCK_H

#include "boid.h"
#include <vector>

class Flock {
public:
    std::vector<Boid> boids;
    size_t size = 0;

    Flock();

    Flock(size_t size);

    void genBoid();

    void addBoid(Boid &other);

    void print();

    void timestep();
};

#endif