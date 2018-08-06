# odometryArduino
## Description
This is an Arduino code for an odometry robot. It uses MD25 motor driver with EMG30 motors for driving and getting the position, and 9g servo for releasing M&Ms. There are no other sensors. The driving logic is implemented using PID control. It drives on a path composed of straight and circular sections. The robot also drops M&Ms at five places marked on a track.

## Usage
The main file is robot_main/robot_main.ino. There is a voltage check in the code that does not let you to drive the motors if the battery voltage is under 12 V. The main code initialise itself and then it waits for a button to be pressed to start driving.
