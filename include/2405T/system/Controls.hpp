#pragma once
#include "main.h"
#include "2405T/system/Chassis.hpp"

class Drivetrain{
    public: 
        /* 
            Constructor.

            @param chassis The chassis to use.
            @param turnSensitivity The sensitivity of the turn.
        */
        Drivetrain(Chassis chassis, float turnSensitivity = 1);

        /* 
            Drive controls.

            @param left The left joystick.
            @param right The right joystick.
            @param strafe The strafe joystick (if using strafe).
        */
        void drive(int driveAxis, int turnAxis, int strafeAxis = 0);

    private:
        Chassis chassis;
        float turnSensitivity;
};