#include <LPC21xx.H>
#include "timer.h"

#define ENABLE_BM (1<<0)
#define RESET_BM (1<<1)

#define INT_ON_MR0_BM (1<<0)
#define RESET_ON_MR0_BM (1<<1)

#define MR0INT_BM (1<<0)


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
	
	while(T0TC < (uiTime*PCLK))
	{
	}
}

void InitTimer0Match0(unsigned int iDelayTime)
{	
	T0MR0 = iDelayTime * PCLK;
	T0MCR = INT_ON_MR0_BM | RESET_ON_MR0_BM;
	InitTimer0();
}


void WaitOnTimer0Match0()
{	
	while((T0IR & MR0INT_BM) == 0)
	{
	}
	T0IR = MR0INT_BM;
}
