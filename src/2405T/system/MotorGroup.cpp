
#include "main.h"
#include "2405T/system/MotorGroup.hpp"
#include "pros/motors.hpp"

MotorGroup::MotorGroup(pros::Motor motor1, pros::Motor motor2) :
    motor1(motor1),
    motor2(motor2) {

}

pros::Motor MotorGroup::getMotor1() {
    return motor1;
}

pros::Motor MotorGroup::getMotor2() {
    return motor2;
}

//Copy of pros::Motor functions for the motor group
MotorGroup& MotorGroup::move(int velocity) {
    motor1.move(velocity);
    motor2.move(velocity);
    return *this;
}

MotorGroup& MotorGroup::move_absolute(int position, int velocity){
    motor1.move_absolute(position, velocity);
    motor2.move_absolute(position, velocity);
    return *this;
}

MotorGroup& MotorGroup::move_relative(int position, int velocity){
    motor1.move_relative(position, velocity);
    motor2.move_relative(position, velocity);
    return *this;
}

MotorGroup& MotorGroup::move_velocity(int velocity){
    motor1.move_velocity(velocity);
    motor2.move_velocity(velocity);
    return *this;
}

MotorGroup& MotorGroup::move_voltage(int voltage){
    motor1.move_voltage(voltage);
    motor2.move_voltage(voltage);
    return *this;
}

MotorGroup& MotorGroup::tare_position(){
    motor1.tare_position();
    motor2.tare_position();
    return *this;
}

MotorGroup& MotorGroup::set_brake_mode(pros::motor_brake_mode_e_t mode){
    motor1.set_brake_mode(mode);
    motor2.set_brake_mode(mode);
    return *this;
}

MotorGroup& MotorGroup::set_encoder_units(pros::motor_encoder_units_e_t units){
    motor1.set_encoder_units(units);
    motor2.set_encoder_units(units);
    return *this;
}

MotorGroup& MotorGroup::set_gearing(pros::motor_gearset_e_t gearset){
    motor1.set_gearing(gearset);
    motor2.set_gearing(gearset);
    return *this;
}

MotorGroup& MotorGroup::set_reversed(bool reversed){
    motor1.set_reversed(reversed);
    motor2.set_reversed(reversed);
    return *this;
}

MotorGroup& MotorGroup::set_zero_position(int position){
    motor1.set_zero_position(position);
    motor2.set_zero_position(position);
    return *this;
}

MotorGroup& MotorGroup::set_voltage_limit(int limit){
    motor1.set_voltage_limit(limit);
    motor2.set_voltage_limit(limit);
    return *this;
}

MotorGroup& MotorGroup::set_current_limit(int limit){
    motor1.set_current_limit(limit);
    motor2.set_current_limit(limit);
    return *this;
}