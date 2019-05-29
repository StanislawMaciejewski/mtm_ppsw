#include "led.h"
#include "keyboard.h"
#include "timer.h"

int main(){
	LedInit();
		
	while(1)
	{
		InitTimer0Match0(100000);
		LedStep(LEFT);
		WaitOnTimer0Match0();
	}
			
}
