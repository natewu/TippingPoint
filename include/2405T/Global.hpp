#pragma once
#include "main.h"

extern pros::Motor Lf;
extern pros::Motor Rf;
extern pros::Motor Lr;
extern pros::Motor Rr;
extern pros::Motor liftL;
extern pros::Motor liftR;
extern pros::Motor intakeL;
extern pros::Motor intakeR;
extern pros::Controller master;
extern pros::ADIDigitalOut claw;

//Sensors
extern pros::ADIEncoder left;
extern pros::ADIEncoder right;
extern pros::ADIEncoder middle;

extern float pi;
extern bool toggle, latch, Rlatch;

extern std::shared_ptr<okapi::OdomChassisController> drive;

int checkSign(int val);
void motorSpeed();
void controller();