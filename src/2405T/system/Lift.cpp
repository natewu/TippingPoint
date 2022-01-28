#include "main.h"
#include "2405T/system/Lift.hpp"
#include "pros/motors.hpp"

// Constructor sets target motor
Lift::Lift(pros::Motor left, pros::Motor right) : 
    left(left), 
    right(right) {
    // Set the lift to the bottom position
    reset();
}

void Lift::move(int speed, double target) {
    // Set target position
    left.move_absolute(target, speed);
    right.move_absolute(target, speed);
}

void Lift::reset(){
    left.tare_position() && right.tare_position();
}

void Lift::stop(){
    left.move_velocity(0) && right.move_velocity(0);
}