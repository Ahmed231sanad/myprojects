
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/LIB.h"

#include "../include/MCAL/RCC/RCC_interface.h"
#include "../include/MCAL/RCC/RCC_private.h"
#include "../include/MCAL/RCC/RCC_configuration.h"

#include "../include/MCAL/NVIC/NVIC_interface.h"
#include "../include/MCAL/NVIC/NVIC_private.h"
#include "../include/MCAL/NVIC/NVIC_congig.h"

static u32 global_u32staticGroupConf;


/******************************************************************************/
/*Function: MNVIC_VoidEnablePeripheral	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Enables the INT of the peripheral in NVIC		          */
/******************************************************************************/
void MNVIC_VoidEnablePeripheral(u8 A_u8INTID)
{
	/*
	 * 240 INT - 8 REG - 32 INT per REG
	 * 0   - 31  REG 0
	 * 32  - 63  REG 1
	 * .
	 * .
	 * .
	 * 224 - 239 REG 7
	 */
	MNVIC->ISER[A_u8INTID / 32] = 1 << (A_u8INTID % 32);
}

/******************************************************************************/
/*Function: MNVIC_VoidDisablePeripheral	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Disables the INT of the peripheral in NVIC		          */
/******************************************************************************/
void MNVIC_VoidDisablePeripheral(u8 A_u8INTID)
{
	MNVIC->ICER[A_u8INTID / 32] = 1 << (A_u8INTID % 32);
}

/******************************************************************************/
/*Function: MNVIC_VoidSetPending    	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Sets pending flag of Peripheral        		          */
/******************************************************************************/
void MNVIC_VoidSetPending(u8 A_u8INTID)
{
	MNVIC->ISPR[A_u8INTID / 32] = 1 << (A_u8INTID % 32);
}

/******************************************************************************/
/*Function: MNVIC_VoidClearPending    	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Clears pending flag of Peripheral        		          */
/******************************************************************************/
void MNVIC_VoidClearPending(u8 A_u8INTID)
{
	MNVIC->ICPR[A_u8INTID / 32] = 1 << (A_u8INTID % 32);
}

/******************************************************************************/
/*Function: MNVIC_u8GetActive       	                         			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function returns state of active flag in NVIC     		          */
/******************************************************************************/
u8 MNVIC_u8GetActive(u8 A_u8INTID)
{
	return GET_BIT(MNVIC->IABR[A_u8INTID / 32],(A_u8INTID % 32));
}

/******************************************************************************/
/*Function: MNVIC_voidSetPriorityConfig                         			  */
/*I/P Parameters: Priority option              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Sets the group and the sub priority configurations       */
/******************************************************************************/
/*
 * Options:- GROUP_4BITS - GROUP_3BITS - GROUP_2BITS - GROUP_1BITS - GROUP_0BITS
/******************************************************************************/
void MNVIC_voidSetPriorityConfig(u8 A_u8Group)
{
	global_u32staticGroupConf = 0x05FA0000 | (A_u8Group << 8);
	SCB->AIRCR = global_u32staticGroupConf;
}

/******************************************************************************/
/*Function: MNVIC_VoidSetPriority                                			  */
/*I/P Parameters: Interrupt ID              								  */
/*Returns:it returns no thing	                            				  */
/*Desc:This Function Sets the group and the sub priority for required INT     */
/******************************************************************************/
/*
 * Options for Copy_u8GroupPriority:- GROUP_PRIORITY_0 ... GROUP_PRIORITY_15
 * Options for Copy_u8SubPriority  :- SUB_PRIORITY_0   ... SUB_PRIORITY_15
 * No Of Bits Per Group
 * This Function
/******************************************************************************/
void MNVIC_VoidSetPriority(s8 A_s8INTID, GroupPriority_e A_GroupPriority, SubPriority_e A_SubPriority)
{
	//How Many Bits  In Group
  u8 local_u8Priority =  A_SubPriority | A_GroupPriority << ((global_u32staticGroupConf - 0x05FA0300)/256);

  if (A_s8INTID < 0)
  {
	  // Core Peripheral
	  if (A_s8INTID == MEMORY_MANAGE || A_s8INTID == BUS_FAULT || A_s8INTID == USAGE_FAULT)
	  {
		  // SHPR1
		  A_s8INTID += 3;
		  SCB->SHPR1 = (local_u8Priority) << ((8 * A_s8INTID) + 4);
	  }
	  else if (A_s8INTID == SV_CALL)
	  {
		  // SHPR2
		  A_s8INTID += 7;
		  SCB->SHPR2 = (local_u8Priority) << ((8 * A_s8INTID) + 4);
	  }
	  else if (A_s8INTID == SYSTICK || A_s8INTID == PEND_SV)
	  {
		  // SHPR3
		  A_s8INTID += 8;
		  SCB->SHPR3 = (local_u8Priority) << ((8 * A_s8INTID) + 4);
	  }
  }
  // External INTs
  else if (A_s8INTID >= 0)
  {
	  MNVIC->IPR[A_s8INTID] = local_u8Priority << 4;
  }
}



