/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */



#include "driver.h" //include the declaration for this class
#include "MD25.h"


Driver::Driver(float Pp, float Pi, float Pd, float Pp_t, float Pi_t, float Pd_t, int limit_correction, int limit_correction_turning, int circumference, float wheel_dist) { // constructor, PID constants
	Kp = Pp;
	Ki = Pi;
	Kd = Pd;
	Kp_t = Pp_t;
	Ki_t = Pi_t;
	Kd_t = Pd_t;
	cir = circumference;
	w_dist = wheel_dist;
	limit_cor = limit_correction;
	limit_cor_turn = limit_correction_turning;
	error = 0;
	previous_error = 0;
	md = new MD25(0, 2); // parametres: mode, accelration (ints 1-10)
	counter = 0; // counter for forward()
	cumulated_error = 0; // cumulated error for terminating the forward()
	pi = 3.14159;
}

void Driver::setup() {
	md->setup();
}

void Driver::forward(int dist, int timeout) {
	md->encReset(); // reset encoders
	delay(10);
	int enc1, enc_target;
	int start_time = millis();
	do {
		enc_target = getEncVal(dist); // get target value for encoders
		enc1 = md->encoder1(); // asign current value of encoder1 to var enc1
		calculatePid(enc1, enc_target); // calculate PID value and assign it to private var PID_speed_limited
		md->setSpeed(PID_speed_limited, PID_speed_limited);
//		Serial.print("enc_target: ");
//		Serial.println(enc_target);
//		Serial.print("enc1: ");
//		Serial.println(enc1);
//		Serial.println();
	} while((abs(enc1) + 1 < abs(enc_target)) && ((millis() - start_time) < timeout));
//	} while(true);
//  md->stopMotors();
}

void Driver::turnAtSpot(float angle, int timeout) {
	md->encReset(); // reset encoders
	delay(10);
	int arc = int((angle/360) * (pi*w_dist));
	int dist = arc;
	int enc1, enc_target = 0;
	int start_time = millis();
  Serial.println(start_time);
  Serial.println();
	do {
		enc_target = getEncVal(dist); // get target value for encoders
		enc1 = md->encoder1();
		calculatePidTurn(enc1, enc_target);
		int spd1 = PID_speed_limited;
		int spd2 = 128 - (spd1 - 128);
		md->setSpeed(spd1, spd2);
	} while((abs(enc1) + 1 < abs(enc_target)) && ((millis() - start_time) < timeout));
//  md->stopMotors();
}

void Driver::turn(int rad, int angle, char side, int timeout) {
	md->encReset();
	delay(10);
	float arc_portion = (float(angle)/360);
	int arc = int (((float(rad) + (w_dist/2)) )*arc_portion*2*pi); // length of outer arc
	float speed_ratio = (float(rad) - (w_dist/2)) / (float(rad) + w_dist/2);
	int dist = arc;
	int spd1, spd2, enc, enc_target;
	int start_time = millis();
	do {
		if (side == 'L') {
			enc_target = getEncVal(dist); // get target value for encoders
			enc = md->encoder2();
			calculatePid(enc, enc_target);
			spd1 = round((PID_speed_limited - 128) * speed_ratio) + 128;
			spd2 = PID_speed_limited;
		}
		else {
			enc_target = getEncVal(dist); // get target value for encoders
			enc = md->encoder1();
			calculatePid(enc, enc_target);
			spd1 = PID_speed_limited;
			spd2 = round((PID_speed_limited - 128) * speed_ratio) + 128;
		}
		md->setSpeed(spd1, spd2);
	} while((abs(enc) + 1 < abs(enc_target)) && ((millis() - start_time) < timeout));
// md->stopMotors();
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

int Driver::getSpeedTurn(int speed) {
	if (speed >= 255 - limit_cor_turn) {
		return (255 - limit_cor_turn);
	}
	if (speed <= 0 + limit_cor_turn) {
		return (0 + limit_cor_turn);
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

void Driver::calculatePidTurn(int enc_val_cur, int target_val) {
	error = target_val - enc_val_cur;
	P = error; // proportional
	I = I + error; // integral
	D = error - previous_error; // derivative
	PID_val = (Kp_t*P) + (Ki_t*I) + (Kd_t*D); // not sure about the sign after 128
	PID_speed_theor = 128 + int(PID_val);
	PID_speed_limited = getSpeedTurn(PID_speed_theor);
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

