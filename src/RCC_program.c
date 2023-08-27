
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/LIB.h"

#include "../include/MCAL/RCC/RCC_interface.h"
#include "../include/MCAL/RCC/RCC_private.h"
#include "../include/MCAL/RCC/RCC_configuration.h"

void MRCC_voidSetClkStatus (clkSource_e A_ClkSource, clkState_e A_ClkState)
{
	switch (A_ClkSource)
	{
	case HSI:
		switch (A_ClkState)
		{
		case RCC_DISABLE: CLR_BIT(RCC->CR,0); break;
		case RCC_ENABLE : SET_BIT(RCC->CR,0); break;
		default: break;
		}
		break;
	case HSE:
		switch (A_ClkState)
		{
		case RCC_DISABLE: CLR_BIT(RCC->CR,16); break;
		case RCC_ENABLE : SET_BIT(RCC->CR,16); break;
		default: break;
		}
		break;
	case PLL:
		switch (A_ClkState)
		{
		case RCC_DISABLE: CLR_BIT(RCC->CR,24); break;
		case RCC_ENABLE : SET_BIT(RCC->CR,24); break;
		default: break;
		}
		break;
	default: break;
	}
}


clkStatus_e MRCC_GetClkStatus (clkSource_e A_ClkSource)
{
	clkStatus_e local_clkStatus = CLK_NOT_READY;
	switch (A_ClkSource)
	{
	case HSI: local_clkStatus = GET_BIT(RCC->CR,1); break;
	case HSE: local_clkStatus = GET_BIT(RCC->CR,17); break;
	case PLL: local_clkStatus = GET_BIT(RCC->CR,25); break;
	default: local_clkStatus = OUT_OF_RANGE;
	}
	return local_clkStatus;
}

clkStatus_e MRCC_GetClkStatusSyncNonBlocking (clkSource_e A_ClkSource)
{
	clkStatus_e local_clkStatus = CLK_NOT_READY;
	u16 local_u16Counter=0;
	while ((local_clkStatus == CLK_NOT_READY) && (local_u16Counter < RDY_WAIT_TIME))
	{
		local_u16Counter++;
		switch (A_ClkSource)
		{
		case HSI: local_clkStatus = GET_BIT(RCC->CR,1); break;
		case HSE: local_clkStatus = GET_BIT(RCC->CR,17); break;
		case PLL: local_clkStatus = GET_BIT(RCC->CR,25); break;
		default: local_clkStatus = OUT_OF_RANGE;
		}
	}
	return local_clkStatus;
}

clkSource_e MRCC_SetClkSource (clkSource_e A_ClkSource)
{
	switch (A_ClkSource)
	{
	case HSI:
		CLR_BIT (RCC->CFGR,0);
		CLR_BIT (RCC->CFGR,1);
		break;
	case HSE:
		SET_BIT (RCC->CFGR,0);
		CLR_BIT (RCC->CFGR,1);
		break;
	case PLL:
		CLR_BIT (RCC->CFGR,0);
		SET_BIT (RCC->CFGR,1);
		break;
	default: ;
	}
	return ((RCC->CFGR & 0xC) >> 2);
}

clkSource_e MRCC_GetSelectedClkSource (void)
{
	return ((RCC->CFGR & 0xC) >> 2);
}


void MRCC_voidSetPLLFactors (u8 A_u8PLLM, u16 A_u16PLLN, u8 A_u8PLLP,u8 A_u8PLLQ)
{
	RCC->PLLCFGR &= 0xF0FC8000;
	RCC->PLLCFGR |= (A_u8PLLM<<0) | (A_u16PLLN << 6) | (A_u8PLLP<<16) |(A_u8PLLQ<<24) ;
}


void MRCC_voidSetPLLSource (clkSource_e A_ClkSource)
{
	switch (A_ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->PLLCFGR,22);
		break;
	case HSE:
		SET_BIT(RCC->PLLCFGR,22);
		break;
	default: break;
	}
}

void MRCC_voidSetBusesPrescaler (u8 A_u8AHB,u8 A_u8APB1,u8 A_u8APB2)
{
	RCC->CFGR &= ~((15<<4)|(63<<10));
	RCC->CFGR |= (A_u8AHB<<4) | (A_u8APB1<<10) | (A_u8APB2 <<13);
}



