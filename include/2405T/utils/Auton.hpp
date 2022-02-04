#pragma once
#include "main.h"
#include "2405T/system/Chassis.hpp"
#include "2405T/utils/Misc.hpp"
#include "2405T/utils/Paths.hpp"

class Slew {
    public:
        /* 
            Constructor.
            
            @param max The maximum speed of the slew.
            @param rate The rate of acceleration.
        */
        Slew(int max, int rate = 1, direction dir = fwd);

        /* 
            Update the slew.
            
            @param input The input to the slew.
        */
        int update(int input);

    private:
        int max;
        int rate;
        int dir;
        int last_input;
        int last_output;
};

class PID{
    public:
        /* 
            Constructor.
            
            @param kP The proportional constant.
            @param kI The integral constant.
            @param kD The derivative constant.
            @param max The maximum output.
            @param min The minimum output.
        */
        PID(float kP, float kI, float kD, pros::Motor left, pros:: Motor right);

        /* 
            Update the PID.
            
            @param input The input to the PID.
        */
        int update(int input);
        void drive(Vector target);

    private:
        float kP;
        float kI;
        float kD;
        int last_input;
        int last_output;
        int last_error;
        pros::Motor left;
        pros::Motor right;
};

class Odom{
    public:
        /* 
            Constructor.
            
            @param left The left encoder.
            @param right The right encoder.
        */
        Odom(Chassis chassis);

        /* 
            Update the odometry.
        */
        void update();

        /* 
            Returns the current position of the robot.
        */
        Vector position();

        /* 
            Returns the current heading of the robot.
        */
        float heading();

        /* 
            Returns the current velocity of the robot.
        */
        Vector velocity();

        /* 
            Returns the current acceleration of the robot.
        */
        Vector acceleration();

        /* 
            Returns the current angular velocity of the robot.
        */
        float angularVelocity();

        /* 
            Returns the current angular acceleration of the robot.
        */
        float angularAcceleration();

    private:
        Chassis chassis;
        Vector last_position;
        float last_heading;
        Vector last_velocity;
        Vector last_acceleration;
        float last_angular_velocity;
        float last_angular_acceleration;
};