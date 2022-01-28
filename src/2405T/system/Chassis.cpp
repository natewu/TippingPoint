#include "main.h"
#include "2405T/Global.hpp"
#include "2405T/system/Chassis.hpp"
#include "pros/motors.hpp"

Chassis::Chassis(pros::Motor leftFront, pros::Motor leftRear, pros::Motor rightFront, pros::Motor rightRear) :
    leftFront(leftFront),
    leftRear(leftRear),
    rightFront(rightFront),
    rightRear(rightRear) {

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