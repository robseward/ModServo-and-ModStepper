

#include <Servo.h>
#include "ModServo.h"
#include "ModStepper.h"

//#include <Serial.h>

// change this to the number of steps on your motor
#define STEPS 100
#define NUM_SERVOS 5

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
ModStepper stepper(STEPS, 6, 7, 8, 9);

ModServo servo;

int servoPin = 14;

int angle = 0;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  
  servo.attach(servoPin);
  servo.setSpeed(20); 
  
  stepper.setSpeed(30);
}

void loop()
{

  //Enter digits from 0-9. These will set the servo between a range of
  //0 and 180 degrees. It will also move the stepper between 0 and 180 steps
  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();
    incomingByte -= 48;              //convert ascii digits into int digits 
    angle = incomingByte * 20;       //multiply your digits so they are in the range of 0-180

    Serial.print("angle: ");
    Serial.println(angle);
    
    int steps = angle;
    servo.moveTo(angle); 
    
    stepper.setAction(steps);
  }

  stepper.update();
  servo.update(); 
  
}




