

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
ModStepper stepper1(STEPS, 6, 7, 8, 9);
ModStepper stepper2(STEPS, 2, 3, 4, 5);

// the previous reading from the analog input
int previous = 0;

ModServo servos[NUM_SERVOS];


int angle = 0;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  servos[0].attach(14);
  servos[1].attach(12);
  servos[2].attach(11);
  servos[3].attach(10);
  servos[4].attach(15);

  int i;
  for(i=0; i<NUM_SERVOS; i++){
    servos[i].setSpeed(20); 
  }

  stepper1.setSpeed(30);
  stepper2.setSpeed(30);

}

void loop()
{
  int i;
  
  stepper1.update();
  stepper2.update();  


  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();
    incomingByte -= 48;
    angle = incomingByte * 20;

    Serial.print("I received: ");
    Serial.println(angle);
    
    stepper1.setAction(angle);
    stepper2.setAction(angle * -1);
    for(i=0; i<NUM_SERVOS; i++){
      servos[i].moveTo(angle); 
    }
  }

  for(i=0; i<NUM_SERVOS; i++){
    servos[i].update(); 
  }
}




