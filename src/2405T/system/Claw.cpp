#include "main.h"
#include "2405T/system/Claw.hpp"

Claw::Claw(pros::ADIDigitalOut claw) :
    claw(claw) {
    claw.set_value(0);
}

void Claw::actuate(){
    if(state){
        claw.set_value(0);
        state = !state;
    }
    else{
        claw.set_value(1);
        state = !state;
    }
}

void Claw::reset(){
    claw.set_value(0);
    state = false;
}

bool Claw::getStatus(){
    return state;
}