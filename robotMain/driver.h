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
	void on(); // switch on
	void off(); // switch off
	void blink(int time); // blink with period of time
private:
};

#endif
