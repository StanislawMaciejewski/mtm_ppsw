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
	
		enum LedState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
		enum LedState eLedState = STATE0;

		KeyboardInit ();
		LedInit();
	
		
while (1) 
	{
		switch (eLedState)
		{
			case STATE0:
				eLedState = STATE1;
				LedStep(RIGHT);
				break;
			
			case STATE1:
				eLedState = STATE2;
				LedStep(RIGHT);
				break;
			
			case STATE2:
				eLedState = STATE3;
				LedStep(RIGHT);
				break;
			
			case STATE3:
				eLedState = STATE4;
				LedStep(LEFT);
				break;
			
			case STATE4:
				eLedState = STATE5;
				LedStep(LEFT);
				break;
			
			case STATE5:
				eLedState = STATE0;
				LedStep(LEFT);
				break;
			
			default:
				break;
		}
		Delay(500);
	}
}
