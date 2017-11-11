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
	counter = 0; // counter for forward()
	cumulated_error = 0; // cumulated error for terminating the forward()
	pi = 3.14159;
}

void Driver::forward(int dist) {
	md->encReset(); // reset encoders
	do {
		int enc_target = getEncVal(dist); // get target value for encoders
		int enc1 = md->encoder1(); // asign current value of encoder1 to var enc1
		calculatePid(enc1, enc_target); // calculate PID value and assign it to private var PID_speed_limited
		md->setSpeed(PID_speed_limited, PID_speed_limited);
	} while(true);
}

void Driver::turnAtSpot(int angle) {
	md->encReset(); // reset encoders
	int arc = int((float(angle)/360) * (pi*wheel_dist));
	int dist = arc;
	do {
		int enc_target = getEncVal(dist); // get target value for encoders
		int enc1 = md->encoder1();
		calculatePid(enc1, enc_target);
		int spd1 = PID_speed_limited;
		int spd2 = abs(PID_speed_limited - 128);
		md->setSpeed(spd1, spd2);
	} while(true);
}

void Driver::turn(int rad, int angle, char side) {
	float arc_portion = (float(angle)/360);
	int arc = int ((float(rad) + (float(wheel_dist)/2)) * arc_portion); // length of outer arc
	float speed_ratio = float(rad) - (float(wheel_dist)/2) / (float(rad) + float(wheel_dist)/2);
	int dist = arc;
	typedef void (*encoder) ();
	if (side == 'L') {
		encoder = md->encoder2;
	}
	else {
		encoder = md->encoder1;
	}
	do {
		int enc_target = getEncVal(dist); // get target value for encoders
		int enc = encoder();
		calculatePid(enc, enc_target);
		if (side == 'L') {

			int spd1 = round((PID_speed_limited) * speed_ratio);
			int spd2 = PID_speed_limited();
		}
		else {
			int spd1 = PID_speed_limited;
			int spd2 = round((PID_speed_limited) * speed_ratio);
		}
		md->setSpeed(sdp1, spd2);
	}
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

bool Driver::terminatePid() {
	cumulated_error += error;
	counter++;
	if (counter >= 10) {
		if (cumulated_error < pid_prec) {
			return true;
		}
		else {
			counter = 0;
			cumulated_error = 0;
		}
	}
	return false;	 
}

// 

