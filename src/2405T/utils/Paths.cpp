#include "main.h"
#include "2405T/utils/Paths.hpp"
#include <cmath>

Vector::Vector(float x, float y) {
    this->storedX = x;
    this->storedY = y;
}

float Vector::x() {
    return storedX;
}

float Vector::y() {
    return storedY;
}

float Vector::magnitude(){
    return sqrt(pow(storedX, 2) + pow(storedY, 2));
}

float Vector::angle(){
    return atan2(storedY, storedX);
}

Vector& Vector::normalize(){
    float mag = magnitude();
    storedX /= mag;
    storedY /= mag;
    return *this;
}

Vector& Vector::rotate(float angle){
    float x = storedX * cos(angle) - storedY * sin(angle);
    float y = storedX * sin(angle) + storedY * cos(angle);
    storedX = x;
    storedY = y;
    return *this;
}

Vector& Vector::add(Vector v){
    storedX += v.x();
    storedY += v.y();
    return *this;
}

Vector& Vector::subtract(Vector v){
    storedX -= v.x();
    storedY -= v.y();
    return *this;
}

Vector& Vector::multiply(float scalar){
    storedX *= scalar;
    storedY *= scalar;
    return *this;
}

Vector& Vector::divide(float scalar){
    storedX /= scalar;
    storedY /= scalar;
    return *this;
}

Bezier::Bezier(Vector start, Vector end, Vector control) :
    startPoint(start),
    endPoint(end),
    controlPoint(control) {

}

Vector Bezier::start() {
    return startPoint;
}

Vector Bezier::end() {
    return endPoint;
}

Vector Bezier::control() {
    return controlPoint;
}

float Bezier::length() {
    return startPoint.magnitude() + endPoint.magnitude() + controlPoint.magnitude();
}

Vector Bezier::point(float distance){
    float startMag = startPoint.magnitude();
    float endMag = endPoint.magnitude();
    float controlMag = controlPoint.magnitude();
    float totalMag = startMag + endMag + controlMag;
    float percent = distance / totalMag;
    float x = startPoint.x() * percent + controlPoint.x() * (1 - percent) + endPoint.x() * percent;
    float y = startPoint.y() * percent + controlPoint.y() * (1 - percent) + endPoint.y() * percent;
    return Vector(x, y);
}

Vector Bezier::derivative(float distance){
    float startMag = startPoint.magnitude();
    float endMag = endPoint.magnitude();
    float controlMag = controlPoint.magnitude();
    float totalMag = startMag + endMag + controlMag;
    float percent = distance / totalMag;
    float x = startPoint.x() * (1 - percent) + controlPoint.x() * (percent) + endPoint.x() * (1 - percent);
    float y = startPoint.y() * (1 - percent) + controlPoint.y() * (percent) + endPoint.y() * (1 - percent);
    return Vector(x, y);
}

Vector Bezier::secondDerivative(float distance){
    float startMag = startPoint.magnitude();
    float endMag = endPoint.magnitude();
    float controlMag = controlPoint.magnitude();
    float totalMag = startMag + endMag + controlMag;
    float percent = distance / totalMag;
    float x = startPoint.x() * (1 - percent) + controlPoint.x() * (2 * percent) + endPoint.x() * (1 - percent);
    float y = startPoint.y() * (1 - percent) + controlPoint.y() * (2 * percent) + endPoint.y() * (1 - percent);
    return Vector(x, y);
}

Vector Bezier::integral(float distance){
    float startMag = startPoint.magnitude();
    float endMag = endPoint.magnitude();
    float controlMag = controlPoint.magnitude();
    float totalMag = startMag + endMag + controlMag;
    float percent = distance / totalMag;
    float x = startPoint.x() * percent + controlPoint.x() * (percent * percent) + endPoint.x() * (percent * percent);
    float y = startPoint.y() * percent + controlPoint.y() * (percent * percent) + endPoint.y() * (percent * percent);
    return Vector(x, y);
}