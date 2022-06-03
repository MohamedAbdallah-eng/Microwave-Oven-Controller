#include "TM4C123.h"
#include "tm4c123gh6pm.h"
#include "ButtonH.h"

void TIMER_INIT(void) //call this function to intialize the timer
{
NVIC_ST_CTRL_R = 0; // 1) disable SysTick during setup
NVIC_ST_RELOAD_R = 0x00FFFFFF ; // 2) maximum reload value
NVIC_ST_CURRENT_R = 0; // 3) any write to cURRENT clears it
NVIC_ST_CTRL_R = 0x00000005; // 4) enable SysTick with core clock
}
	
void TIMERCOUNTER_xHZ(unsigned long delay) // you will never call this function we use in implementation of other functions
{
	NVIC_ST_CTRL_R =0;
	NVIC_ST_RELOAD_R= delay-1;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R=0x5;
  while ((NVIC_ST_CTRL_R & 0x00010000 )==0);	
}
void TIMER_MS(unsigned long times)//call it to wait "X" ms send X as argument with the amount of MS you want to wait
{
	int i;
	for(i=0; i<times;i++)
	{
		TIMERCOUNTER_xHZ(16000);
	}
}
void TIMER_SEC(unsigned long times)//call it to wait "X" second send X as argument with the amount of seconds you want to wait
{
	int i;
	for(i=0; i<times;i++)
	{
		TIMER_MS(1000);
	}
}

void TIMER_uS(unsigned long times)//call it to wait "X" us send X as argument with the amount of MS you want to wait
{
	int i;
	for(i=0; i<times;i++)
	{
		TIMERCOUNTER_xHZ(16);
	}
}

void TIMERCOUNTER_xHZ2(unsigned long delay) // you will never call this function we use in implementation of other functions
{
	NVIC_ST_CTRL_R =0;
	NVIC_ST_RELOAD_R= delay-1;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R=0x5;
  while ((NVIC_ST_CTRL_R & 0x00010000 )==0 && (BUTTON_u8READ('F',4) == 1) && (BUTTON_u8READ('D',2) == 1));	//sw1 & sw3
}

void TIMER_MS2(unsigned long times)//call it to wait "X" ms send X as argument with the amount of MS you want to wait
{
	int i;
	for(i=0; i<times;i++)
	{
		TIMERCOUNTER_xHZ2(16000);
		if(BUTTON_u8READ('F',4) == 0)
		{
			break;
		}
	}
}
void TIMER_SEC2(unsigned long times)//call it to wait "X" second send X as argument with the amount of seconds you want to wait
{
	int i;
	for(i=0; i<times;i++)
	{
		TIMER_MS2(1000);
	}
}

void TIMER_uS2(unsigned long times)//call it to wait "X" us send X as argument with the amount of MS you want to wait
{
	int i;
	for(i=0; i<times;i++)
	{
		TIMERCOUNTER_xHZ2(16);
	}
}
