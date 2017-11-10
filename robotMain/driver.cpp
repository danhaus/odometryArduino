/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */



#include "driver.h" //include the declaration for this class
#include "MD25.h"


Driver::Driver(float Pp, float Pi, float Pd, int circumference, int wheel_dist, int limit_correction, unsigned int time_period, int pid_precision) { // constructor, PID constants
	Kp = Pp;
	Ki = Pi;
	Kd = Pd;
	cir = circumference;
	w_dist = wheel_dist;
	limit_cor = limit_correction;
	error = 0;
	previous_error = 0;
	md = new MD25(0); // 0 is for mode 0 of MD25 and code is writ
	period = time_period;
	pid_prec = pid_precision;
}

void Driver::forward(int dist) {
	md->encReset(); // reset encoders
	int cumulated_error = 0;
	int counter = 0;
	do {
		int enc_target = getEncVal(dist); // get target value for encoders
		int enc1 = md->encoder1(); // asign current value of encoder1 to var enc1
		calculatePid(enc1, enc_target); // calculate PID value and assign it to private var PID_speed_limited
		md->setSpeed(PID_speed_limited, PID_speed_limited);
		 if (readingPeriod()) {
		 	cumulated_error += error;
		 	counter++;
		 	if (counter >= 10) {
		 		if (cumulated_error < pid_prec) {
		 			break;
		 		}
		 		else {
		 			counter = 0;
		 			cumulated_error = 0;
		 		}
		 	}
		 }
	} while(true);
}

void Driver::printPid() {
	Serial.print("error: ");
	Serial.println(error);
	Serial.print("P: ");
	Serial.println(P);
	Serial.print("I: ");
	Serial.println(I);
	Serial.print("D: ");
	Serial.println(D);
	Serial.print("PID_val: ");
	Serial.println(PID_val);
	Serial.print("PID_speed_theor: ");
	Serial.println(PID_speed_theor);
	Serial.print("PID_speed_limited: ");
	Serial.println(PID_speed_limited);
	Serial.println();
}

void Driver::printEnc() {
	int encodeVal1 = md->encoder1();
	Serial.print("encoder1: ");
	Serial.print(encodeVal1, DEC);
	Serial.print("\t");
	int encodeVal2 = md->encoder2();
	Serial.print("encoder2: ");
	Serial.println(encodeVal2, DEC);
	Serial.println();
}



// HELP FUNCTIONS

int Driver::getEncVal(int dist) { // returns encoder value to be set to drive required distance
	int enc_count = int(((float(dist)/cir) * 360));
	return enc_count;
}

int Driver::getSpeed(int speed) {
	if (speed >= 255 - limit_cor) {
		return (255 - limit_cor);
	}
	if (speed <= 0 + limit_cor) {
		return (0 + limit_cor);
	}
	return speed;
}

void Driver::calculatePid(int enc_val_cur, int target_val) {
	error = target_val - enc_val_cur;
	P = error; // proportional
	I = I + error; // integral
	D = error - previous_error; // derivative
	PID_val = (Kp*P) + (Ki*I) + (Kd*D); // not sure about the sign after 128
	PID_speed_theor = 128 + int(PID_val);
	PID_speed_limited = getSpeed(PID_speed_theor);
	previous_error = error;
}
bool Driver::readingPeriod() {
	cur_time = millis();
	if (cur_time > (prev_time + period)) {
		prev_time = cur_time;
		return true;
	}
	return false;
}

// 

