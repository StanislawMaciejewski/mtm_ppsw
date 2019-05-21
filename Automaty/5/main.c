#include "led.h"
#include "keyboard.h"
#define CounterMax 7510

void Delay(unsigned int uiDelayValue){
	unsigned int uiCounter;
	unsigned int uiCounter2;
	for(uiCounter=0; uiCounter<=uiDelayValue; uiCounter++){
		for(uiCounter2=0; uiCounter2<CounterMax; uiCounter2++){}
	}
	
}

int main ()
{
		enum LedState{STATE_START, STATE_STOP};
		enum LedState eLedState = STATE_STOP;

	
		KeyboardInit ();
		LedInit();
		
while (1) 
	{
		switch (eLedState)
		{
			case STATE_START:
				if(eKeyboardRead()==BUTTON_0)
				{
					eLedState = STATE_STOP;
				}
				else
				{
					LedStep(RIGHT);
				}
				break;
			
			case STATE_STOP:
				if(eKeyboardRead()==BUTTON_1)
				{
					eLedState = STATE_START;
				}
				break;
			
			default:
				break;
		}
		Delay(500);
	}
}
