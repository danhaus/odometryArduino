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
Driver driver(5, 0, 1, 100, 200);
Servo servo;

int cor = 15;

void setup() {
  Serial.begin(9600); // start serial commuication
  md.setup();
//  led.blink(1000);
  md.encReset(); // reset encoders
//  md.setSpeed(100, 100);
  delay(200);
  servo.attach(servo_pin);
  Serial.println("set up done");
}

void loop() {
  driver.calculatePid(10, 1000);
  Serial.print("P: ");
  Serial.println(driver.P);
  Serial.print("I: ");
  Serial.println(driver.I);
  Serial.print("D: ");
  Serial.println(driver.D);
  Serial.println(driver.PID_value);
  Serial.println();
  delay(1000);
  driver.calculatePid(100, 1000);
  Serial.print("P: ");
  Serial.println(driver.P);
  Serial.print("I: ");
  Serial.println(driver.I);
  Serial.print("D: ");
  Serial.println(driver.D);
  Serial.println(driver.PID_value);
  Serial.println();
  delay(1000);
  driver.calculatePid(500, 1000);
  Serial.print("P: ");
  Serial.println(driver.P);
  Serial.print("I: ");
  Serial.println(driver.I);
  Serial.print("D: ");
  Serial.println(driver.D);
  Serial.println(driver.PID_value);
  Serial.println();
  delay(1000);
  driver.calculatePid(900, 1000);
  Serial.print("P: ");
  Serial.println(driver.P);
  Serial.print("I: ");
  Serial.println(driver.I);
  Serial.print("D: ");
  Serial.println(driver.D);
  Serial.println(driver.PID_value);
  Serial.println();
  delay(1000);
  driver.calculatePid(1100, 1000);
  Serial.print("P: ");
  Serial.println(driver.P);
  Serial.print("I: ");
  Serial.println(driver.I);
  Serial.print("D: ");
  Serial.println(driver.D);
  Serial.println(driver.PID_value);
  Serial.println();
  delay(1000);

  while(true);






  
//  int t = 0;
////  Serial.println("reading encoder 1");
//  led.blink(400);
//  do{
//    md.setSpeed(0+cor, 0+cor);
//    delay(500);
//    t += 500;
//  } while (t <= 5000);
//  md.setSpeed(128, 128);
//  delay(500);
//  t = 0;
//  do{
//    md.setSpeed(255-cor, 255-cor);
//    delay(500);
//    t += 500;
//  } while (t <= 5000);
//  md.setSpeed(128, 128);
//  delay(500);
//
//  int encodeVal1 = md.encoder1();
//  Serial.print("encoder1: ");
//  Serial.print(encodeVal1, DEC);
//  Serial.print("\t");
////  Serial.println("reading encoder 2");
//  int encodeVal2 = md.encoder2();
//  Serial.print("encoder2: ");
//  Serial.println(encodeVal2, DEC);
//  delay(3000);
//  md.encodeReset();
}
