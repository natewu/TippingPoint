#include "main.h"
#include "2405T/system/Controls.hpp"

Drivetrain::Drivetrain(Chassis chassis, float turnSensitivity) : chassis(chassis) {
    this->turnSensitivity = turnSensitivity;
}

void Drivetrain::drive(int driveAxis, int turnAxis, int strafeAxis) {
    chassis.opDrive(driveAxis, turnAxis, turnSensitivity, strafeAxis);
}