void MRCC_voidInit()
{
	clkStatus_e local_clkStatus;
#if CLK_SOURCE == CFG_HSI

	// Turn ON HSI
	MRCC_voidSetClkStatus(HSI, RCC_ENABLE);
	// Check if HSI is Ready
	local_clkStatus = MRCC_GetClkStatusSyncNonBlocking(HSI);
	// If HSI is Ready
	if (local_clkStatus==CLK_READY)
	{
		// Switch to HSI
		(void)MRCC_SetClkSource(HSI);

		// Set Buses Pre-scaler
		MRCC_voidSetBusesPrescaler(AHB_PRESCALER,APB1_PRESCALER,APB2_PRESCALER);

		// Turn OFF HSE
		MRCC_voidSetClkStatus(HSE, RCC_DISABLE);
		// Turn OFF PLL
		MRCC_voidSetClkStatus(PLL, RCC_DISABLE);
	}

#elif CLK_SOURCE == CFG_HSE
	// Turn ON HSE
	MRCC_voidSetClkStatus(HSE, RCC_ENABLE);
	// Check if HSE is Ready
	local_clkStatus = MRCC_GetClkStatusSyncNonBlocking(HSE);
	// If HSI is Ready
	if (local_clkStatus==CLK_READY)
	{
		// Switch to HSE
		(void)MRCC_SetClkSource(HSE);

		// Set Buses Pre-scaler
		MRCC_voidSetBusesPrescaler(AHB_PRESCALER,APB1_PRESCALER,APB2_PRESCALER);

		// Turn OFF HSI
		MRCC_voidSetClkStatus(HSI, RCC_DISABLE);
		// Turn OFF PLL
		MRCC_voidSetClkStatus(PLL, RCC_DISABLE);
	}

#elif CLK_SOURCE == CFG_PLL
	// Turn ON HSI
	MRCC_voidSetClkStatus(HSI, RCC_ENABLE);
	// Check if HSI is Ready
	local_clkStatus = MRCC_GetClkStatusSyncNonBlocking(HSI);
	// If HSI is Ready
	if (local_clkStatus==CLK_READY)
	{
		// Switch to HSI
		(void)MRCC_SetClkSource(HSI);
		// Turn OFF HSE
		MRCC_voidSetClkStatus(HSE, RCC_DISABLE);
		// Turn OFF PLL
		MRCC_voidSetClkStatus(PLL, RCC_DISABLE);
//---------------------------------------------------------------
		#if PLL_SOURCE == CFG_HSI
			// Set PLL Source as HSI
			MRCC_voidSetPLLSource(HSI);
		#elif PLL_SOURCE == CFG_HSE
			// Turn ON HSE
			MRCC_voidSetClkStatus(HSE, RCC_ENABLE);
			// Check if HSE is Ready
			local_clkStatus = MRCC_GetClkStatusSyncNonBlocking(HSE);
			// If HSI is Ready
			if (local_clkStatus==CLK_READY)
			{
				// Set PLL Source
				MRCC_voidSetPLLSource(HSE);
			}
		#else
			#error Wrong PLL Source Configuration.
		#endif

		// Set BusePrescaler
		MRCC_voidSetBusesPrescaler(AHB_PRESCALER,APB1_PRESCALER,APB2_PRESCALER);

		// Set PLL Factors
		MRCC_voidSetPLLFactors (PLLM_VALUE, PLLN_VALUE, PLLP_VALUE,PLLQ_VALUE);

		// Turn ON PLL
		MRCC_voidSetClkStatus(PLL, RCC_ENABLE);
		// Check if HSE is Ready
		local_clkStatus = MRCC_GetClkStatusSyncNonBlocking(PLL);
		if (local_clkStatus==CLK_READY)
		{
			// Switch to PLL
			(void)MRCC_SetClkSource(PLL);
			#if PLL_SOURCE == HSE
			// Turn OFF HSI
			MRCC_voidSetClkStatus(HSI,RCC_DISABLE);
			#endif
		}
	}
#else
	#error Wrong Clock Source Configuration.
#endif
}



void MRCC_voidPeripheralEnable (bus_e A_Bus,peripheral_e A_PeripheralToEnable)
{
	switch (A_Bus)
	{
	case RCC_AHB1: SET_BIT(RCC->AHB1ENR,A_PeripheralToEnable); break;
	case RCC_AHB2: SET_BIT(RCC->AHB2ENR,A_PeripheralToEnable); break;
	case RCC_APB1: SET_BIT(RCC->APB1ENR,A_PeripheralToEnable); break;
	case RCC_APB2: SET_BIT(RCC->APB2ENR,A_PeripheralToEnable); break;
	}
}


void MRCC_voidPeripheralDisable (bus_e A_Bus,peripheral_e A_PeripheralToEnable)
{
	switch (A_Bus)
	{
	case RCC_AHB1: CLR_BIT(RCC->AHB1ENR,A_PeripheralToEnable); break;
	case RCC_AHB2: CLR_BIT(RCC->AHB2ENR,A_PeripheralToEnable); break;
	case RCC_APB1: CLR_BIT(RCC->APB1ENR,A_PeripheralToEnable); break;
	case RCC_APB2: CLR_BIT(RCC->APB2ENR,A_PeripheralToEnable); break;
	}
}
