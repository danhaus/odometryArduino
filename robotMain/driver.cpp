/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */


#include "driver.h" //include the declaration for this class
#include "MD25.h"


Driver::Driver(float Pp, float Pi, float Pd, int circumference, int wheel_dist) { // constructor, PID constants
	Kp = Pp;
	Ki = Pi;
	Kd = Pd;
	cir = circumference;
	w_dist = wheel_dist;
	error = 0;
	previous_error = 0;
	md = new MD25(0);
}

int Driver::getEncVal(int dist) { // returns encoder value to be set to drive required distance
	int enc_count = ((dist/cir) * 360);
	return enc_count;
}

int Driver::getSpeed(int speed, int limit_correction) {
	if (speed >= 255 - limit_correction) {
		return (255 - limit_correction);
	}
	if (speed <= 0 + limit_correction) {
		return (0 + limit_correction);
	}
	return speed;
}

void Driver::calculatePid(int enc_val, int target_val) {
	error = target_val - enc_val;
	P = error;
	I = I + error;
	D = error - previous_error;
	PID_value = ((Kp*P) + (Ki*I) + (Kd*D))/100;
}

void Driver::forward(int dist) {
	md->encReset();
}

