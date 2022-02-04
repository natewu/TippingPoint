#include "main.h"
#include "2405T/utils/Auton.hpp"

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

Odom::Odom(Chassis chassis) :
    chassis(chassis),
    last_position(0,0),
    last_velocity(0,0),
    last_acceleration(0,0){
}

void Odom::update(){
    // Update the position, velocity, and acceleration
    Vector position = this->position();
    Vector velocity = this->velocity();
    Vector acceleration = this->acceleration();

    // Update the last position, velocity, and acceleration
    this->last_position = position;
    this->last_velocity = velocity;
    this->last_acceleration = acceleration;
}

Vector Odom::position(){
    // Get the position of the robot
    int left_pos = this->chassis.getLeft();
    int right_pos = this->chassis.getRight();

    // Calculate the position of the robot
    float x = (left_pos + right_pos) / 2.0;
    float y = (left_pos - right_pos) / 2.0;

    // Return the position of the robot
    return Vector(x, y);
}

float Odom::heading(){
    // Get the position of the robot
    Vector position = this->position();

    // Calculate the heading of the robot
    float heading = atan2(position.y(), position.x());

    // Return the heading of the robot
    return heading;
}

Vector Odom::velocity(){
    // Get the position of the robot
    Vector position = this->position();

    // Calculate the velocity of the robot
    Vector velocity = (position.subtract(this->last_position)).divide(0.02);

    // Return the velocity of the robot
    return velocity;
}

Vector Odom::acceleration(){
    // Get the velocity of the robot
    Vector velocity = this->velocity();

    // Calculate the acceleration of the robot
    Vector acceleration = (velocity.subtract(this->last_velocity)).divide(0.02);

    // Return the acceleration of the robot
    return acceleration;
}

float Odom::angularVelocity(){
    // Calculate the angular velocity of the robot
    float angular_velocity = (this->heading() - this->last_heading) / 0.02;

    // Return the angular velocity of the robot
    return angular_velocity;
}

float Odom::angularAcceleration(){
    // Calculate the angular acceleration of the robot
    float anglular_velocity = (this->heading() - this->last_heading) / 0.02;
    
    // Calcualte the derivative of the angular velocity
    float angular_acceleration = (anglular_velocity - this->last_angular_velocity) / 0.02;

    // Return the angular acceleration of the robot
    return angular_acceleration;
}