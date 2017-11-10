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

float Pp = 2;
float Pi = 0;
float Pd = 0;
int circumference = 321; // [mm]
int wheel_dist = 235; // [mm]
int limit_correction = 70; // [ms] (min value of 15)
unsigned int time_period = 50; // [ms]
int pid_precision = 10; // sum of ten errors for pid [encoder count]

// create objects
LED led(led_pin);
MD25 md(0);
Driver driver(Pp, Pi, Pd, circumference, wheel_dist, limit_correction, time_period, pid_precision);
Servo servo;

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
//  // DEBUGGING PID
//  int target_value = driver.getEncVal(3000);
//  int enc_cur = md.encoder1();
//  Serial.print("target_value: ");
//  Serial.println(target_value);
//  Serial.print("enc_cur: ");
//  Serial.println(enc_cur);
//  driver.calculatePid(enc_cur, target_value);
//  driver.printPid();
//  int enc = md.encoder1();
//  Serial.println("\n");
//  delay(500);

  driver.forward(3000);
  while(true);


// // PID PRINTING
//  driver.calculatePid(10, 1000);
//  driver.printPid();
//  driver.calculatePid(100, 1000);
//  driver.printPid();
//  driver.calculatePid(500, 1000);
//  driver.printPid();
//  driver.calculatePid(900, 1000);
//  driver.printPid();
//  driver.calculatePid(1100, 1000);
//  driver.printPid();
//  while(true);





//// FIRST TEST
//  int t = 0;
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
//  int encodeVal2 = md.encoder2();
//  Serial.print("encoder2: ");
//  Serial.println(encodeVal2, DEC);
//  delay(3000);
//  md.encReset();


}
