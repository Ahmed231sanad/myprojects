/*

 * Led_Matrix_Program.c
 *
 *
 *
 */
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/LIB.h"

#include "../include/MCAL/GPIO/GPIO_interface.h"
// To Make Delay
#include "../include/MCAL/STk/STK_interface.h"

#include "../include/HAL/Led_Matrix/Led_Matrix_interface.h"
#include "../include/HAL/Led_Matrix/Led_Matrix_Private.h"
#include "../include/HAL/Led_Matrix/Led_Matrix._config.h"

void HLEDMX_voidDisableAllCol (void)
{
	for (u8 i =0; i<8; i++)
	{
		GPIO_WritePin(GPIOB, i, GPIO_SET);
	}
}

void HLEDMX_voidSetRowValue (u8 A_u8Value)
{
	u8 local_u8RowValue;

	local_u8RowValue = GET_BIT(A_u8Value,0);
	GPIO_WritePin(LEDMX_R0, local_u8RowValue);

	local_u8RowValue = GET_BIT(A_u8Value,1);
	GPIO_WritePin(LEDMX_R1, local_u8RowValue);

	local_u8RowValue = GET_BIT(A_u8Value,2);
	GPIO_WritePin(LEDMX_R2, local_u8RowValue);

	local_u8RowValue = GET_BIT(A_u8Value,3);
	GPIO_WritePin(LEDMX_R3, local_u8RowValue);

	local_u8RowValue = GET_BIT(A_u8Value,4);
	GPIO_WritePin(LEDMX_R4, local_u8RowValue);

	local_u8RowValue = GET_BIT(A_u8Value,5);
	GPIO_WritePin(LEDMX_R5, local_u8RowValue);

	local_u8RowValue = GET_BIT(A_u8Value,6);
	GPIO_WritePin(LEDMX_R6, local_u8RowValue);

	local_u8RowValue = GET_BIT(A_u8Value,7);
	GPIO_WritePin(LEDMX_R7, local_u8RowValue);
}

void HLEDMX_voidDisplay (u8 *A_u8arrData)
{
	// Disable All Columns
	HLEDMX_voidDisableAllCol();
	// Set Row Value
	HLEDMX_voidSetRowValue(A_u8arrData[0]);
	// Enable 1 Column
	GPIO_WritePin(LEDMX_C0, GPIO_RESET);
	// Delay
	MSTK_voidSetBusyWait(2500);

	// Disable All Columns
	HLEDMX_voidDisableAllCol();
	// Set Row Value
	HLEDMX_voidSetRowValue(A_u8arrData[1]);
	// Enable 1 Column
	GPIO_WritePin(LEDMX_C1, GPIO_RESET);
	// Delay
	MSTK_voidSetBusyWait(2500);

	// Disable All Columns
	HLEDMX_voidDisableAllCol();
	// Set Row Value
	HLEDMX_voidSetRowValue(A_u8arrData[2]);
	// Enable 1 Column
	GPIO_WritePin(LEDMX_C2, GPIO_RESET);
	// Delay
	MSTK_voidSetBusyWait(2500);

	// Disable All Columns
	HLEDMX_voidDisableAllCol();
	// Set Row Value
	HLEDMX_voidSetRowValue(A_u8arrData[3]);
	// Enable 1 Column
	GPIO_WritePin(LEDMX_C3, GPIO_RESET);
	// Delay
	MSTK_voidSetBusyWait(2500);

	// Disable All Columns
	HLEDMX_voidDisableAllCol();
	// Set Row Value
	HLEDMX_voidSetRowValue(A_u8arrData[4]);
	// Enable 1 Column
	GPIO_WritePin(LEDMX_C4, GPIO_RESET);
	// Delay
	MSTK_voidSetBusyWait(2500);

	// Disable All Columns
	HLEDMX_voidDisableAllCol();
	// Set Row Value
	HLEDMX_voidSetRowValue(A_u8arrData[5]);
	// Enable 1 Column
	GPIO_WritePin(LEDMX_C5, GPIO_RESET);
	// Delay
	MSTK_voidSetBusyWait(2500);

	// Disable All Columns
	HLEDMX_voidDisableAllCol();
	// Set Row Value
	HLEDMX_voidSetRowValue(A_u8arrData[6]);
	// Enable 1 Column
	GPIO_WritePin(LEDMX_C6, GPIO_RESET);
	// Delay
	MSTK_voidSetBusyWait(2500);

	// Disable All Columns
	HLEDMX_voidDisableAllCol();
	// Set Row Value
	HLEDMX_voidSetRowValue(A_u8arrData[7]);
	// Enable 1 Column
	GPIO_WritePin(LEDMX_C7, GPIO_RESET);
	// Delay
	MSTK_voidSetBusyWait(2500);
}




