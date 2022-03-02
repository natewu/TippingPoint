#pragma once
#include "main.h"
#include "2405T/system/Chassis.hpp"
#include "2405T/system/Lift.hpp"
#include "2405T/system/Intake.hpp"
#include "2405T/system/Claw.hpp"

template<typename ChassisType>

class Drivetrain{
    public: 
        /* 
            Constructor.

            @param chassis The chassis to use.
            @param turnSensitivity The sensitivity of the turn.
        */
        Drivetrain(ChassisType chassisType, float turnSensitivity = 1){
            chassis(chassisType);
            this->turnSensitivity = turnSensitivity;
        }

        /* 
            Drive controls.

            @param driveAxis The 3 axis.
            @param turnAxis The 1 axis.
            @param strafe The strafe joystick (if using strafe).
        */
        void drive(int driveAxis, int turnAxis, int strafeAxis = 0){
            chassis.opDrive(driveAxis, turnAxis, turnSensitivity, strafeAxis);
        }

        /* 
            Use headless operation.

            @param driveAxis The drive axis.
            @param turnAxis The turn axis.
            @param strafeAxis The strafe joystick (if using strafe).
            @param toggleOn The button to toggle headless. 
            @param toggleOff The button to toggle off headless.
        */
        void headlessDrive(int driveAxis, int turnAxis, int toggleOn, int toggleOff, int strafeAxis = 0){
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
            Get headless status.
        */
        bool getHeadless(){
            return headless;
        }

    private:
        ChassisType chassis;

        float turnSensitivity;
        bool headless = false, headlessLatch = false;
};

class Subsystems{
    public:
        Lift lift;
        Intake intake;
        Claw claw;
        /* 
            Constructor.

            @param lift The lift to use.
            @param intake The intake to use.
            @param claw The claw to use.
        */
        Subsystems(Lift lift, Intake intake, Claw claw);

        /* 
            Update the subsystems.
        */
        void update();

        /* 
            Lift controls

            @param up The up button.
            @param down The down button.
        */
        void liftControl(int up, int down, int reset, int unlock);

        /* 
            Intake controls

            @param intake The intake button.
            @param outtake The outtake button.
        */
        void intakeControl(int intake, int outtake);

        /* 
            Claw controls

            @param clawState 
         */
        void clawControl(int clawToggle);
        

    private:
        bool intakeToggle = false;
        bool intakeLatch = false;
};