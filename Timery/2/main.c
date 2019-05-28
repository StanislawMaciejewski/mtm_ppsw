#include "led.h"
#include "keyboard.h"
#include "timer.h"

int main(){
	LedInit();
	InitTimer0Match0(1000);
		
	while(1)
	{
		LedStep(LEFT);
		WaitOnTimer0Match0();
	}
			
}
