# odometryArduino
## Description
This is an Arduino code for an odometry robot. It uses MD25 motor driver with EMG30 motors for driving and getting the position, and 9g servo for releasing M&Ms. There are no other sensors. The driving logic is implemented using PID control. It drives on a path composed of straight and circular sections. The robot also drops M&Ms at five places marked on a track.

## Usage
There are two main files, one drives the robot slowly, the other is faster. These are inside robotMain_slowWorking and robotMain_turboRocket respectively. There is a voltage check in the code that does not let you to drive the motors if the battery voltage is under 12 V. The code in both robotMain_slowWorking and robotMain_turboRocket initialise itself and then it waits for a button to be pressed to start driving.
