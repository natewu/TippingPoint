#pragma once
#include "main.h"
#include "2405T/utils/Misc.hpp"
#include "pros/motors.hpp"

class Lift {
    public:
        Lift(pros::Motor left, pros::Motor right);
        
        /* 
            Move the lift.

            @param dir The direction, fwd or rev
        */
        void move(direction dir = fwd);
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

        /* 
            Sets default speed

            @param speed The speed of the lift.
        */
        void setSpeed(int speed);

        /* 
            Gets the current position of the lift.
        */
        double getPosition();

    private:
        double position;
        int speed;
        pros::Motor left, right;
};