#include "flock.h"
#include "boid.h"


void Flock::genBoid() {
    this->boids.push_back(Boid());
    this->size++;
}

void Flock::addBoid(Boid &other) {
    this->boids.push_back(other);
    this->size++;
}

Flock::Flock() {
    // std vector initializes by default
}

Flock::Flock(size_t size) {
    for (size_t i = 0; i < size; i++) {
        this->genBoid();
    }
}

void Flock::print() {
    for (size_t i = 0; i < size; i++) {
        this->boids[i].print();
    }
}

void Flock::timestep() {
    //for each boid: calculate new position based on all boids, update position, draw
    for (Boid& boid : this->boids) {
        boid.handleEdges();
        boid.adjustAcceleration(*this);
        boid.adjustColor(*this);
        boid.update();
        boid.draw();
    }
}