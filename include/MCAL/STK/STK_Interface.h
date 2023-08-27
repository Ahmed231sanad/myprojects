/*
 * STK_Interface.h
 *
 *  Created on: AUG 11, 2023
 *      Author: Ahmed Sanad
 */

#ifndef STK_INTERFACE_H_
#define STK_INTERFACE_H_

#define AHB 		  0
#define AHB_DIV_BY_8  1

#define STK_DISABLE   0
#define STK_ENABLE    1

typedef enum{
	STK_AHB_DIV_BY_8=0,
	STK_AHB
}StkClockSource_e;


void MSTK_voidSetIntervalPeriodic (void (*pf)(void),u32 A_u32Ticks);
void MSTK_voidSetIntervalSingle (void (*pf)(void),u32 A_u32Ticks);
void MSTK_voidSetBusyWait (u32 A_u32TickstToWait);
void MSTK_voidResetSystick ();
void MSTK_voidSetPreloadValue (u32 A_u32PreloadValue);
u32 MSTK_u32GetRemainingTime ();
u32 MSTK_u32GetElapsedTime ();
void MSTK_voidSetClkSource (StkClockSource_e A_clkSource);
void MSTK_voidDisable ();
void MSTK_voidEnable ();
void MSTK_voidInit ();
#endif /* STK_INTERFACE_H_ */
