#include "led.h"//GITTEST
#include "keyboard.h"
#define CounterMax 7510


void Delay(unsigned int uiDelayValue){
	unsigned int uiCounter;
	unsigned int uiCounter2;
	for(uiCounter=0; uiCounter<=uiDelayValue; uiCounter++){
		for(uiCounter2=0; uiCounter2<CounterMax; uiCounter2++){}
	}
	
}


int main(){
	LedInit();//afbajbh
	KeyboardInit();//sdjhbfjksbh

	
	while(1){
		
		switch (eKeyboardRead())
		{
			case BUTTON_0:
				break;
			
			case BUTTON_1:
				LedStep(RIGHT);
				break;
			
			case BUTTON_2:
				LedStep(LEFT);
				break;
			
			case BUTTON_3:
				break;
			
			case RELASED:
				break;
			
			default:
				break;
		}
		Delay(100);
	}		
}//GITTEST

