/* This code..
 * 
 */


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
MD25 md(0);

int cor = 15;

void setup() {
  Serial.begin(9600); // start serial commuication
  md.setup();
  delay(200);
  Serial.println("set up done");
}

void loop() {
  Serial.print("battery voltage (sum of 10 readings): ");
  Serial.println(md.volts());
  delay(1000);
}
