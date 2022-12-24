# EMBEDDED_SYSTEMS

## PRESENTATION
Project 1, Software Engineering Bachelor First Year.

RCxD by the 1617 team of the INF1900 course at the Polytechnic School of Montreal.
Version: 1.0
Date: December 7, 2022

Authors:
* ZGHAL Ahmed
* LAHBABI Ryan
* MOUCHAHID Ali
* Evan BLANC

This project was designed as part of the embedded system integrator project of the first year (INF1900) in software and computer engineering at the Polytechnic School of Montreal.

Use:
To use this robot, you need to use the following six instructions:

1. Clean the library:
o In the project/lib folder, use the command:
* make clean
2. Compile the library:
o In the project/lib folder, use the command:
* make
3. Clean the app folder:
o In the project/app folder, use the command:
*make clean*

4. Compile and install the executable on the robot:
o In the project/app folder, use the command:
* make install
o In order to debug, use the command:
* make debug

5. To start the course:
* Choose the desired state using the push button placed on the breadbord.
* Once the LED shows the color of the route requested, press the push button on the motherboard to confirm the choice.

### lib folder
This folder has all the classes to control and manipulate the robot and its peripherals.
Class handling output devices: motor.cpp, del.cpp, sonorite.cpp, usart.cpp, LineSensor.cpp
Class handling input devices: Button.cpp, Interrupt.cpp, can.cpp
  Class handling the external memory of the robot: memoire_24.cpp and loadingMemoireExterne.cpp

### app folder
This folder is the executable of the robot it includes all the files of the library thanks to the edition of the links and compiles the program in the robot.

### Robot.cpp
This file is our main class and it implements the Robot object which controls all the states of the robot by following the different steps. Starting from route A, until parking at its respective location in Route B_S. We find in this file a call to different methods available from the library of the lib folder.

### Material Handling
The robot is programmed on an Atmega324PA microcontroller board. The devices used are a Cytron LSS05 distance sensor to pick up the poles in course A and a GP2D12 line follower to follow a black line for the entire course.

### State Machine

The RCxD is composed of three states: A_VERS_B, B_VERS_S, S_VERS_FIN.

| Current     |State  |Transition Next    |State Output |                                                 
|-------------|-------|-------------------|-------------|
| A_VERS_B    |Push   |Button B_VERS_S    |GREEN LED    |                                                 
| B_VERS_S    |Push   |Button S_VERS_FIN  |RED LED      |                                                 
| S_VERS_FIN  |Push   |Button A_VERS_B    |LED AMBER    | 


## PROJECT STATEMENT
![image](https://user-images.githubusercontent.com/89122986/209289057-4b673f19-c2a6-41d0-a826-b2bf12e24859.png)

<ins> Figure 1: Robot Path Diagram </ins>



Selection of starting point:

The ability to choose a starting point serves two purposes. First, as will be explained later, the robot will have to be reset at point B. After the reset, the robot will therefore have to be told to resume from point B. Second, choosing a starting point allows you to resume part of the game. the test without having to start over from the beginning. However, this is at the discretion of the assessor.

There are three possible starting points for the robot: A, B and S. Each of these points is associated with a color.

A: green

B: red

S: amber

The mechanism for choosing the starting point uses the Interrupt button, the white button (connected to the breadboard) and the Del Libre.

The white button, which must be plugged into the breadboard, allows you to change the selection. Each time the button is pressed, the selection moves to the next point. The alternation is done in a loop. Thus, past the last point (S) the selection returns to the first (A).

The Free LED indicates which point is currently selected. It therefore displays the color associated with the point as listed above.

The Interrupt button is used to confirm the selection. When pressed, the Free LED should flash 4 times per second for two seconds and then turn off. The robot should then follow the path from the selected starting point.

When the robot is powered up or reset, the selection should initially be point A. The Free LED should therefore be lit green.

Placing a robot for the start:

When the robot is placed on the table, it must straddle the segment preceding the start marker. The line follower should be directly over the start marker.




Before starting the test:

The robot is placed at start marker A.

The evaluator chooses a point among {F, G, H, I} and places a pole there.

The evaluator chooses a point among {N, O} and places a pole there.

The evaluator can optionally place a last post on a point chosen among {L, K}.

### Part 1 (from A):

Once the robot is powered on by the evaluator, the latter will select the starting point A. Once running, the robot must detect and remember the location of the poles using its distance sensor. Each time a pole is detected, the robot stops then emits a sound for one second and then continues to move forward. If the pole detected is close to it (points F, H, K, N) the sound emitted must be high-pitched. If the pole is far (points G, I, L, O), the sound must be serious.

When the robot reaches marker B, it stops. The evaluator will then press the reset button to reset the motherboard. He will then make sure that the robot is well placed. That is to say straddling the segment and the nose on the starting point. It will then select starting point B.

### Part 2 (from B):


From marker B, the robot starts moving forward, makes a 90 degree turn at point C, then another at point D. It continues and heads towards the fork at point E where it will have to choose the path free of poles . 

Arrived at J it advances to place its center of rotation vis-à-vis the points K and L. If a pole is on L, it makes a turn of 15 degrees clockwise, pause for a second, makes the opposite turn and continues its path towards M. If a pole is on K instead, it performs the same action sequence, but this time the initial turn is counterclockwise. 

Finally, if there is no post, it does not turn. Instead, it will have to back up 1.5 inches, pause for a second, then start back towards M. At this point, the robot again chooses the path without a pole. At P, the robot continues to Q and makes a 90 degree turn, then another to R and goes to S. When it gets to S, it does not stop and continues with the third part.


### Part 3 (from S):


The robot continues its line following towards the corridor formed by segments UW and VX. When it arrives at the beginning of this corridor, the robot must change its path following mode. Indeed, rather than following a line, he will have to take the corridor and move inside it by “bouncing” from one segment to another.

When the corridor ends, i.e. at point W, the robot must quickly resume normal line following on VX and go to point X.

A hit at X, the robot must immediately perform a maneuver to “park” between the 4 yellow dots. The robot can point either up or down the table. Provided that it is centered as much as possible between the 4 yellow dots.


When the robot is in its final position, it emits a high-pitched one-second sound to indicate that it is finished.
