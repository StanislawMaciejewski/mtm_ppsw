#include <LPC21xx.H>

int i;
void Delay()
	{
		for ( i=0; i<2000000; i++) {}
	}
	
int main ()
{
IO1DIR = 0x10000;

while (1) 
	{
		IO1SET = 0x10000;
		Delay();
		IO1CLR = 0x10000;
	}
}
