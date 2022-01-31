#include "main.h"
#include "2405T/system/Intake.hpp"

Intake::Intake(pros::Motor left, pros::Motor right) :
    left(left),
    right(right) {
    left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD) && right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void Intake::intake(int speed) {
    left.move_voltage(speed);
    right.move_voltage(speed);
}

void Intake::outtake(int speed) {
    left.move_voltage(-speed);
    right.move_voltage(-speed);
}

void Intake::stop() {
    left.move_voltage(0);
    right.move_voltage(0);
}