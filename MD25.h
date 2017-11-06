/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */

#ifndef MD25_H
#define MD25_H

#include <Arduino.h>

class MD25 {
public:
	MD25(); // constructor
	void forward(int speed, int encoderCount); /* drives both motors forward with set speed until encoders
	do not reach the specified number of pulses (360 pulese per revolution), then it stops */
	void simpleForward(int speed1, int speed2); /* send command to drive both motors with the set speeds,
	needs to be enclosed in while loop to drive constantly, otherwise it stops within 2 seconds */
	void stopMotors(); // stops both motors
	void encodeReset(); // resets both endocedrs
	long encoder1(); // returns value of encoder 1
	long encoder2(); // returns value of encoder 2
	int volts(); // returns battery voltage as a sum of ten readings
};

#endif
