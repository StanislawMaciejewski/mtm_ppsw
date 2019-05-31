#include <LPC21xx.H>
#include "led.h"
#include "servo.h"
#include "timer_interrupts.h"

#define DETECTOR_bm (1<<10)

void DetectorInit(void)
{
	IO0DIR = IO0DIR & (~DETECTOR_bm);
}

enum DetectorState eReadDetector(void)
{
	if((IO0PIN & DETECTOR_bm) == 0)
	{
		if ((IO0PIN & DETECTOR_bm) == 0)
		{
			return ACTIVE;
		}
	}
	return INACTIVE;
}

struct Servo sServo;

void ServoInit(unsigned int uiServoFrequency)
{
	LedInit();
	DetectorInit();
	Timer0Interrupts_Init((1000000/uiServoFrequency), &Automat);
	ServoCallib();
}

void ServoCallib(void)
{
	sServo.eState = CALLIB;
}


void ServoGoTo(void)
{
	sServo.uiDesiredPosition = uiPosition;
}


void Automat(void)
{
		switch (sServo.eState)
		{
			case CALLIB:
				if(eReadDetector() == INACTIVE)
				{
					LedStepRight();
				}
				else
				{
					LedStepRight();
					sServo.eState = IDLE;
					sServo.uiCurrentPosition = 0;
					sServo.uiDesiredPosition = 0;
				}
				break;
			
			case IDLE:
				if(sServo.uiCurrentPosition != sServo.uiDesiredPosition)
				{
					sServo.eState = IN_PROGRESS;
				}
				else
				{
					sServo.eState = IDLE;
				}
				break;
				
			case IN_PROGRESS:
				if(sServo.uiDesiredPosition > sServo.uiCurrentPosition))
				{
					LedStepRight();
					sServo.uiCurrentPosition++;
				}
				else if(sServo.uiDesiredPosition < sServo.uiCurrent)
				{
					LedStepLeft();
					sServo.uiCurrentPosition--;
				}
				else
				{
					sServo.eState = IDLE;
				}
				break;

			default:
				break;
		}
	
}