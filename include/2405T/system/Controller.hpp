#pragma once
#include "main.h"

namespace lib{
    class Controller{
        public:
            /* 
                Constructor

                @param controller The controller to use. 
            */
            Controller(pros::Controller controller);

            /*
                Controller display.

                @param headless The headless status.
                @param pistonState The piston status.

            */
            void display(
                bool headless = false,
                bool pistonState = false
            );
        private:
            pros::Controller controller;
    };
}
