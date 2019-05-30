#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

void Automat(void)
{
		enum LedState{STATE_LEFT, STATE_STOP, STATE_RIGHT};
		enum LedState eLedState = STATE_STOP; // static??
	
		KeyboardInit ();
		LedInit();
		
		switch (eLedState)
		{
			case STATE_RIGHT:
				if(eKeyboardRead()==BUTTON_1)
				{
					eLedState = STATE_STOP;
				}
				else
				{
					LedStep(RIGHT);
				}
				break;
				
			case STATE_LEFT:
				if(eKeyboardRead()==BUTTON_1)
				{
					eLedState = STATE_STOP;
				}
				else
				{
					LedStep(LEFT);
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
	Timer0Interrupts_Init(2000, &Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
