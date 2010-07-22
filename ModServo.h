

// ensure this library description is only included once
#ifndef ModServo_h
#define ModServo_h

#include <Servo.h>



// library interface description
class ModServo {
public:
  // constructors:
  ModServo(){
  };

  // speed setter method:
  void setSpeed(long whatSpeed);

  uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
  uint8_t attach(int pin, int min, int max); // as above but also sets min and max values for writes. 
  void detach();
  void write(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
  void writeMicroseconds(int value); // Write pulse width in microseconds 
  int read();                        // returns current pulse width as an angle between 0 and 180 degrees
  int readMicroseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
  bool attached();                   // return true if this servo is attached, otherwise false


  void moveTo(int new_angle);
  int update();

  void maybeStepMotor();

  int version(void);

private:

  Servo servo;

  int direction;        // Direction of rotation
  int speed;          // Speed in RPMs
  unsigned long step_delay;    // delay between steps, in ms, based on speed
  int number_of_steps;      // total number of steps this motor can take
  int step_number;        // which step the motor is on
  int steps_left;   //number of steps left if running a sequence

  int current_angle;


  long last_step_time;      // time stamp in ms of when the last step was taken
};

#endif


