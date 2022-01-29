#pragma once
#include "main.h"

class Claw {
    public:
        bool latch = false;

        /* 
            Constructor.
            
            @param piston The piston to use as the claw.
        */
        Claw(pros::ADIDigitalOut piston);
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
        pros::ADIDigitalOut claw;
};
