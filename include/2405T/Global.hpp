#pragma once
#include "main.h"
#include "system/Controls.hpp"

extern pros::Motor Lf;
extern pros::Motor Rf;
extern pros::Motor Lr;
extern pros::Motor Rr;
extern pros::Motor Lr1;
extern pros::Motor Rr1;
extern pros::Motor liftL;
extern pros::Motor liftR;
extern pros::Motor intakeL;
extern pros::Motor intakeR;
extern pros::Controller master;
extern pros::ADIDigitalOut claw;
extern pros::ADIDigitalOut rearClaw;

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
void progSkills(Subsystems subsystems);