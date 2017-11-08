/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */

#ifndef Driver_H
#define Driver_H

#include <Arduino.h>

class Driver {
public:
	Driver(float Pp, float Pi, float Pd, int circumference, int wheelDist); // constructor
	int getEncVal(int dist);
	int encoder1;
	int encoder2;
private:
	float Kp;
	float Ki;
	float Kd;
	int cir; // circumference of the wheel [mm]
	int wDist; // distance between wheels [mm]
};

#endif
