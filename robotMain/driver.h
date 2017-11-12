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
	Driver(float Pp, float Pi, float Pd, float Pp_t, float Pi_t, float Pd_t, int limit_correction, int limit_correction_turning, int circumference, float wheel_dist); // constructor
	/* Pp, Pi, Pd: PID constants, circumference of the wheel [mm], wheel_dist[mm]: distance between the wheels, limit_correction: speed correction so that it does not reach max power,
	time_period[ms]: period in between readings of error for terminating PID, pid_precision: sum of 10 erros for terminating driving function */
	void forward(int dist); // drives forward using PID and functions above
	void turnAtSpot(float angle); // turns at spot until it reaches required angle (positive clockwise)
	void turn(int rad, int angle, char side);
	void printPid(); // prints current PID values and error
	void printEnc(); // prints current ecoder values

	// HELP FUNCTIONS
	int getEncVal(int dist);
	int getSpeed(int speed); /* inputs speed from pid, if it is outside the limit
	[0+limit_correction, 255-limit_correction], returns the limit value, otherwise it returns the speed */
	int getSpeedTurn(int speed);
	void calculatePid(int enc_val_cur, int target_val); // calculates PID values
	void calculatePidTurn(int enc_val_cur, int target_val); // calculates PID values
	bool readingPeriod(); // returns true if time elapsed between current time and previous time is larger than period
	bool terminatePid(); // help function for terminating pid
	float pi;

private:
	float Kp;
	float Ki;
	float Kd;
	float Kp_t;
	float Ki_t;
	float Kd_t;
	int limit_cor;
  	int limit_cor_turn;
	int error; // error for PID (encoder count)
	int previous_error;
	int P; // proportional error for PID
	int I; // integral of error for PID
	int D; // differential of error for PID
	float PID_val; // value for PID (it is devided by 100 so that it does not require type float)
	int PID_speed_theor; // PID_speed = 128 + PID_val (automatically asigned in calculatePID())
	int PID_speed_limited; // limited PID speed so that the motor does not exceeds min and max speeds, performed by getSpeed(..)
	int cir; // circumference of the wheel [mm]
	float w_dist; // distance between wheels [mm]
	MD25* md;
	unsigned long cur_time;
	unsigned long prev_time;
	unsigned int period;
	int pid_prec; // if sum of 10 encoder reading is smaller than pid_prec, forward(..) terminates
	int counter;
	int cumulated_error;
};

#endif
