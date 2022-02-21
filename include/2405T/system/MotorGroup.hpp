#pragma once
#include "main.h"
#include "pros/motors.hpp"

class MotorGroup{
    public:
        /*  
            Constructor for the MotorGroup class.

            @param motor1 The first motor in the group.
            @param motor2 The second motor in the group.
        */
        MotorGroup();
        MotorGroup(pros::Motor motor1, pros::Motor motor2);

        // Return the first motor in the group
        pros::Motor getMotor1();
        // Return the second motor in the group
        pros::Motor getMotor2();
        
        //Copy all the functions from the pros::Motor class for the motor group
        MotorGroup& move(int velocity);
        MotorGroup& move_absolute(int position, int velocity);
        MotorGroup& move_relative(int delta_position, int velocity);
        MotorGroup& move_velocity(int velocity);
        MotorGroup& move_voltage(int voltage);
        MotorGroup& tare_position();
        MotorGroup& set_brake_mode(pros::motor_brake_mode_e mode);
        MotorGroup& set_encoder_units(pros::motor_encoder_units_e_t units);
        MotorGroup& set_gearing(pros::motor_gearset_e gearset);
        MotorGroup& set_reversed(bool reverse);
        MotorGroup& set_zero_position(int position);
        MotorGroup& set_voltage_limit(int limit);
        MotorGroup& set_current_limit(int limit);

    private:
        pros::Motor motor1, motor2;
};