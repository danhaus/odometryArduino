/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */

#ifndef Driver_H
#define Driver_H

#include <Arduino.h>
#include "MD25.h"


class Driver {
public:
	Driver(float Pp, float Pi, float Pd, int circumference, int wheel_dist, int limit_correction=15); // constructor
	int getEncVal(int dist);
	int getSpeed(int speed); /* inputs speed from pid, if it is outside the limit
	[0+limit_correction, 255-limit_correction], returns the limit value, otherwise it returns the speed */
	void calculatePid(int enc_val_cur, int target_val); // calculates PID values
	void forward(int dist); // drives forward using PID and functions above
	void printPid(); // prints current PID values and error

private:
	float Kp;
	float Ki;
	float Kd;
	int limit_cor;
	int error; // error for PID
	int previous_error;
	int P; // proportional error for PID
	int I; // integral of error for PID
	int D; // differential of error for PID
	int PID_val; // value for PID (it is devided by 100 so that it does not require type float)
	int PID_speed_theor; // PID_speed = 128 + PID_val (automatically asigned in calculatePID())
	int PID_speed_limited; // limited PID speed so that the motor does not exceeds min and max speeds, performed by getSpeed(..)
	int cir; // circumference of the wheel [mm]
	int w_dist; // distance between wheels [mm]
	MD25* md;
};

#endif
