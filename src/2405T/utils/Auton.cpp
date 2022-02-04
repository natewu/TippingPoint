#include "main.h"
#include "2405T/utils/Auton.hpp"
#include "2405T/utils/Paths.cpp"

Slew::Slew(int max, int rate, direction dir) {
    this->max = max;
    this->rate = rate;
    this->dir = dir;

    last_input = 0;
    last_output = 0;
}

int Slew::update(int input){
    /* if(max/max*dir == 1){
        if((input > last_input) && (input < max)){
            last_output += rate;
        } 
        else if(input < last_input){
            last_output = max;
        }
    } 
    else if (max/max*dir == -1){
        if(input < last_input){
            last_output += rate;
        } 
        else if(input > last_input){
            last_output = max;
        }
    } */

    if(dir == fwd){
        if(input > last_input){
            last_output += rate;
        } 
        else if(input < last_input){
            last_output = max;
        }
    } 
    else if (dir == rev){
        if(input < last_input){
            last_output += rate;
        } 
        else if(input > last_input){
            last_output = max;
        }
    }

    return last_output;
}
//find path magnitude

//initialize the function
// Use front motor to pick up
// start PID
PID::PID(float kP, float kI, float kD, pros::Motor left, pros::Motor right) :
    left(left),
    right(right){
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;

    last_input = 0;
    last_output = 0;
    last_error = 0;
}
void PID::drive(Vector target){
    // Use left and right sensors to find the distance and then use PID to output the left and right motor powers
  
    // PID
    

}

/*
    Start of odometry code
*/

Odom::Odom(