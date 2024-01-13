#include "flock.h"
#include "boid.h"
#include "obstacle.h"

// ---------- Transition to WorldState model

void WorldState::genBoid() {
    this->objects.push_back(new Boid());
    this->num_boids++;
    this->num_total++;
}

void WorldState::addBoid(Boid* other) {
    this->objects.push_back(other);
    this->num_boids++;
    this->num_total++;
}

void WorldState::genObstacle() {
    this->objects.push_back(new Obstacle());
    this->num_boids++;
    this->num_total++;
}

void WorldState::addObstacle(Obstacle* other) {
    this->objects.push_back(other);
    this->num_boids++;
    this->num_total++;
}

// Init WorldState with (num boids, num obstacles)

WorldState::WorldState(size_t nboids, size_t nobstacles) {
    for (size_t i = 0; i < nboids; i++) {
        this->genBoid();
    }

    for (size_t i = 0; i < nobstacles; i++) {
        this->genObstacle();
    }
}

WorldState::~WorldState() {
    for (Solid* solid : this->objects) {
        delete solid;
        solid = nullptr;
    }
}

void WorldState::timestep() {
    //for each boid: calculate new position based on all boids, update position, draw
    for (Solid* solid : this->objects) {
        if (solid->type == boid) {
            Boid* boid = dynamic_cast<Boid*>(solid);
            boid->handleEdges();
            boid->adjustAcceleration(*this);
            boid->adjustColor(*this);
            boid->update();
            boid->draw();
        }
        
    }
}

void WorldState::print() {
    for (Solid* object : this->objects) {
        object->print();
    }
}



