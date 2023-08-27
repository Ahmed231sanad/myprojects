/*

 * STK_Program.c
 *
 *  Created on: 11/8/2023
 *      Author: Ahmed sanad
 */

 #include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/LIB.h"

#include "../include/MCAL/STK/STK_interface.h"
#include "../include/MCAL/STK/STK_Private.h"
#include "../include/MCAL/STK/STK_Config.h"



void MSTK_voidInit ()
{
  #if STK_CLK_SOURCE == AHB
	SET_BIT(STK->CTRL,2);
  #elif STK_CLK_SOURCE == AHB_DIV_BY_8
	CLR_BIT(STK->CTRL,2);
  #else
     #error "STK Clock Configuration ERROR"
  #endif

  #if STK_INTERRUPT == STK_ENABLE
	SET_BIT(STK->CTRL,1);
  #elif STK_INTERRUPT == STK_DISABLE
	CLR_BIT(STK->CTRL,1);
  #else
     #error "STK Interrupt Configuration ERROR"
  #endif

	// Disable SYSTICK
	CLR_BIT(STK->CTRL,0);
}

void MSTK_voidEnable ()
{
	SET_BIT(STK->CTRL,0);
}

void MSTK_voidDisable ()
{
	CLR_BIT(STK->CTRL,0);
}


void MSTK_voidSetClkSource (StkClockSource_e A_clkSource)
{
	switch (A_clkSource)
	{
	case STK_AHB         : SET_BIT(STK->CTRL,2); break;
	case STK_AHB_DIV_BY_8: CLR_BIT(STK->CTRL,2); break;
	}
}

u32 MSTK_u32GetElapsedTime ()
{
	u32 local_u32ElapsedTime = STK->LOAD - STK->VAL;
	return local_u32ElapsedTime;
}

u32 MSTK_u32GetRemainingTime ()
{
	return STK->VAL;
}
void MSTK_voidSetPreloadValue (u32 A_u32PreloadValue)
{
	STK->LOAD = A_u32PreloadValue;
}

void MSTK_voidResetSystick ()
{
	STK->VAL = 0;
}

void MSTK_voidSetBusyWait (u32 A_u32TickstToWait)
{
	STK->LOAD = A_u32TickstToWait;
	STK->VAL = 0;
	SET_BIT(STK->CTRL,0);
	while (GET_BIT(STK->CTRL,16)==0);
	CLR_BIT(STK->CTRL,0);
	STK->VAL = 0;
}


void MSTK_voidSetIntervalSingle (void (*pf)(void),u32 A_u32Ticks)
{
	global_IntervalType = SINGLE_INTERVAL;
	pvCallBack = pf;
	STK->LOAD = A_u32Ticks;
	STK->VAL = 0;
	SET_BIT(STK->CTRL,1);
	SET_BIT(STK->CTRL,0);
}

void MSTK_voidSetIntervalPeriodic (void (*pf)(void),u32 A_u32Ticks)
{
	global_IntervalType = PERIODIC_INTERVAL;
	pvCallBack = pf;
	STK->LOAD = A_u32Ticks;
	STK->VAL = 0;
	SET_BIT(STK->CTRL,1);
	SET_BIT(STK->CTRL,0);
}



void SysTick_Handler ()
{
	u8 local_u8Flag;
	if (global_IntervalType == SINGLE_INTERVAL)
	{
		CLR_BIT(STK->CTRL,0);
		STK->VAL = 0;
		STK->LOAD = 0;
	}

	if (pvCallBack != NULL)
	{
		pvCallBack();
	}
	local_u8Flag = GET_BIT(STK->CTRL,16);
}

