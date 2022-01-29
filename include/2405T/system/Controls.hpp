#pragma once
#include "main.h"
#include "2405T/system/Chassis.hpp"
#include "2405T/system/Lift.hpp"
#include "2405T/system/Intake.hpp"
#include "2405T/system/Claw.hpp"

class Drivetrain{
    public: 
        /* 
            Constructor.

            @param chassis The chassis to use.
            @param turnSensitivity The sensitivity of the turn.
        */
        Drivetrain(Chassis chassis, float turnSensitivity = 1);

        /* 
            Drive controls.

            @param driveAxis The 3 axis.
            @param turnAxis The 1 axis.
            @param strafe The strafe joystick (if using strafe).
        */
        void drive(int driveAxis, int turnAxis, int strafeAxis = 0);

    private:
        Chassis chassis;
        float turnSensitivity;
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
        void liftControl(int up, int down);

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
        void clawControl(int clawToggle)
        

    private:
        
};