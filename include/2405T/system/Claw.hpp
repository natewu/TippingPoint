#pragma once
#include "main.h"

class Claw {
    public:
        Claw(pros::ADIDigitalOut claw);
        /* 
            Actuate the claw.        
        */
        void actuate();
        /*
            Resets the piston to a unextended position.
        */
        void reset();
        /* 
            returns the actuation status (true or false)
         */
        bool getStatus();

    private:
        bool state = false;
        pros::ADIDigitalOut storedClaw;
};
