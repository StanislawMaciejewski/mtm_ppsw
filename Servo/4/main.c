#include "led.h"
#include "keyboard.h"
#include "servo.h"
#include "timer_interrupts.h"

int main (){
	//unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	ServoInit(50);
	//Timer0Interrupts_Init(200000, &Automat);

	while(1){
	 	switch(eKeyboardRead())
		{
			case BUTTON_0:
				ServoCallib();
				break;
			
			case BUTTON_1:
				ServoGoTo(12);
				break;
			
			case BUTTON_2:
				ServoGoTo(24);
				break;
			
			case BUTTON_3:
				ServoGoTo(36);
				break;
			
			default:
				break;
		}
	}
}
