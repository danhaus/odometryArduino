/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(2);  // attaches the servo on pin 2 to the servo object
}

void loop() {
  for (pos = 0; pos <= 31; pos +=2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);}                       // waits 15ms for the servo to reach the position
    delay(2000);
  for (pos = 31; pos <= 62; pos +=2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50); }                      // waits 15ms for the servo to reach the position
    delay(2000);
 for (pos = 62; pos <= 96; pos +=2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(100);  }                     // waits 15ms for the servo to reach the position
    delay(2000);
 for (pos = 96; pos <= 128; pos +=2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50);   }                    // waits 15ms for the servo to reach the position
    delay(5000);
   for (pos = 128; pos <= 160; pos +=2) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50); }                      // waits 15ms for the servo to reach the position
    delay(2000);
  for (pos = 160; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    delay(1000);
}

