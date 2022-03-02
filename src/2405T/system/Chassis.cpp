#include "2405T/utils/Paths.hpp"
#include "main.h"
#include "2405T/Global.hpp"
#include "2405T/system/Chassis.hpp"
#include "2405T/system/MotorGroup.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

Chassis::Chassis(pros::Motor leftFront, pros::Motor leftRear, pros::Motor rightFront, pros::Motor rightRear) :
    leftFront(leftFront),
    leftRear(leftRear),
    rightFront(rightFront),
    rightRear(rightRear){
}

Chassis::Chassis(pros::Motor leftFront, MotorGroup leftRear, pros::Motor rightFront, MotorGroup rightRear) :
    leftFront(leftFront),
    leftRearGroup(leftRear),
    rightFront(rightFront),
    rightRearGroup(rightRear),
    leftRear(leftRear.getMotor1()),
    rightRear(rightRear.getMotor1()) {
}

Chassis& Chassis::move(int left, int right, int x) {
    leftFront.move_voltage(left+x);
    rightFront.move_voltage(right-x);
    leftRear.move_voltage(left-x);
    rightRear.move_voltage(right+x);

    return *this;
}

Chassis& Chassis::opDrive(int drive, int turn, double turnSensitivity, int strafe) {
    if(abs(drive) < 10 ) drive = 0;
    if(abs(turn) < 10 ) turn = 0;
    if(abs(strafe) < 10 ) strafe = 0;

    int left = drive + turn * turnSensitivity;
    int right = drive - turn * turnSensitivity;

    int leftSign = checkSign(left);
    int rightSign = checkSign(right);
    int xSign = checkSign(strafe);

    int remapLeft = (pow(left,2)*.75)*leftSign;
    int remapRight = (pow(right,2)*.75)*rightSign;
    int quadX = (pow(strafe,2)*.75)*xSign;

    move(remapLeft, remapRight, quadX);
    return *this;
}

Chassis& Chassis::drive() {
    /* under construction */
    return *this;
}

Chassis& Chassis::driveTo(Vector point, int speed, int slew, bool reverse) {
    /* under construction */
    return *this;
}

Chassis& Chassis::stop() {
    move(0,0);
    return *this;
}

int Chassis::getLeft() {
    return (leftFront.get_position() + leftRear.get_position()) / 2;
}

int Chassis::getRight() {
    return (rightFront.get_position() + rightRear.get_position()) / 2;
}

//Combine two pros::Motor objects into one pros::Motor object so that the both motors can be used as one
// not actually sure if this works
pros::Motor operator+(pros::Motor master, pros::Motor slave) {
    return master + slave;
}

//Vector Chassis
VectorChassis::VectorChassis(pros::Motor leftFront, pros::Motor leftRear, pros::Motor rightFront, pros::Motor rightRear) {
    addMotors(leftFront, rightFront);
    addMotors(leftRear, rightRear);
}

//Vector Chassis 6 motor
VectorChassis::VectorChassis(pros::Motor leftFront, pros::Motor leftRear, pros::Motor rightFront, pros::Motor rightRear, pros::Motor leftRear1, pros::Motor rightRear1) {
    addMotors(leftFront, rightFront);
    addMotors(leftRear, rightRear);
    addMotors(leftRear1, rightRear1);
}

VectorChassis& VectorChassis::addMotors(pros::Motor left, pros::Motor right) {
    leftVector.push_back(left);
    rightVector.push_back(right);
    return *this;
}

VectorChassis& VectorChassis::move(int left, int right){
    ITERATELEFT(move_voltage(left));
    ITERATERIGHT(move_voltage(right));
    return *this;
}

VectorChassis& VectorChassis::opDrive(int drive, int turn, double turnSensitivity, int strafe) {
    if(abs(drive) < 10 ) drive = 0;
    if(abs(turn) < 10 ) turn = 0;
    if(abs(strafe) < 10 ) strafe = 0;

    int left = drive + turn * turnSensitivity;
    int right = drive - turn * turnSensitivity;

    int leftSign = checkSign(left);
    int rightSign = checkSign(right);
    int xSign = checkSign(strafe);

    int remapLeft = (pow(left,2)*.75)*leftSign;
    int remapRight = (pow(right,2)*.75)*rightSign;
    int quadX = (pow(strafe,2)*.75)*xSign;

    move(remapLeft, remapRight);
    return *this;
}


VectorChassis& VectorChassis::driveTo(Vector point, int speed, int slew, bool reverse) {
    /* under construction */
    return *this;
}

VectorChassis& VectorChassis::stop() {
    ITERATELEFT(move_voltage(0));
    ITERATERIGHT(move_voltage(0));
    return *this;
}

VectorChassis& VectorChassis::setBrakeMode(pros::motor_brake_mode_e mode){
    ITERATELEFT(set_brake_mode(mode));
    ITERATERIGHT(set_brake_mode(mode));
    return *this;
}