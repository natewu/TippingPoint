#include "main.h"
#include "pros/misc.h"
#include "2405T/Global.hpp"
#include "2405T/system/Chassis.hpp"
#include "2405T/system/Controls.hpp"
#include "2405T/utils/Auton.hpp"

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
	// Task odometer(controller);
	Subsystems subsystems(Lift(liftL, liftR), Intake(intakeL, intakeR), Claw(claw));

	//driver
	drive->okapi::OdomChassisController::setState({0_ft, 0_ft, 0_deg});
	drive->driveToPoint({10.5_ft, 0_ft});
	subsystems.claw.actuate();
	drive->driveToPoint({0_ft, 0_ft}, true);
	// progSkills(subsystems);
};

void opcontrol() {
	// No need to initialize the chassis because driver control. Instead, initialize the Drivetrain.
	Drivetrain drivetrain(Chassis(Lf, Lr, Rf, Rr), 0.95);
	Subsystems subsystems(Lift(liftL, liftR), Intake(intakeL, intakeR), Claw(claw));
	subsystems.lift.setSpeed(127);

	auto controller = [&](){
		int grabs = 40;
		bool clawStateLatch = false;
		
		while(1){
			//Increment grabs if pistonState is changed
			if(subsystems.claw.getStatus() && !clawStateLatch){
				if(grabs > 0){
					grabs--;
				}
				else{
					grabs = 0;
				}

				clawStateLatch = true;
			}
			else if(!subsystems.claw.getStatus() && clawStateLatch){
				clawStateLatch = false;
			}


			int totalSeconds = millis() / 1000.0;
			int minutes = totalSeconds / 60;
			int seconds = totalSeconds % 60;
			master.print(0, 0, "%02i:%02i", minutes, seconds);
			delay(55);
			master.print(0, 10, "Bot: %02.0f%%", battery::get_capacity()); 
			delay(55);
			master.print(1, 0, "Headless: %s", drivetrain.getHeadless() ? "Rev" : "Fwd");
			delay(55);
			master.print(2, 0, "Grabs: %02.0d", grabs); 
			delay(55);
			// master.print(2,2, "%0.2f°C", liftL.get_temperature()); 
			delay(55);
			// master.print(2,14, "%0.2f°C", liftR.get_temperature()); 
			delay(55);
    	}
	};


	master.clear();
	Task odometer(controller);

	while (true) {
		//toggle headless mode(reverse for intake)
		// 
		drivetrain.headlessDrive(
			master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 
			master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 
			master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT), 
			master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)
		);
		//What button do u want it to be pressed on?

		subsystems.liftControl(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1), master.get_digital(pros::E_CONTROLLER_DIGITAL_L2), master.get_digital(pros::E_CONTROLLER_DIGITAL_B), master.get_digital(pros::E_CONTROLLER_DIGITAL_A));
		subsystems.liftControl(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1), master.get_digital(pros::E_CONTROLLER_DIGITAL_L2), master.get_digital(pros::E_CONTROLLER_DIGITAL_B), master.get_digital(pros::E_CONTROLLER_DIGITAL_A));
		subsystems.clawControl(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1));
		subsystems.intakeControl(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2), master.get_digital(pros::E_CONTROLLER_DIGITAL_X));

		pros::delay(20);
	}
}

