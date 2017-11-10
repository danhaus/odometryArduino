/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */

/*	10*circumference = 3213 mm
	distance between wheels = 235 mm
*/

#ifndef Driver_H
#define Driver_H

#include <Arduino.h>
#include "MD25.h"


class Driver {
public:
	Driver(float Pp, float Pi, float Pd, int circumference, int wheel_dist, int limit_correction, unsigned int time_period, int pid_precision); // constructor
	/* Pp, Pi, Pd: PID constants, circumference of the wheel [mm], wheel_dist[mm]: distance between the wheels, limit_correction: speed correction so that it does not reach max power,
	time_period[ms]: period in between readings of error for terminating PID, pid_precision: sum of 10 erros for terminating driving function */
	void forward(int dist); // drives forward using PID and functions above
	void printPid(); // prints current PID values and error
	void printEnc(); // prints current ecoder values

	// HELP FUNCTIONS
	int getEncVal(int dist);
	int getSpeed(int speed); /* inputs speed from pid, if it is outside the limit
	[0+limit_correction, 255-limit_correction], returns the limit value, otherwise it returns the speed */
	void calculatePid(int enc_val_cur, int target_val); // calculates PID values
	bool readingPeriod(); // returns true if time elapsed between current time and previous time is larger than period

private:
	float Kp;
	float Ki;
	float Kd;
	int limit_cor;
	int error; // error for PID (encoder count)
	int previous_error;
	int P; // proportional error for PID
	int I; // integral of error for PID
	int D; // differential of error for PID
	float PID_val; // value for PID (it is devided by 100 so that it does not require type float)
	int PID_speed_theor; // PID_speed = 128 + PID_val (automatically asigned in calculatePID())
	int PID_speed_limited; // limited PID speed so that the motor does not exceeds min and max speeds, performed by getSpeed(..)
	int cir; // circumference of the wheel [mm]
	int w_dist; // distance between wheels [mm]
	MD25* md;
	unsigned long cur_time;
	unsigned long prev_time;
	unsigned int period;
	int pid_prec; // if sum of 10 encoder reading is smaller than pid_prec, forward(..) terminates
};

#endif
