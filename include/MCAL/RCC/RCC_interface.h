
#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

typedef enum{
	HSI=0,
	HSE,
	PLL
}clkSource_e;

typedef enum{
	RCC_DISABLE=0,
	RCC_ENABLE
}clkState_e;


typedef enum{
	CLK_NOT_READY=0,
	CLK_READY,
	OUT_OF_RANGE
}clkStatus_e;

typedef enum{
	RCC_AHB1=0,
	RCC_AHB2,
	RCC_APB1,
	RCC_APB2
}bus_e;

typedef enum{
	AHB1_GPIOA=0,
	AHB1_GPIOB=1,
	AHB1_GPIOC=2,
	AHB1_GPIOD=3,
	AHB1_GPIOH=7,
	AHB1_CRC=12,
	AHB1_DMA1=21,
	AHB1_DMA2=22,
	AHB2_OTGFS=7,
	APB1_TIM2=0,
	APB1_TIM3=1,
	APB1_TIM4=2,
	APB1_TIM5=3,
	APB1_WWDG=11,
	APB1_SPI2=14,
	APB1_SPI3=15,
	APB1_USART2=17,
	APB1_I2C1=21,
	APB1_I2C2=22,
	APB1_I2C3=23,
	APB1_PWR=28,
	APB2_TIM1=0,
	APB2_USART1=4,
	APB2_USART6=5,
	APB2_ADC1=8,
	APB2_SDIO=11,
	APB2_SPI1=12,
	APB2_SPI4=13,
	APB2_SYSCFG=14,
	APB2_TIM9=16,
	APB2_TIM10=17,
	APB2_TIM11=18
}peripheral_e;

/* ----------------------------------------------------------------------------- */

void MRCC_voidSetClkStatus (clkSource_e A_ClkSource, clkState_e A_ClkState);

clkStatus_e MRCC_GetClkStatus (clkSource_e A_ClkSource);

clkStatus_e MRCC_GetClkStatusSyncNonBlocking (clkSource_e A_ClkSource);

clkSource_e MRCC_SetClkSource (clkSource_e A_ClkSource);

clkSource_e MRCC_GetSelectedClkSource (void);

void MRCC_voidSetPLLFactors (u8 A_u8PLLM, u16 A_u16PLLN, u8 A_u8PLLP,u8 A_u8PLLQ);

void MRCC_voidSetPLLSource (clkSource_e A_ClkSource);

void MRCC_voidSetBusesPrescaler (u8 A_u8AHB,u8 A_u8APB1,u8 A_u8APB2);

void MRCC_voidInit();

void MRCC_voidPeripheralDisable (bus_e A_Bus,peripheral_e A_PeripheralToEnable);

void MRCC_voidPeripheralEnable (bus_e A_Bus,peripheral_e A_PeripheralToEnable);

#endif /* RCC_INTERFACE_H_ */
