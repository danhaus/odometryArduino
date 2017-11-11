/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */


#include "button.h" //include the declaration for this class

Button::Button(byte pin){ // constructor
	_pin = pin; // set pin
	pinMode(_pin, INPUT); //make _pin an OUTPUT
}

//turn the button on
bool Button::state() {
	if (digitalRead(_pin) == 1) {
		return true;
	}
	return false;
}
