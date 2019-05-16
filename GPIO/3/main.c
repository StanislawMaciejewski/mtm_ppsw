#include <LPC21xx.H>

int main ()
{
IO1DIR = 0x10000;

while (1) 
	{
		IO1SET = 0x10000;
		IO1CLR = 0x10000;
	}
}
