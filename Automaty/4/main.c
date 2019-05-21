#include "led.h"
#include "keyboard.h"
#define CounterMax 7510

unsigned char ucStepCounter;

void Delay(unsigned int uiDelayValue){
	unsigned int uiCounter;
	unsigned int uiCounter2;
	for(uiCounter=0; uiCounter<=uiDelayValue; uiCounter++){
		for(uiCounter2=0; uiCounter2<CounterMax; uiCounter2++){}
	}
	
}
	
int main ()
{
		enum LedState{STATE_RIGHT, STATE_STOP};
		enum LedState eLedState = STATE_RIGHT;
	
		KeyboardInit ();
		LedInit();
		
while (1) 
	{
		switch (eLedState)
		{
			case STATE_RIGHT:
				if(ucStepCounter>=3)
				{
					eLedState = STATE_STOP;
				}
				else
				{
					ucStepCounter++;
					LedStep(RIGHT);
				}
				break;
			
			case STATE_STOP:
				if(eKeyboardRead()==BUTTON_0)
				{
					eLedState = STATE_RIGHT;
					ucStepCounter=0;
				}
				break;
			
			default:
				break;
		}
		Delay(500);
	}
}
