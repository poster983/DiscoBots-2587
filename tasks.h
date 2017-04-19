//starts extened code
#ifndef tasks
#define tasks

void move(int dist, int dir)
{
resetMotorEncoder(rightMotor);
resetMotorEncoder(leftMotor);

		dist = dist*627/12.5*3/5;
if(dir > 0){
	while(nMotorEncoder[rightMotor] < dist)
	{
		motor[rightMotor] = motor[leftMotor] = 127;
	}
} else if(dir < 0){
		while(nMotorEncoder[rightMotor] > dist)
	{
		motor[rightMotor] = motor[leftMotor] = -127;
	}
}
		motor[rightMotor] = motor[leftMotor] = 0;
}

void lift(int deg)
{
	deg = deg*5*627/360;
	if (nMotorEncoder[lift1] > deg)
	{
		while (nMotorEncoder[lift1] > deg)
		{
			motor[lift1] = motor[lift2] = -127;
		}
	} else if (nMotorEncoder[lift1] < deg)
	{
		while (nMotorEncoder[lift1] < deg)
		{
			motor[lift1] = motor[lift2] =  127;
		}
	}

	motor[lift1] = -10;
	motor[lift2] = 10;
}

void claw(int time, int dir)
{
	motor[claw1] = motor[claw2] = dir*127;
	wait1Msec(time);

	motor[claw1] = motor[claw2] = 0;
}
//------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//-------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}

#endif //ends extended code
