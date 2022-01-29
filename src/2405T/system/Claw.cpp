#include "main.h"
#include "2405T/system/Claw.hpp"

Claw::Claw(pros::ADIDigitalOut claw) :
    storedClaw(claw) {
        
    }
void Claw::actuate() {

}

bool Claw::getStatus() {
    return state;
}