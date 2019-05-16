#include <LPC21xx.H>
#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19

int i, iTime_ms;
unsigned char ucLedNumber;

void Delay(iTime_ms)
	{
		for ( i=0; i<iTime_ms*2400; i++) {}
	}
	
void vLedInit ( )
	{
		IO1DIR = (IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm);
		IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
		IO1SET = LED0_bm;
	}
	
void LedOn (unsigned char ucLedIndeks)
	{
		IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
		switch (ucLedIndeks)
		{
			case 0:
				IO1SET = LED0_bm;
				break;
			
			case 1:
				IO1SET = LED1_bm;
				break;
			
			case 2:
				IO1SET = LED2_bm;
				break;
			
			case 3:
				IO1SET = LED3_bm;
				break;
		}
	}
	
int main ()
{
	
while (1) 
	{
	vLedInit();
	Delay(250);
	
	LedOn (1);
	Delay(250);
		
	LedOn (2);
	Delay(250);
		
	LedOn (3);
	Delay(250);
	
	}
}
