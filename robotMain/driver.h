/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */

#ifndef Driver_H
#define Driver_H

#include <Arduino.h>

class Driver {
public:
	Driver(); // constructor
	void getEncVal(int dist);
	int encoder1;
	int encoder2;
private:
	float p;
	float i;
	float d;
	int cir; // circumference of the wheel
	int wDist; // distance between wheels
};

#endif
