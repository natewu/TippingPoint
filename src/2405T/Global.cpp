#include "Global.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "okapi/api.hpp"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>

// Ports
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor
    //Front Left
    Lf(20, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS),
    //Front Right
    Rf(15, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS),
    //Rear Left (mid)
    Lr(19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS),
    //Rear Right (mid)
    Rr(16, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS),
    //Rear Left (end)
    Lr1(18, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS),
    //Rear Right (end)
    Rr1(17, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS),
    //Left Lift
    liftL(14, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_COUNTS),
    //Right Lift
    liftR(10, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS),

    /* redundant */
    //Intake Left
    intakeL(1, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS),
    //Intake Right
    intakeR(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS)
    ;
pros::ADIDigitalOut claw('A'), rearClaw('B');

//units
float pi = M_PI;
float tics = Lf.get_position(); 
float ticksPerInch = 900/(4*pi);
float inch = tics/ticksPerInch;
// bool toggle = false, latch = false, Rlatch = true;
okapi::MotorGroup rightGroup({-15, -16, -17});
okapi::MotorGroup leftGroup({-20, -19, -18});

std::shared_ptr<okapi::OdomChassisController> drive = 
    okapi::ChassisControllerBuilder()
    .withMotors(leftGroup, rightGroup) // left motor is 1, right motor is 2 (reversed)
    .withGains(
        {0.00180, 0, 0.000126}, // distance controller gains
        {0.00090, 0, 0.00005}, // turn controller gains
        {0.00033, 0, 0.00005}  // angle controller gains (helps drive straight)
    )
    // .withSensors(
    //     okapi::ADIEncoder{'A', 'B'}, // left encoder in ADI ports A & B
    //     okapi::ADIEncoder{'C', 'D'},  // right encoder in ADI ports C & D (reversed)
	// 	okapi::ADIEncoder{'E', 'F'}  // middle encoder in ADI ports E & F
    // )
    // green gearset, tracking wheel diameter (2.75 in), track (7 in), and TPR (360)
    .withDimensions(okapi::AbstractMotor::gearset::green, {{4_in, 14_in}, okapi::quadEncoderTPR})
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

/* void controller(){
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
        // master.print(1,0, "L: %0.2fNm", liftL.get_torque());
        delay(55);
        // master.print(1,10, "R: %0.2fNm", liftR.get_torque()); 
        delay(55);
        // master.print(2,2, "%0.2f°C", liftL.get_temperature()); 
        delay(55);
        // master.print(2,14, "%0.2f°C", liftR.get_temperature()); 
        delay(55);
    }
} */
//skills auton
void progSkills(Subsystems subsystems){
    float ratio = 1.75;
    float angleRatio = 3.25;
    // every 1.75ft is 1 ft IRL for the ratio
	// subsystems.claw.actuate();
    drive->okapi::OdomChassisController::setState({0_ft, 0_ft, 0_deg});
	drive->driveToPoint({2.5_ft*ratio, 0_ft});
	subsystems.claw.actuate();
    drive->turnToAngle(90_deg*angleRatio);
    drive->okapi::OdomChassisController::setState({0_ft, 0_ft, 0_deg});
	drive->driveToPoint({4_ft, 0_ft});

}