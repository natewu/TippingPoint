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
//Headless drivetrain
void Drivetrain::headlessDrive(int driveAxis, int turnAxis, int toggleOn, int toggleOff, int strafeAxis){
    if(toggleOn && !headlessLatch){
        headless = true;
        headlessLatch = false;
    }
    else if(toggleOff && !headlessLatch){
        headless = false;
        headlessLatch = true;
    }
	else {
		headlessLatch = false;
	}
	
	if(headless){
		drive(driveAxis, -turnAxis, -strafeAxis);

		pros::lcd::set_text(1, "Headless");
	} 
    else {
		drive(-driveAxis, -turnAxis, strafeAxis);
	}
}


/* 
    Subsystems section
*/
Subsystems::Subsystems(Lift lift, Intake intake, Claw claw) : lift(lift), intake(intake), claw(claw) {
}

void Subsystems::liftControl(int up, int down){
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
}
//TODO: should probably change int to boolean
void Subsystems::clawControl(int clawToggle){
    if(clawToggle){
        if(!claw.latch){
            claw.latch = true;
            claw.actuate();
        }
    }
    else{
        claw.latch = false;
    }
}