/*

 * EXTI_Program.c
 *
 *
 *
 */
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/LIB.h"

#include "../include/MCAL/RCC/RCC_interface.h"

#include "../include/MCAL/GPIO/GPIO_interface.h"

#include "../include/MCAL/EXTI/EXTI_interface.h"
#include "../include/MCAL/EXTI/EXTI_private.h"
#include "../include/MCAL/EXTI/EXTI_configuration.h"

void (*EXTI0_callBack)(void);
void MEXTI_voidConfig (EXTI_LINES_e A_EXTILine, GPIO_t  *A_GPIOx, SENSE_CONTROL_e A_SenseMode)
{
	// SYSCFG to set Line For EXTI
	if (A_GPIOx == GPIOA)
	{
		switch (A_EXTILine)
		{
		case EXTI0 :
		case EXTI1 :
		case EXTI2 :
		case EXTI3 :
			SYSCFG -> EXTICR1 &= ~(15 << (A_EXTILine * 4)); break;
		case EXTI4 :
		case EXTI5 :
		case EXTI6 :
		case EXTI7 :
			SYSCFG -> EXTICR2 &= ~(15 << (A_EXTILine * 4)); break;
		case EXTI8 :
		case EXTI9 :
		case EXTI10:
		case EXTI11:
			SYSCFG -> EXTICR3 &= ~(15 << (A_EXTILine * 4)); break;
		case EXTI12:
		case EXTI13:
		case EXTI14:
		case EXTI15:
			SYSCFG -> EXTICR4 &= ~(15 << (A_EXTILine * 4)); break;
		}
	}
	else if (A_GPIOx == GPIOB)
	{
		switch (A_EXTILine)
		{
		// EXTIO...EXTI3
		case EXTI0 :
		case EXTI1 :
		case EXTI2 :
		case EXTI3 :
			SYSCFG -> EXTICR1 &= ~(15 << (A_EXTILine * 4));
			SYSCFG -> EXTICR1 |= (1 << (A_EXTILine * 4));
			break;
		case EXTI4 :
		case EXTI5 :
		case EXTI6 :
		case EXTI7 :
			SYSCFG -> EXTICR2 &= ~(15 << (A_EXTILine * 4));
			SYSCFG -> EXTICR2 |= (1 << (A_EXTILine * 4));
			break;
		case EXTI8 :
		case EXTI9 :
		case EXTI10:
		case EXTI11:
			SYSCFG -> EXTICR3 &= ~(15 << (A_EXTILine * 4));
			SYSCFG -> EXTICR3 |= (1 << (A_EXTILine * 4));
			break;
		case EXTI12:
		case EXTI13:
		case EXTI14:
		case EXTI15:
			SYSCFG -> EXTICR4 &= ~(15 << (A_EXTILine * 4));
			SYSCFG -> EXTICR4 |= (1 << (A_EXTILine * 4));
			break;
		}
	}
	else
	{

	}

	// Set Sense Control
	switch (A_SenseMode)
	{
	case FALLING_EDGE:
		SET_BIT(EXTI->FTSR,A_EXTILine);
		CLR_BIT(EXTI->RTSR,A_EXTILine);
		break;
	case RISING_EDGE:
		CLR_BIT(EXTI->FTSR,A_EXTILine);
		SET_BIT(EXTI->RTSR,A_EXTILine);
		break;
	case ON_CHANGE:
		SET_BIT(EXTI->FTSR,A_EXTILine);
		SET_BIT(EXTI->RTSR,A_EXTILine);
		break;
	}

	// Enable EXTI Line
	SET_BIT(EXTI->IMR,A_EXTILine);

}

void MEXTI_voidSetCallBack (void(*A_ptrToFunc)(void))
{
	if (A_ptrToFunc != NULL)
	{
		EXTI0_callBack = A_ptrToFunc;
	}
}
void MEXTI_voidDisable (EXTI_LINES_e A_EXTILine)
{
	CLR_BIT(EXTI->IMR,A_EXTILine);
}


void EXTI0_IRQHandler(void)
{
	if (EXTI0_callBack != NULL)
	{
		EXTI0_callBack();
	}
	SET_BIT(EXTI->PR,0);
}






