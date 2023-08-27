

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_





//#define IS_GPIO_AF(AF)  1
//#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0)         || ((AF) == GPIO_AF8)        || \
//                          ( (AF) == GPIO_AF1)        || ((AF) == GPIO_AF9)        || \
//                          ( (AF) == GPIO_AF2)        || ((AF) == GPIO_AF10)       || \
//                          ( (AF) == GPIO_AF3)        || ((AF) == GPIO_AF11)       || \
//                          ( (AF) == GPIO_AF4)        || ((AF) == GPIO_AF12)       || \
//                          ( (AF) == GPIO_AF5)        || ((AF) == GPIO_AF13)       || \
//                          ( (AF) == GPIO_AF6)        || ((AF) == GPIO_AF14)       || \
//                          ( (AF) == GPIO_AF7)        || ((AF) == GPIO_AF15)       ||((AF) == GPIO_AF_NA)))

//#define IS_GPIO_AF(PIN)	     (((PIN) == GPIO_AF0) || ((PIN) == GPIO_AF8)    || \
//							 ((PIN) == GPIO_AF1) || ((PIN) == GPIO_AF9)     || \
//							 ((PIN) == GPIO_AF2) || ((PIN) == GPIO_AF10)    || \
//							 ((PIN) == GPIO_AF3) || ((PIN) == GPIO_AF11)    || \
//							 ((PIN) == GPIO_AF4) || ((PIN) == GPIO_AF12)    || \
//							 ((PIN) == GPIO_AF5) || ((PIN) == GPIO_AF13)    || \
//							 ((PIN) == GPIO_AF6) || ((PIN) == GPIO_AF14)    || \
//							 ((PIN) == GPIO_AF7) || ((PIN) == GPIO_AF15) || ((PIN) == GPIO_AF_NA))

#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF_0_RTC_50Hz)   || ((AF) == GPIO_AF_12_SDIO)      || \
                          ((AF) == GPIO_AF_0_MCO)        || ((AF) == GPIO_AF_0_TAMPER)     || \
                          ((AF) == GPIO_AF_0_SWJ)        || ((AF) == GPIO_AF_0_TRACE)      || \
                          ((AF) == GPIO_AF_1_TIM1)       || ((AF) == GPIO_AF_1_TIM2)       || \
                          ((AF) == GPIO_AF_2_TIM3)       || ((AF) == GPIO_AF_2_TIM4)       || \
                          ((AF) == GPIO_AF_2_TIM5)       || ((AF) == GPIO_AF_3_TIM9)       || \
                          ((AF) == GPIO_AF_3_TIM10)      || ((AF) == GPIO_AF_3_TIM11)      || \
                          ((AF) == GPIO_AF_4_I2C1)       || ((AF) == GPIO_AF_4_I2C2)       || \
                          ((AF) == GPIO_AF_4_I2C3)       || ((AF) == GPIO_AF_5_SPI1)       || \
                          ((AF) == GPIO_AF_5_SPI2)       || ((AF) == GPIO_AF_5_SPI4)       || \
                          ((AF) == GPIO_AF_5_SPI3)       || ((AF) == GPIO_AF_7_USART1)     || \
                          ((AF) == GPIO_AF_7_USART2)     || ((AF) == GPIO_AF_8_USART6)     || \
                          ((AF) == GPIO_AF_9_I2C2)       || ((AF) == GPIO_AF_9_I2C3)       || \
                          ((AF) == GPIO_AF_10_OTG_FS)    || ((AF) == GPIO_AF_15_EVENTOUT)  || ((AF) == GPIO_AF_NA))


// PIN >=0 && PIN <=15
#define IS_GPIO_PIN(PIN)	(((PIN) == PIN0) || ((PIN) == PIN8)     || \
							 ((PIN) == PIN1) || ((PIN) == PIN9)     || \
							 ((PIN) == PIN2) || ((PIN) == PIN10)    || \
							 ((PIN) == PIN3) || ((PIN) == PIN11)    || \
							 ((PIN) == PIN4) || ((PIN) == PIN12)    || \
							 ((PIN) == PIN5) || ((PIN) == PIN13)    || \
							 ((PIN) == PIN6) || ((PIN) == PIN14)    || \
							 ((PIN) == PIN7) || ((PIN) == PIN15))



#define IS_GPIO_PIN_ACTION(ACTION) (((ACTION) == GPIO_RESET) || ((ACTION) == GPIO_SET))

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
#endif /* GPIO_PRIVATE_H_ */
