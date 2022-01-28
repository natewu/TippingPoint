#include "main.h"
#include "2405T/system/Intake.hpp"

Intake::Intake(pros::Motor left, pros::Motor right) :
    left(left),
    right(right) {
    left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD) && right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}