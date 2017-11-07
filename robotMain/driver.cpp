/* This library was created by Daniel Hausner in Nov 2017 for odometry assignment
 * at University of Southampton
 * dh4n16@soton.ac.uk
 */


#include "driver.h" //include the declaration for this class

Driver::Driver(float p, float i, float d){ // constructor, PID constants
	
}

//turn the LED on
void LED::on(){
	digitalWrite(_pin,HIGH); //set the pin HIGH and thus turn LED on
}

//turn the LED off
void LED::off(){
	digitalWrite(_pin,LOW); //set the pin LOW and thus turn LED off
}

//blink the LED in a period equal to paramterer time.
void LED::blink(int time){
	on(); 			//turn LED on
	delay(time/2);  //wait half of the wanted period
	off();			//turn LED off
	delay(time/2);  //wait the last half of the wanted period
}
