#include "main.h"
#include "2405T/system/Lift.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

// Constructor sets target motor
Lift::Lift(pros::Motor left, pros::Motor right) : 
    left(left), 
    right(right) {
    // Set the lift to the bottom position
    reset();
    left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD) && right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void Lift::move(direction dir) {
    left.move_velocity(dir*speed);
    right.move_velocity(dir*speed);
}
void Lift::move(int speed, double target) {
    // Set target position
    left.move_absolute(target, speed);
    right.move_absolute(target, speed);
}

void Lift::reset(){
    left.tare_position() && right.tare_position();
    left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD) && right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void Lift::unlock(){
    left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST) && right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void Lift::stop(){
    left.move_velocity(0) && right.move_velocity(0);
}

void Lift::setSpeed(int speed){
    this->speed = speed;
}

double Lift::getPosition(){
    return (left.get_position() + right.get_position())/2;
}