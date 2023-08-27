/*
 * GPIO_interface.h
 *

 *
 *  Created on: July  23, 2023
 *      Author:Ahmed Sanad
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

typedef struct
{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFRL;
	volatile u32 AFRH;
}GPIO_t;

#define GPIOA ((volatile GPIO_t *)0x40020000)
#define GPIOB ((volatile GPIO_t *)0x40020400)
#define GPIOC ((volatile GPIO_t *)0x40020800)



typedef enum{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}GPIO_Pin_Number;


typedef enum{
	GPIO_LOW_SPEED=0,
	GPIO_MEDIUM_SPEED,
	GPIO_HIGH_SPEED,
	GPIO_VERY_HIGH_SPEED,
	GPIO_SPEED_NA
}GPIO_Speed;

typedef enum
{
  GPIO_RESET = 0,
  GPIO_SET
}GPIO_Pin_State;

typedef enum{
	GPIO_INPUT=0,
	GPIO_OUTPUT,
	GPIO_AF,
	GPIO_ANALOG
}GPIO_Mode;

typedef enum{
	GPIO_PUSH_PULL=0,
	GPIO_OPEN_DRAIN,
	GPIO_Output_NA
}GPIO_Output_Type;

typedef enum{
	GPIO_NO_PULL_UP_DOWN=0,
	GPIO_PULL_UP,
	GPIO_PULL_DOWN
}GPIO_Pull_State;

#define     GPIO_AF0 0
#define 	GPIO_AF1 1
#define 	GPIO_AF2 2
#define 	GPIO_AF3 3
#define 	GPIO_AF4 4
#define 	GPIO_AF5 5
#define 	GPIO_AF6 6
#define 	GPIO_AF7 7
#define 	GPIO_AF8 8
#define 	GPIO_AF9 9
#define 	GPIO_AF10 10
#define 	GPIO_AF11 11
#define 	GPIO_AF12 12
#define 	GPIO_AF13 13
#define 	GPIO_AF14 14
#define 	GPIO_AF15 15
//
typedef enum{
	GPIO_AF_0_RTC_50Hz=GPIO_AF0,
	GPIO_AF_0_MCO=GPIO_AF0,
	GPIO_AF_0_TAMPER= GPIO_AF0,
	GPIO_AF_0_SWJ= GPIO_AF0,
	GPIO_AF_0_TRACE= GPIO_AF0,

	GPIO_AF_1_TIM1=GPIO_AF1,
	GPIO_AF_1_TIM2=GPIO_AF1,

	GPIO_AF_2_TIM3=GPIO_AF2,
	GPIO_AF_2_TIM4=GPIO_AF2,
	GPIO_AF_2_TIM5=GPIO_AF2,

	GPIO_AF_3_TIM9=GPIO_AF3,
	GPIO_AF_3_TIM10=GPIO_AF3,
	GPIO_AF_3_TIM11=GPIO_AF3,

	GPIO_AF_4_I2C1=GPIO_AF4,
	GPIO_AF_4_I2C2=GPIO_AF4,
	GPIO_AF_4_I2C3=GPIO_AF4,

	GPIO_AF_5_SPI1=GPIO_AF5,
	GPIO_AF_5_SPI2=GPIO_AF5,
	GPIO_AF_5_SPI3=GPIO_AF5,
	GPIO_AF_5_SPI4=GPIO_AF5,
	GPIO_AF_5_I2S3ext=GPIO_AF5,

	GPIO_AF_6_SPI3=GPIO_AF6,
	GPIO_AF_6_I2S2ext=GPIO_AF6,

	GPIO_AF_7_USART1=GPIO_AF7,
	GPIO_AF_7_USART2=GPIO_AF7,
	GPIO_AF_7_I2S3ext=GPIO_AF7,

	GPIO_AF_8_USART6=GPIO_AF8,

	GPIO_AF_9_I2C2=GPIO_AF9,
	GPIO_AF_9_I2C3=GPIO_AF9,

	GPIO_AF_10_OTG_FS=GPIO_AF10,

	GPIO_AF_12_SDIO=GPIO_AF12,

	GPIO_AF_15_EVENTOUT=GPIO_AF15,

	GPIO_AF_NA
}GPIO_AF_Num;


typedef struct
{
  GPIO_Pin_Number Pin;

  GPIO_Mode Mode;

  GPIO_Output_Type Output_Mode;

  GPIO_Pull_State Pull;

  GPIO_Speed Speed;

  GPIO_AF_Num Alternate;
}GPIO_InitType;

void GPIO_SetPinDirection( GPIO_t  *GPIOx, const GPIO_InitType *GPIO_Init);
void GPIO_WritePin( GPIO_t  *GPIOx, const GPIO_Pin_Number Pin_Number,const GPIO_Pin_State GPIO_state);
GPIO_Pin_State GPIO_ReadPin ( GPIO_t  *GPIOx, const GPIO_Pin_Number Pin_Number);




#endif /* GPIO_INTERFACE_H_ */
