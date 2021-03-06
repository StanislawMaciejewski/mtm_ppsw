#include <LPC21xx.H>
#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19
#define S0_bm 1<<4
#define S1_bm 1<<6
#define S2_bm 1<<5
#define S3_bm 1<<7

enum ButtonState {RELASED, PRESSED};

int i;
unsigned char ucLedNumber;

void Delay(int iTime_ms)
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
	
enum ButtonState ReadButton1()
	{
		if ((IO0PIN & S0_bm) != 0 )
		{
			return RELASED;
		}
		else return PRESSED;
	}
	
void KeyboardInit ()
	{
		IO0DIR = (IO0DIR & ~(S0_bm | S1_bm | S2_bm | S3_bm));
	}
	
int main ()
{
	
	switch (ReadButton1())
		{
			case PRESSED:
				LedOn(0);
			case RELASED:
				break;
		}
		
	KeyboardInit ();
		
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
