#include <LPC21xx.H>
#include "timer.h"

#define ENABLE_BM (1<<0)
#define RESET_BM (1<<1)

#define INT_ON_MR0_BM (1<<0)
#define RESET_ON_MR0_BM (1<<1)

#define MR0INT_BM (1<<0)

#define PCLK 15 //15 cykli na 1 us

void InitTimer0(void)
{
		T0TCR = T0TCR | ENABLE_BM; // wlaczenie timera
}

void WaitOnTimer0(unsigned int uiTime)
{
		T0TCR = T0TCR | RESET_BM; // wlaczenie resetu timera
		T0TCR = T0TCR & ~RESET_BM; // wylaczenie resetu timera
	
		while(T0TC != (uiTime*PCLK)) //czekanie na osiagniecie przez timer wartosc podanej w argumencie
		{
		}
}

void InitTimer0Match0(unsigned int iDelayTime)
{	
		T0MR0 = iDelayTime * PCLK; // obliczanie ilosci cykli i wpisanie wartosci do rejestru porownujacego
		T0MCR = INT_ON_MR0_BM | RESET_ON_MR0_BM; // wlaczenie bitow odpowiedzialnych za : resetowanie sie po osignieciu wartosci oraz ustawienie flagi przerwania
		InitTimer0(); // inicjalizacja timera
}


void WaitOnTimer0Match0()
{	
		while((T0IR & MR0INT_BM) == 0) // oczekiwanie na ustawienie flagi przerwania przez uklad porownujacy
		{
		}
		T0IR = MR0INT_BM; // zerowanie flagi przerwania
}
