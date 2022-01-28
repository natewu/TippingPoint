#include "main.h"
#pragma once
#include "pros/motors.hpp"

class Lift {
    public:
        Lift(pros::Motor left, pros::Motor right);
        
        /* 
            Moves the lift to a given point at a given speed.
            
            @param speed The speed of the lift.
            @param target The target position of the lift.
        */
        void move(int speed, double target);
        /* 
            Recalibrates the lift to zero at set position.
        */
        void reset();
        /* 
            Stops the lift.
        */
        void stop();

    private:
        double position();
        pros::Motor left;
        pros::Motor right;
};