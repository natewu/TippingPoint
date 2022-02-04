#pragma once
#include "main.h"
#include "pros/motors.hpp"
#include "2405T/utils/Paths.hpp"

class Chassis{
    public:
        Chassis();

        /* 
            Constructor for the Chassis class. 
        */
        Chassis(pros::Motor leftFront, pros::Motor leftRear, pros::Motor rightFront, pros::Motor rightRear);

        /* 
            Moves the chassis at a given speed on each side.
            
            @param left The speed of the left side of the chassis.
            @param right The speed of the right side of the chassis.
            @param x (optional) The speed of strafing.
         */ 
        Chassis& move(int left, int right, int x = 0);

        /* 
            Drive the chassis as an operator.
         */
        Chassis& opDrive(int drive, int turn, double turnSensitivity = 1, int strafe = 0);

        /* 
            Drive the chassis as autonomous.

            Starts task to move the chassis.
         */
        Chassis& drive();

        /* 
            Drives the chassis to a given position.
            
            @param point The position to drive to.
            @param speed The speed to drive at.
            @param slew The slew rate of the chassis.
            @param reverse Whether to reverse the motors.
        */
        Chassis& driveTo(Vector point, int speed, int slew, bool reverse = false);

        /* 
            Stop the chassis.
        */
        Chassis& stop();

        /* 
            Get the average left position.
        */
        int getLeft();

        /* 
            Get the average right position.
        */
        int getRight();

    private:
        pros::Motor leftFront, 
                    rightFront, 
                    leftRear, 
                    rightRear;
};