#include "main.h"
#include "2405T/system/Controls.hpp"

/* 
    Drivetrain section
*/
Drivetrain::Drivetrain(Chassis chassis, float turnSensitivity) : chassis(chassis) {
    this->turnSensitivity = turnSensitivity;
}
//Controller drivetrain
void Drivetrain::drive(int driveAxis, int turnAxis, int strafeAxis) {
    chassis.opDrive(driveAxis, turnAxis, turnSensitivity, strafeAxis);
}

/* 
    Subsystems section
*/
Subsystems::Subsystems(Lift lift, Intake intake, Claw claw) : lift(lift), intake(intake), claw(claw) {
}
void Subsystems::liftControl(int up, int down){
    //TODO: add lift control mechanism stop points
    //what do you mean by stop points
    //what are we doing, what are we programming
    //move forbar up
    double rotations = lift.getPosition();
    double maxRotations = 3600;
    
    std::cout << "rotations: " << rotations << std::endl;
    //Check if the lift is at the top or bottom, prevent it from going past the top or bottom
    if(up && rotations < maxRotations){
        if(rotations > maxRotations*0.85){
            lift.setSpeed(50);
        }
        lift.move(fwd);
    }
    else if(down && rotations > 0){
        if(rotations < maxRotations*0.3){
            lift.setSpeed(50);
        }
        lift.move(rev);
    }
    else{
        lift.setSpeed(127);
        lift.stop();
    }
    /* 
    if(up){
        lift.move(fwd);
    }
    //move forbar down
    else if(down){
        lift.move(rev);
    }
    //stop forbar from moving
    else{
        lift.stop();
    } */
}
void Subsystems::clawControl()