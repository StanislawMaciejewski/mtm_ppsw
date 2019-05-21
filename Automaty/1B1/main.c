#include <LPC21xx.H>
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
		enum LedState{LED_LEFT, LED_RIGHT};
		enum LedState eLedState = LED_LEFT;

	while (1) {
			switch (eLedState)
			{
				case LED_LEFT:
					eLedState = LED_RIGHT;
					break;
			
				case LED_RIGHT:
					eLedState = LED_LEFT;
					break;
			
				default:
					break;
			}
	}
}
