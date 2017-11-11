/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 *
 */

#ifndef MD25_H
#define MD25_H

#include <Arduino.h>

#include <SoftwareSerial.h>
#include <Wire.h>

class MD25 {
public:
	MD25(int mode); // constructor, mode is used to setup MD25 in setup()
	void setup(); // setups I2C and mode of MD22
	void forward(int speed, int encoderCount); /* drives both motors forward with set speed until encoders
	do not reach the specified number of pulses (360 pulese per revolution), then it stops */
	void setSpeed(int speed1, int speed2); /* send command to drive both motors with the set speeds, =D
	needs to be enclosed in while loop to drive constantly, otherwise it stops within 2 seconds */
	void stopMotors(); // stops both motors =D
	void encodeReset(); // resets both endocedrs =D
	long encoder1(); // returns value of encoder 1 =D
	long encoder2(); // returns value of encoder 2 =D
	int volts(); // returns battery voltage as a sum of ten readings
private:
	int _mode;
};

#endif
