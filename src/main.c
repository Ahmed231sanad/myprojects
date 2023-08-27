
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"


#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/LIB.h"

#include "../include/MCAL/RCC/RCC_interface.h"
#include "../include/MCAL/GPIO/GPIO_interface.h"
#include "../include/MCAL/EXTI/EXTI_interface.h"
void ToggleLed()
{
	static u8 flag= 0;
	if (flag==0)
	{
		flag=1;
		  GPIO_WritePin(GPIOA,PIN0,GPIO_SET);
	}
	else
	{
		flag=0;
	  GPIO_WritePin(GPIOA,PIN0,GPIO_RESET);
	}
}
void APP_GPIO_Init();

int
main(int argc, char* argv[])
{
	  MRCC_voidInit();
	  MRCC_voidPeripheralEnable(RCC_AHB1, AHB1_GPIOA);


	  GPIO_WritePin(GPIOA,PIN0,GPIO_SET);
	  EXTI0_callBack(ToggleLed);

	  MEXTI_voidConfig(EXTI0,GPIOA,FALLING_EDGE);

	  void APP_GPIO_Init()
	  {


		  GPIO_InitType PIN_01={PIN0,GPIO_INPUT,GPIO_OUTPUT,GPIO_PULL_UP,GPIO_SPEED_NA,GPIO_AF_NA};
		  GPIO_SetPinDirection(GPIOA,&PIN_01);

		  GPIO_InitType PIN_02={PIN1,GPIO_OUTPUT,GPIO_PUSH_PULL,GPIO_NO_PULL_UP_DOWN,GPIO_LOW_SPEED,GPIO_AF_NA};
		  GPIO_SetPinDirection(GPIOA,&PIN_02);

	  }

  // Infinite loop
  while (1)
    {
       // Add your code here.
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
