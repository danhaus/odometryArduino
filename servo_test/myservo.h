/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */

#ifndef MyServo_H
#define MyServo_H

#include <Arduino.h>
#include <Servo.h>

class MyServo {
public:
	MyServo(byte pin); // constructor
  void attach();
	void setPosition(int angle, int del=50);
private:
	byte _pin;
	Servo* servo;
	int cur_angle;
};

#endif
