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
    cout << "x: " << this->x << ", y: " << this->y << ", mag: " << this->mag()  << endl;
}

float Vector2::mag() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

void Vector2::add(Vector2 other) {
    this->x += other.x;
    this->y += other.y;
}

void Vector2::sub(Vector2 other) {
    this->x -= other.x;
    this->y -= other.y;
}

void Vector2::mult(float scaling_factor) {
    this->x *= scaling_factor;
    this->y *= scaling_factor;
}

void Vector2::div(float scaling_factor) {
    this->x /= scaling_factor;
    this->y /= scaling_factor;
}

void Vector2::norm() {
    if (this->mag() != 0) {
        this->div(this->mag());
    }
}

void Vector2::limit(float max_mag) {
    if (this->mag() == 0) {return;}

    float scaling_factor = min(max_mag, this->mag()) / this->mag();
    this->mult(scaling_factor);
}

// Generalized vector math

Vector2 add(Vector2 vec1, Vector2 vec2) {
    Vector2 sum = Vector2(vec1.x + vec2.x, vec1.y + vec2.y);
    return sum;
}

Vector2 sub(Vector2 vec1, Vector2 vec2) {
    Vector2 diff = Vector2(vec1.x - vec2.x, vec1.y - vec2.y);
    return diff;
}