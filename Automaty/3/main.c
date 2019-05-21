#include "led.h"
#include "keyboard.h"
#define CounterMax 7510

unsigned char ucStateCounter;

void Delay(unsigned int uiDelayValue){
	unsigned int uiCounter;
	unsigned int uiCounter2;
	for(uiCounter=0; uiCounter<=uiDelayValue; uiCounter++){
		for(uiCounter2=0; uiCounter2<CounterMax; uiCounter2++){}
	}
}
	
int main (){
	
		enum LedState{STATE_LEFT, STATE_RIGHT};
		enum LedState eLedState = STATE_LEFT;
	
		KeyboardInit ();
		LedInit();

while (1) 
	{
		ucStateCounter++;
		switch (eLedState)
		{
			case STATE_LEFT:
				if(ucStateCounter>3)
				{
					eLedState = STATE_RIGHT;
					ucStateCounter=0;
				}
				else
				{
					LedStep(LEFT);
				}
				break;
			
			case STATE_RIGHT:
				if(ucStateCounter>3)
				{
					eLedState = STATE_LEFT;
					ucStateCounter=0;
				}
				else
				{
					LedStep(RIGHT);
				}
				break;
			
			default:
				break;
		}
		Delay(500);
	}
}
