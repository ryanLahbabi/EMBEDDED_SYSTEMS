#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "robot.h"

 int main()
 {
    Robot robot;

    robot.start();
 }