#include "main.h"
#include "2405T/Global.hpp"
#include "2405T/system/Chassis.hpp"
#include "2405T/system/Controls.hpp"
#include "pros/misc.h"

#include <fstream>

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	// pros::lcd::initialize();
	// pros::lcd::set_text(1, "2405T");
	// pros::lcd::register_btn1_cb(on_center_button);
	
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	// Initialize the chassis because autonomous.
	Chassis chassis(Lf, Lr, Rf, Rr);

	Task odometer(controller);
}

bool headless = false;
bool latch = false;

void toggleHeadless(Drivetrain drivetrain){
	
	if (master.get_digital(DIGITAL_Y)) {
		if(!latch){
			headless = !headless;
			latch = true;
		}
	} 
	else {
		latch = false;
	}
	
	if(headless){
		drivetrain.drive(master.get_analog(ANALOG_LEFT_Y), -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
		//set led to red
		pros::lcd::set_text(1, "Headless");
	} else {
		drivetrain.drive(-master.get_analog(ANALOG_LEFT_Y), -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
	}
}


void opcontrol() {
	// No need to initialize the chassis because driver control. Instead, initialize the Drivetrain.
	Drivetrain drivetrain(Chassis(Lf, Lr, Rf, Rr), 0.9);
	Subsystems subsystems(Lift(liftL, liftR), Intake(intakeL, intakeR), Claw(claw));
	subsystems.lift.setSpeed(127);

	master.clear();
	Task odometer(controller);

	while (true) {
		//toggle headless mode(reverse for intake)
		toggleHeadless(drivetrain);
		
		subsystems.liftControl(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1), master.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
		subsystems.clawControl(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1));

		pros::delay(20);
	}
}

