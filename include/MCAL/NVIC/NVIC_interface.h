
#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_


/////////////////////////
// Has No position On NVIC
#define PEND_SV -6
#define SYSTICK -5
////////////////////////////
#define SV_CALL -4
/////////////////////////
#define MEMORY_MANAGE -3
#define BUS_FAULT -2
#define USAGE_FAULT -1
/////////////////////////

#define WWDG 0
#define EXTI16_EN 1
#define EXTI21_EN 2
#define EXTI22_EN 3
#define FLASH 4
#define RCC 5
#define EXTI0_EN 6
#define EXTI1_EN 7
#define EXTI2_EN 8
#define EXTI3_EN 9
#define EXTI4_EN 10
#define DMA1_STREAM0 11
#define DMA1_STREAM1 12
#define DMA1_STREAM2 13
#define DMA1_STREAM3 14
#define DMA1_STREAM4 15
#define DMA1_STREAM5 16
#define DMA1_STREAM6 17
#define ADC 18
#define EXTI9_EN 23
#define TIM1_BRK_TIM9 24
#define TIM1_UP_TIM10 25
#define TIM1_TRG_COM_TIM11 26
#define TIM1_CC      27
#define TIM2         28
#define TIM3 	     29
#define TIM4 		 30
#define I2C1_EV 	 31
#define I2C1_ER 	 32
#define I2C2_EV 	 33
#define I2C2_ER 	 34
#define SPI1 		 35
#define SPI2 		 36
#define USART1 		 37
#define USART2 		 38
#define EXTI15_10 	 30
#define EXTI17_EN 		 41
#define EXTI18_EN 		 42
#define DMA1_STREAM7 47
#define SDIO 		 49
#define TIM5 		 50
#define SPI3 		 51
#define DMA2_STREAM0 56
#define DMA2_STREAM1 57
#define DMA2_STREAM2 58
#define DMA2_STREAM3 59
#define DMA2_STREAM4 60
#define OTG_FS 		 67
#define DMA2_STREAM5 68
#define DMA2_STREAM6 69
#define DMA2_STREAM7 70
#define USART6 		 71
#define I2C3_EV 	 72
#define I2C3_ER 	 73
#define FPU          81
#define SPI4         84


typedef enum{
 NO_GROUP_PRIORITY = 0 ,
 GROUP_PRIORITY_0  ,
 GROUP_PRIORITY_1  ,
 GROUP_PRIORITY_2  ,
 GROUP_PRIORITY_3  ,
 GROUP_PRIORITY_4  ,
 GROUP_PRIORITY_5  ,
 GROUP_PRIORITY_6  ,
 GROUP_PRIORITY_7  ,
 GROUP_PRIORITY_8  ,
 GROUP_PRIORITY_9  ,
 GROUP_PRIORITY_10 ,
 GROUP_PRIORITY_11 ,
 GROUP_PRIORITY_12 ,
 GROUP_PRIORITY_13 ,
 GROUP_PRIORITY_14 ,
 GROUP_PRIORITY_15
}GroupPriority_e;



typedef enum{
 NO_SUB_PRIORITY =0,
 SUB_PRIORITY_0  ,
 SUB_PRIORITY_1  ,
 SUB_PRIORITY_2  ,
 SUB_PRIORITY_3  ,
 SUB_PRIORITY_4  ,
 SUB_PRIORITY_5  ,
 SUB_PRIORITY_6  ,
 SUB_PRIORITY_7  ,
 SUB_PRIORITY_8  ,
 SUB_PRIORITY_9  ,
 SUB_PRIORITY_10 ,
 SUB_PRIORITY_11 ,
 SUB_PRIORITY_12 ,
 SUB_PRIORITY_13 ,
 SUB_PRIORITY_14 ,
 SUB_PRIORITY_15

}SubPriority_e;

typedef enum {
 GROUP_4BITS = 0,
 GROUP_3BITS = 4,
 GROUP_2BITS = 5,
 GROUP_1BITS = 6,
 GROUP_0BITS = 7
}GroupOptions_e;

/******************************************************************************/
/*Function: MNVIC_VoidEnablePeripheral	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Enables the INT of the peripheral in NVIC		          */
/******************************************************************************/
void MNVIC_VoidEnablePeripheral(u8 Copy_u8INTID);

/******************************************************************************/
/*Function: MNVIC_VoidDisablePeripheral	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Disables the INT of the peripheral in NVIC		          */
/******************************************************************************/
void MNVIC_VoidDisablePeripheral(u8 Copy_u8INTID);

/******************************************************************************/
/*Function: MNVIC_VoidSetPending    	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Sets pending flag of Peripheral        		          */
/******************************************************************************/
void MNVIC_VoidSetPending(u8 Copy_u8INTID);

/******************************************************************************/
/*Function: MNVIC_VoidClearPending    	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Clears pending flag of Peripheral        		          */
/******************************************************************************/
void MNVIC_VoidClearPending(u8 Copy_u8INTID);

/******************************************************************************/
/*Function: MNVIC_u8GetActive       	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function returns state of active flag in NVIC     		          */
/******************************************************************************/
u8 MNVIC_u8GetActive(u8 Copy_u8INTID);

/******************************************************************************/
/*Function: MNVIC_voidSetPriorityConfig                         			  */
/*I/P Parameters: Priority option              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Sets the group and the sub priority configurations       */
/******************************************************************************/
/*
 * Options:- GROUP_4BITS - GROUP_3BITS - GROUP_2BITS - GROUP_1BITS - GROUP_0BITS
/******************************************************************************/
void MNVIC_voidSetPriorityConfig(u8 Copy_u8Group);

/******************************************************************************/
/*Function: MNVIC_VoidSetPriority                                			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Sets the group and the sub priority for required INT     */
/******************************************************************************/
/*
 * Options for Copy_u8GroupPriority:- GROUP_PRIORITY_0 ... GROUP_PRIORITY_15
 * Options for Copy_u8SubPriority  :- SUB_PRIORITY_0   ... SUB_PRIORITY_15
/******************************************************************************/
void MNVIC_VoidSetPriority(s8 Copy_u8INTID, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority);

#endif
