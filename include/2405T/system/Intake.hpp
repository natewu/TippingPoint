#include "main.h"

class Intake{
    public:

        /* 
            Constructor.
            
            @param left The left intake motor.
            @param right The right intake motor.
        */
        Intake(pros::Motor left, pros::Motor right);
        /* 
            Move the intake.
            
            @param speed The speed of the intake.
        */
        void intake(int speed);

        /* 
            Move the intake out.

            @param speed The speed of the intake.
        */
        void outtake(int speed);

        /* 
            Stop the intake.
        */
        void stop();
    private:
        pros::Motor left, right;
};