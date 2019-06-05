#include "led.h"
#include "keyboard.h"
#include "servo.h"
#include "timer_interrupts.h"

int main (){
	
	KeyboardInit();
	ServoInit(50);
//	if(eReadDetector()==ACTIVE){
//		ServoGoTo(48);
//	}
	//ServoGoTo(24);
	//ServoGoTo(12);


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
