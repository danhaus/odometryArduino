/* This code..
 * 
 */

#include "LED.h"
#include "MD25.h"

// create objects
LED led(13);
MD25 md;

void setup() {
  Serial.begin(9600); // start serial commuication
  led.blink(1000);
  md.encodeReset(); // reset encoders
  md.simpleForward(200, 200);
}

void loop() {
  int encodeVal1 = md.encoder1();
  Serial.print("encoder1: ");
  Serial.print(encodeVal1, DEC);
  Serial.print("\t");
  int encodeVal2 = md.encoder2();
  Serial.print("encoder2: ");
  Serial.println(encodeVal2, DEC);
  delay(100);
}
