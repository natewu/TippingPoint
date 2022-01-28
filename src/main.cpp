#include "main.h"
#include "2405T/Global.hpp"
#include "2405T/system/Chassis.hpp"
#include "2405T/system/Controls.hpp"

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

void opcontrol() {
	// No need to initialize the chassis because driver control. Instead, initialize the Drivetrain.
	Drivetrain drivetrain(Chassis(Lf, Lr, Rf, Rr), 0.9);

	master.clear();
	Task odometer(controller);
	
	while (true) {
		drivetrain.drive(master.get_analog(ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

		pros::delay(20);
	}
}
