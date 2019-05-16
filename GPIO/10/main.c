#include <LPC21xx.H>
#define LED3_bm 1<<19
#define LED0_bm 1<<16

int i, iTime_ms;
void Delay(iTime_ms)
	{
		for ( i=0; i<iTime_ms*2400; i++) {}
	}
	
int main ()
{
IO1DIR = LED0_bm;

while (1) 
	{
		IO1SET = LED3_bm;
		Delay(100);
		IO1CLR = LED3_bm;
		Delay(100);
	}
}
