

#include "WProgram.h"
#include "ModServo.h"



uint8_t ModServo::attach(int pin){
  int result = this->servo.attach(pin);
  this->current_angle = 90;
  return result;
}
uint8_t ModServo::attach(int pin, int min, int max){
  return  this->servo.attach(pin, min, max);
}
void ModServo::detach(){
  this->servo.detach();
}
void ModServo::write(int value){
  this->servo.write(value);
}
void ModServo::writeMicroseconds(int value){
  this->servo.writeMicroseconds(value);
}
int ModServo::read(){
  return this->servo.read();
}
int ModServo::readMicroseconds(){
  return this->servo.readMicroseconds();
}
bool ModServo::attached(){
  return this->servo.attached();
}


/*
  Sets the speed in revs per minute
 
 */
void ModServo::setSpeed(long whatSpeed)
{
  this->step_delay = 60L * 1000L / 180 / whatSpeed;
}


void ModServo::moveTo(int new_angle){
  int difference = this->current_angle - new_angle;
  this->steps_left = abs(difference);  // how many steps to take
  Serial.println(difference);
  if (difference > 0) {
    this->direction = 1;
  }
  if (difference < 0) {
    this->direction = 0;
  }
}


int ModServo::update(){
  if(this->steps_left > 0) {
    maybeStepMotor();
  }
  return this->steps_left;
}

void ModServo::maybeStepMotor(){
  if (millis() - this->last_step_time >= this->step_delay) {
    this->last_step_time = millis();
    this->current_angle = direction ? this->current_angle - 1 : this->current_angle + 1;
    this->servo.write(current_angle);
    this->steps_left--;
  }	
}


/*
  version() returns the version of the library:
 */
int ModServo::version(void)
{
  return 1;
}

