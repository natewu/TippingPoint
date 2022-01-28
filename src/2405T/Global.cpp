#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "okapi/api.hpp"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>

// Ports
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor Lf(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS),
    Rf(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS),
    Lr(3, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS),
    Rr(4, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS),
    liftL(7, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS),
    liftR(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS),
    intakeL(9, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS),
    intakeR(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//units
float pi = M_PI;
float tics = Lf.get_position(); 
float ticksPerInch = 900/(4*pi);
float inch = tics/ticksPerInch;
bool toggle = false, latch = false, Rlatch = true;

std::shared_ptr<okapi::OdomChassisController> drive = 
    okapi::ChassisControllerBuilder()
    .withMotors(1, 2, 4, 3) // left motor is 1, right motor is 2 (reversed)
    .withGains(
        {0.00082, 0, 0.00008}, // distance controller gains
        {0.00089, 0, 0.00005}, // turn controller gains
        {0.00035, 0, 0.00009}  // angle controller gains (helps drive straight)
    )
    .withSensors(
        okapi::ADIEncoder{'A', 'B'}, // left encoder in ADI ports A & B
        okapi::ADIEncoder{'C', 'D'},  // right encoder in ADI ports C & D (reversed)
		okapi::ADIEncoder{'E', 'F'}  // middle encoder in ADI ports E & F
    )
    // green gearset, tracking wheel diameter (2.75 in), track (7 in), and TPR (360)
    .withDimensions(okapi::AbstractMotor::gearset::green, {{2.75_in, 14_in, 1_in, 2.75_in}, okapi::quadEncoderTPR})
    .withOdometry()
    .buildOdometry();

int checkSign(int val) {
    return (0.0 < val) - (val < 0.0);
}

void motorSpeed(){
    while (1){
        master.print(0,0, "%d", master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
    }
}

void controller(){
    while(1){
        float tics = Lf.get_encoder_units(); 
        float ticksPerInch = 360/(2.75*pi);
        float inch = tics/ticksPerInch;
        int totalSeconds = millis() / 1000.0;
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        master.print(0,0, "%02i:%02i", minutes, seconds);
        delay(55);
        master.print(0,10, "Bot: %02.0f%%", battery::get_capacity()); 
        delay(55);
        master.print(1,0, "L: %0.2fNm", liftL.get_torque()); 
        delay(55);
        master.print(1,10, "R: %0.2fNm", liftR.get_torque()); 
        delay(55);
        master.print(2,2, "%0.2f°C", liftL.get_temperature()); 
        delay(55);
        master.print(2,14, "%0.2f°C", liftR.get_temperature()); 
        delay(55);
    }
}