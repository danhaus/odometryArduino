/* This code..
 * 
 */

#include "LED.h"
#include "MD25.h"

#define MD25ADDRESS         0x58                              // Address of the MD25
#define SPEED1              0x00                              // Byte to send speed to both motors for forward and backwards motion if operated in MODE 2 or 3 and Motor 1 Speed if in MODE 0 or 1
#define SPEED2              0x01                              // Byte to send speed for turn speed if operated in MODE 2 or 3 and Motor 2 Speed if in MODE 0 or 1
#define ENCODERONE          0x02                              // Byte to read motor encoder 1
#define ENCODERTWO          0x06                              // Byte to read motor encoder 2
#define ACCELERATION        0xE                               // Byte to define motor acceleration
#define CMD                 0x10                              // Byte to reset encoder values
#define MODE_SELECTOR       0xF                               // Byte to change between control MODES

// create objects
LED led(13);
MD25 md(2);

void setup() {
  Serial.begin(9600); // start serial commuication
  md.setup();
//  led.blink(1000);
  md.encodeReset(); // reset encoders
//  md.simpleForward(100, 100);
  delay(200);
  Serial.println("set up done");
}

void loop() {
//  Serial.println("reading encoder 1");
  md.simpleForward(-50, -50);
  int encodeVal1 = md.encoder1();
  Serial.print("encoder1: ");
  Serial.print(encodeVal1, DEC);
  Serial.print("\t");
//  Serial.println("reading encoder 2");
  int encodeVal2 = md.encoder2();
  Serial.print("encoder2: ");
  Serial.println(encodeVal2, DEC);
  delay(3000);
  md.encodeReset();
}
