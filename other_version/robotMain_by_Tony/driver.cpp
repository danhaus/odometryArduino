/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */


#include "driver.h" //include the declaration for this class

Driver::Driver(float Pp, float Pi, float Pd, int circumference, int wheelDist) { // constructor, PID constants
	Kp = Pp;
	Ki = Pi;
	Kd = Pd;
	cir = circumference;
	wDist = wheelDist;
}

int Driver::getEncVal(int dist) { // returns encoder value to be set to drive required distance
	int encCount = ((dist/cir) * 360);
	return encCount;
}

