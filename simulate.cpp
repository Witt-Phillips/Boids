//#include "boid.h"
#include "vector.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

int main() {
    cout << "Compiling!" << endl;
    Vector2 testVec = Vector2(3, 4);
    testVec.print();
    testVec.norm();
    testVec.print();
    return 0;
}