/* This code..
 * 
 */

#include "LED.h"
#include "MD25.h"
#include "driver.h"
#include <Servo.h>

#define MD25ADDRESS         0x58                              // Address of the MD25
#define SPEED1              0x00                              // Byte to send speed to both motors for forward and backwards motion if operated in MODE 2 or 3 and Motor 1 Speed if in MODE 0 or 1
#define SPEED2              0x01                              // Byte to send speed for turn speed if operated in MODE 2 or 3 and Motor 2 Speed if in MODE 0 or 1
#define ENCODERONE          0x02                              // Byte to read motor encoder 1
#define ENCODERTWO          0x06                              // Byte to read motor encoder 2
#define ACCELERATION        0xE                               // Byte to define motor acceleration
#define CMD                 0x10                              // Byte to reset encoder values
#define MODE_SELECTOR       0xF                               // Byte to change between control MODES

#define servo_pin 9
#define led_pin 13

// create objects
LED led(led_pin);
MD25 md(0);
Driver driver(0, 0, 0, 100, 200);
Servo servo;

int cor = 15;

void setup() {
  Serial.begin(9600); // start serial commuication
  md.setup();
//  led.blink(1000);
  md.encodeReset(); // reset encoders
//  md.setSpeed(100, 100);
  delay(200);
  servo.attach(servo_pin);
  Serial.println("set up done");
}

void loop() {
  
   
  
  md.setSpeed(80, 80);
  delay(1000);
  //md.setSpeed(105, 151); 
  //delay(1000);          // 90 degrees to the left 
  
 // md.setSpeed(80,80);
  //delay(1000);
  //md.setSpeed(151,105);
  //delay(1000);         // 90 degrees to the right 
  
  md.setSpeed(151, 105);  
  delay(1500);          // 180 degrees(faces reverse Direction)      // delay time which gives any angle =  that angle * (100/9)
                                                                       // e.g delay(50*100/9) = 50 degree turn
   //md.setSpeed(151,105);                                              // BUT keep setspeed at(100,156) or (156,100) depending on the direction
   //delay(500);         // 45 degrees to the right                    
    //md.setSpeed(151,105);  
    //delay(556);        // 50 degrees to the right
   md.setSpeed(80, 80);  
   delay(1000);       
   //md.setSpeed(60, 100);   // to move in a circle set both speeds in the same direction but keep one faster than the other 
   //delay(10000);
   md.setSpeed(128, 128);
   delay(5000);





}
