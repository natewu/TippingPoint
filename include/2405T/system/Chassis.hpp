#pragma once
#include "main.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "2405T/system/MotorGroup.hpp"
#include "2405T/utils/Paths.hpp"

class Chassis{
    public:
        Chassis();

        /* 
            Constructor for the Chassis class. 
        */
        Chassis(pros::Motor leftFront, pros::Motor leftRear, pros::Motor rightFront, pros::Motor rightRear);

        /* 
            Constructor for a 6 motor configured chassis.

            @param leftFront The left front motor.
            @param leftRear The left rear motor group.
            @param rightFront The right front motor.
            @param rightRear The right rear motor group.
        */
        Chassis(pros::Motor leftFront, MotorGroup leftRear, pros::Motor rightFront, MotorGroup rightRear);

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

        std::optional<MotorGroup> leftRearGroup,
                                    rightRearGroup;
};

//Combine two pros::Motor objects into one pros::Motor object
pros::Motor operator+(pros::Motor master, pros::Motor slave);

// Infinitely scalable chassis
class VectorChassis{
    // Macro to iterate through all motors
    #define ITERATELEFT(command) for(int i = 0; i < leftVector.size(); i++) {leftVector.at(i).command;}
    #define ITERATERIGHT(command) for(int i = 0; i < rightVector.size(); i++) {rightVector.at(i).command;}
    
    public:
        VectorChassis();

        /* 
            Default 4 motor configuration.

            @param leftFront The left front motor.
            @param leftRear The left rear motor.
            @param rightFront The right front motor.
            @param rightRear The right rear motor.
        */
        VectorChassis(pros::Motor leftFront, pros::Motor leftRear, pros::Motor rightFront, pros::Motor rightRear);

        /* 
            6 motor configuration.

            @param leftFront The left front motor.
            @param leftRear The left rear motor.
            @param rightFront The right front motor.
            @param rightRear The right rear motor.
        */
        VectorChassis(pros::Motor leftFront, pros::Motor leftRear, pros::Motor rightFront, pros::Motor rightRear, pros::Motor leftRear1, pros::Motor rightRear1);

        /* 
            Add motor groups

            @param left The left member of the motor group.
            @param right The right member of the motor group.
        */
        VectorChassis& addMotors(pros::Motor left, pros::Motor right);

        /*
            Move all motors at a given speed.

            @param left The speed of the left side of the chassis.
            @param right The speed of the right side of the chassis. 
        */
        VectorChassis& move(int left, int right);

        /*
            Move all motors at a given speed.

            @param drive The speed of the drive motors.
            @param turn The speed of the turn motors.
            @param turnSensitivity The sensitivity of the turn motors.
            @param strafe The speed of the strafing motors.
        */
        VectorChassis& opDrive(int drive, int turn, double turnSensitivity = 1, int strafe = 0);

        /*  
            Move to a given position.

            @param point The position to move to.
            @param speed The speed to move at.
            @param slew The slew rate of the chassis.
            @param reverse Whether to reverse the motors.
        */
        VectorChassis& driveTo(Vector point, int speed, int slew, bool reverse = false);

        /* 
            Stop the chassis.
        */
        VectorChassis& stop();

        /*
            Set brake mode.

            @param mode The mode to set the brake mode to. 
        */
        VectorChassis& setBrakeMode(pros::motor_brake_mode_e mode);

        private:
            std::vector<pros::Motor> leftVector,
                                    rightVector;
};