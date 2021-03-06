#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  led1,           sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           claw1,         tmotorVex393_HBridge, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port2,           lift1,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           lift2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_2)
#pragma config(Motor,  port6,            ,             tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port7,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           lift3,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port10,          claw2,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "tasks.h"

int count = 0;
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
string bat1, bat2;

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

while(nLCDButtons != centerButton)
{
	switch(count)
	{
	case 0:

	displayLCDCenteredString(0, "Left Auton");
	displayLCDCenteredString(1, "<   Enter   >");
	waitForPress();

		if(nLCDButtons == leftButton)
		{
			waitForRelease();
			count = 2;
		}
		else if (nLCDButtons == rightButton)
		{
			waitForRelease();
			count = 1;
		}
		break;


		case 1:

		displayLCDCenteredString(0, "Right Auton");
		displayLCDCenteredString(1, "<   Enter   >");

		if(nLCDButtons == leftButton)
		{
			waitForRelease();
			count = 0;
		}
		else if (nLCDButtons == rightButton)
		{
			waitForRelease();
			count = 2;
		}
		break;


		case 2:

		displayLCDString(0, 0, "Primary: ");
		sprintf(bat1, "%1.2f%c", nImmediateBatteryLevel/1000.0, 'v');
		displayNextLCDString(bat1);

		displayLCDString(1, 0, "Backup: ");
		sprintf(bat2, "%1.2f%c", BackupBatteryLevel/1000.0, 'v');
		displayNextLCDString(bat2);

		if(nLCDButtons == leftButton)
		{
			waitForRelease();
			count = 1;
		}
		else if (nLCDButtons == rightButton)
		{
			waitForRelease();
			count = 0;
		}
		break;

		if(nLCDButtons == centerButton)
		{return;}

}


}
}



task autonomous()
{

	switch(count)
	{
		case 0:
resetMotorEncoder(lift1);
resetMotorEncoder(rightMotor);
resetMotorEncoder(leftMotor);

motor[lift1] = motor[lift2] = -20;

move(24, 1);

claw(1500, 1);
motor[claw1] = motor[claw2] = 20;
lift(45);

while(nMotorEncoder(rightMotor) > -575*3/5)
{
	motor[rightMotor] = -127;
}
motor[leftMotor] = motor[rightMotor] = 0;

lift(95);

move(-9, -1);

motor[lift1] = motor[lift2] = 127;
claw(300, -1);
motor[lift1] = motor[lift2] = 0;
wait1Msec(500);

lift(95);

resetMotorEncoder(leftMotor);
while(nMotorEncoder(leftMotor) < 1500*3/5)
{
	motor[leftMotor] = 127;
}
motor[leftMotor] = 0;

claw(150, -0.5);

move(10, 1);

break;

case 1:
resetMotorEncoder(lift1);
resetMotorEncoder(rightMotor);
resetMotorEncoder(leftMotor);

motor[lift1] = motor[lift2] = -20;

move(24, 1);

claw(1500, 1);
motor[claw1] = motor[claw2] = 20;
lift(45);

while(nMotorEncoder(leftMotor) > -575*3/5)
{
	motor[leftMotor] = -127;
}
motor[leftMotor] = motor[rightMotor] = 0;

lift(95);

move(-9, -1);

motor[lift1] = motor[lift2] = 127;
claw(300, -1);
motor[lift1] = motor[lift2] = 0;
wait1Msec(500);

lift(95);

resetMotorEncoder(rightMotor);
while(nMotorEncoder(rightMotor) < 1500*3/5)
{
	motor[rightMotor] = 127;
}
motor[rightMotor] = 0;

claw(150, -0.5);

move(10, 1);
	break;

	default:
	break;
		}

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop
resetMotorEncoder(lift1);
	while (true)
	{
		int leftstick = vexRT[Ch3];
		int rightstick = vexRT[Ch2];
		int liftbuttonU = vexRT[Btn6U];
		int liftbuttonD = vexRT[Btn6D];
		int clawopen = vexRT[Btn5U];
		int clawclose = vexRT[Btn5D];
		int stayinAlive = vexRT[Btn8D];
		string bat1, bat2;

		if(stayinAlive == 1)
			{
				playSoundFile("1.wav");
				wait1Msec(100);
			}


		//left motor control
		if (leftstick > 10 || leftstick < -10){
			motor [leftMotor] = leftstick;
			//			motor [leftMotorB] = leftstick;
		}
		else
			motor [leftMotor] = 0;
		//			motor [leftMotorB] = 0;

		//right motor control
		if (rightstick > 10 || rightstick <-10){
			motor [rightMotor] = rightstick;
			//			motor [rightMotorB] = rightstick;
		}
		else
			motor [rightMotor] = 0;
		//			motor [rightMotorB] = 0;

		//Lift control
		if (liftbuttonU == 1)
		{
			motor [lift1] = motor [lift2] = motor[lift3] =  127;
		}
		else if (liftbuttonD == 1)
		{
			motor [lift1] = motor [lift2] = motor [lift3] = -127;
		}	else 	{
				motor [lift1] = -10;
				motor [lift2] = -10;
				motor [lift3] =  10;
		}


		//Claw control
		if (clawopen == 1){
			motor [claw1] = 127;
			motor [claw2] = 127;
		}
		else if (clawclose == 1){
			motor [claw1] = -127;
			motor [claw2] = -127;
		}
		else
			{
			motor [claw1] = 10;
			motor [claw2] = -10;
			}

					clearLCDLine(0);
		clearLCDLine(1);

		displayLCDString(0, 0, "Primary: ");
		sprintf(bat1, "%1.2f%c", nImmediateBatteryLevel/1000.0, 'v');
		displayNextLCDString(bat1);

		displayLCDString(1, 0, "Backup: ");
		sprintf(bat2, "%1.2f%c", BackupBatteryLevel/1000.0, 'v');
		displayNextLCDString(bat2);

	}

}
