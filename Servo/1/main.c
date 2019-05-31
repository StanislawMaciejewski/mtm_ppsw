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

void Automat(void)
{
		enum LedState{STATE_LEFT, STATE_STOP, STATE_RIGHT, CALLIB};
		enum LedState eLedState = STATE_STOP;
	
		KeyboardInit ();
		LedInit();
		
		switch (eLedState)
		{
			case CALLIB:
				if(eReadDetector() == INACTIVE)
				{
					LedStepRight();
				}
				else
				{
					LedStepLeft();
				}
				break;
			
			case STATE_RIGHT:
				if(eKeyboardRead()==BUTTON_1)
				{
					eLedState = STATE_STOP;
				}
				else
				{
					LedStepRight();
				}
				break;
				
			case STATE_LEFT:
				if(eKeyboardRead()==BUTTON_1)
				{
					eLedState = STATE_STOP;
				}
				else
				{
					LedStepLeft();
				}
				break;
			
			case STATE_STOP:
				if(eKeyboardRead()==BUTTON_0)
				{
					eLedState = STATE_LEFT;
				}
				else if(eKeyboardRead()==BUTTON_2)
				{
					eLedState = STATE_RIGHT;
				}

			default:
				break;
		}
	
}

int main (){
	unsigned int iMainLoopCtr;
	
	LedInit();
	Timer0Interrupts_Init(200000, &Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
