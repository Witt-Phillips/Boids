#include "vector.h"
#include <iostream>
using namespace std;

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

void Vector2::print() {
    cout << "x: " << this->x << ", y: " << this->y << endl;
}

void Vector2::add(Vector2 &other) {
    this->x += other.x;
    this->y += other.y;
}