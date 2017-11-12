/* This code..
 * 
 */

#include "myservo.h"


#define servo_pin 9
#define led_pin 13
#define led_battery_pin 8
#define button_pin 12
#define servo_pin 2


// create objects
MyServo servo(servo_pin);

void setup() {
  servo.attach();
  Serial.begin(9600); // start serial commuication
  delay(200);
  Serial.println("set up done");
}

void loop() {
  servo.setPosition(0);
  delay(1000);
}
