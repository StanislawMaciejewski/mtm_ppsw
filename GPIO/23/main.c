#include <LPC21xx.H>
#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19
#define S0_bm 1<<4
#define S1_bm 1<<6
#define S2_bm 1<<5
#define S3_bm 1<<7

/*enum ButtonState {RELASED, PRESSED};*/
enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};
enum Direction {LEFT, RIGHT};

int i, iLeftStepCounter, iRightStepCounter;
unsigned char ucLedNumber;


void Delay(int iTime_ms)
	{
		for ( i=0; i<iTime_ms*2400; i++) {}
	}
	
void LedInit ( )
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
	
void KeyboardInit ()
	{
		IO0DIR = (IO0DIR & ~(S0_bm | S1_bm | S2_bm | S3_bm));
	}
	
enum KeyboardState eKeyboardRead()
	{
		if ((IO0PIN & S0_bm) == 0)
		{
			return BUTTON_0;
		}
		else if ((IO0PIN & S1_bm) == 0 )
		{
			return BUTTON_1;
		}
		else if ((IO0PIN & S2_bm) == 0 )
		{
			return BUTTON_2;
		}
		else if ((IO0PIN & S3_bm) == 0 )
		{
			return BUTTON_3;
		}
		else 
		{
			return RELASED;
		}
	}
	
void LedStep (enum Direction eDirection)
		{
			static unsigned int uiLedPointer = 0;
			if (eDirection == LEFT)
			{
				uiLedPointer++;
				LedOn(uiLedPointer%4);
			}
			else if (eDirection == RIGHT)
			{
				uiLedPointer = uiLedPointer + 3 ;
				LedOn(uiLedPointer%4);
			}
		}
	
	
int main ()
{
	
	KeyboardInit ();
	
	switch (eKeyboardRead())
		{
			case BUTTON_0:
				LedOn(0);
				break;
			
			case BUTTON_1:
				LedOn(1);	
				break;
			
			case BUTTON_2:
				LedOn(2);
				break;
			
			case BUTTON_3:
				LedOn(3);
				break;
			
			case RELASED:
				LedOn(4);
				break;
		}
		
		LedInit();
		
while (1) 
	{
		for (iLeftStepCounter =0 ; iLeftStepCounter<9; iLeftStepCounter++)
		{
			LedStep(LEFT);
		}
		
		for (iRightStepCounter =0 ; iRightStepCounter<9; iRightStepCounter++)
		{
			LedStep(RIGHT);
		}
	}
}
