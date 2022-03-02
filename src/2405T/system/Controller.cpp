#include "main.h"
#include "2405T/system/Controller.hpp"
#include "2405T/Global.hpp"

lib::Controller::Controller(pros::Controller controller) : controller(controller) {
}

void lib::Controller::display(bool headless, bool pistonState) {
    int grabs = 20;
    
    while(1){
        
        //Increment grabs if pistonState is changed
        if(pistonState){
            grabs--;
        }


        int totalSeconds = millis() / 1000.0;
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        controller.print(0,0, "%02i:%02i", minutes, seconds);
        delay(55);
        controller.print(0,10, "Bot: %02.0f%%", battery::get_capacity()); 
        delay(55);
        controller.print(1,0, "Headless: %s", headless ? "Rev" : "Fwd");
        delay(55);
        master.print(1,10, "Grabs: %d", grabs); 
        delay(55);
        // master.print(2,2, "%0.2f°C", liftL.get_temperature()); 
        delay(55);
        // master.print(2,14, "%0.2f°C", liftR.get_temperature()); 
        delay(55);
    }
}