#include "boid.h"
#include "flock.h"
#include "vector.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

int main() {
    WorldState test_state = WorldState(5, 1);
    //test_state.print();

    Boid* test_boid = dynamic_cast<Boid*>(test_state.objects[0]);
    test_boid->print();

    test_state.print();

    test_boid->cohesion(test_state);

    return 0;
}