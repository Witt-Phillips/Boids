#include "boid.h"
#include "flock.h"
#include "vector.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

int main() {
    /* Boid test_boid;
    test_boid.acceleration.x = 0;
    test_boid.acceleration.y = 0;
    test_boid.print();

    test_boid.update();
    test_boid.print(); */

    Flock test_flock = Flock(5);
    test_flock.print();
    return 0;
}