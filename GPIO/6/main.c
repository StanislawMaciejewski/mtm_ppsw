#include <LPC21xx.H>

int i, iTime_ms;
void Delay(iTime_ms)
	{
		for ( i=0; i<iTime_ms*2400; i++) {}
	}
	
int main ()
{
IO1DIR = 0x10000;

while (1) 
	{
		IO1SET = 0x10000;
		Delay(17);
		IO1CLR = 0x10000;
	}
}
