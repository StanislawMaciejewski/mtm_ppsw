#include <LPC21xx.H>
#include "timer.h"

#define ENABLE_BM (1<<0)
#define RESET_BM (1<<1)

#define PCLK 15

void InitTimer0(void)
{
	T0TCR = ENABLE_BM | RESET_BM;
	T0TCR = T0TCR & ~RESET_BM;
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR = T0TCR | RESET_BM;
	T0TCR = T0TCR & ~RESET_BM;
	
	while(T0TC < uiTime*PCLK)
	{
	}
}