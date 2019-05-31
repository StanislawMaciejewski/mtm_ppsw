#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

#define DETECTOR_bm (1<<10)

void DetectorInit(void)
{
	IO0DIR = IO0DIR & (~DETECTOR_bm);
}

enum DetectorState {ACTIVE, INACTIVE};

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

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};

struct Servo sServo;

void Automat(void)
{
	
//		enum LedState{STATE_LEFT, STATE_STOP, STATE_RIGHT, CALLIB};
//		enum LedState eLedState = STATE_STOP;
//	
//		KeyboardInit ();
//		LedInit();
		
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

int main (){
	//unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	DetectorInit();
	
	Timer0Interrupts_Init(200000, &Automat);

	while(1){
	 	if(eKeyboardRead() == BUTTON_0)
		{
			sServo.eState = CALLIB;
		}
		else if(eKeyboardRead() == BUTTON_1)
		{
			sServo.uiDesiredPosition = 12;
		}
		else if(eKeyboardRead() == BUTTON_2)
		{
			sServo.uiDesiredPosition = 24;
		}
		else if(eKeyboardRead() == BUTTON_3)
		{
			sServo.uiDesiredPosition = 36;
		}
			
	}
}
