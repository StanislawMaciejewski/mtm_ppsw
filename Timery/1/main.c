#include "led.h"
#include "keyboard.h"
#include "timer.h"

int main(){
	LedInit();

		InitTimer0();
		WaitOnTimer0(100);
	
		
		while(1)
		{
			LedStep(LEFT);
		}
	
}

