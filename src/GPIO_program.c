

#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/LIB.h"

#include "../include/MCAL/RCC/RCC_interface.h"
#include "../include/MCAL/RCC/RCC_private.h"
#include "../include/MCAL/RCC/RCC_configuration.h"

#include "../include/MCAL/GPIO/GPIO_interface.h"
#include "../include/MCAL/GPIO/GPIO_private.h"
#include "../include/MCAL/GPIO/GPIO_configurations.h"





void GPIO_SetPinDirection( GPIO_t  *GPIOx, const GPIO_InitType *GPIO_Init)
{
	// check Pin Number
	VALIDATE ((IS_GPIO_PIN(GPIO_Init->Pin)),"Wrong Pin Number");

	// Configure The Mode
	VALIDATE ((GPIO_Init->Mode <= GPIO_ANALOG), "Wrong Mode Configuration");
	// Mask the 2 bits of the mode
	//Each Pin Has Two bits
	GPIOx->MODER &= ~(3 << (GPIO_Init->Pin * 2));
	// Set Mode
	GPIOx->MODER |= (GPIO_Init->Mode << (GPIO_Init->Pin * 2));

	// Configure the Speed
	if (GPIO_Init->Speed != GPIO_SPEED_NA)
	{
		VALIDATE((GPIO_Init->Speed <= GPIO_VERY_HIGH_SPEED), "Wrong Speed Configuration");
		// Mask the 2 bits of the speed
		GPIOx->OSPEEDR &= ~(3 << (GPIO_Init->Pin * 2));
		// Set speed
		GPIOx->OSPEEDR |= (GPIO_Init->Speed << (GPIO_Init->Pin * 2));
	}

	// Configure The O/P Type
	VALIDATE((GPIO_Init->Output_Mode <= GPIO_Output_NA),"Wrong Output Configurations");
	switch (GPIO_Init->Output_Mode)
	{
	case GPIO_PUSH_PULL: CLR_BIT (GPIOx->OTYPER,GPIO_Init->Pin); break;
	case GPIO_OPEN_DRAIN:SET_BIT (GPIOx->OTYPER,GPIO_Init->Pin); break;
	case GPIO_Output_NA: break;
	}

	// Configure Pull-up/down
	VALIDATE((GPIO_Init->Pull <= GPIO_PULL_DOWN), "Wrong Pull-up/down Configuration");
	// Mask the 2 bits of the Pull-up/down
	GPIOx->PUPDR &= ~(3 << (GPIO_Init->Pin * 2));
	// Set Pull-up/down
	GPIOx->PUPDR |= (GPIO_Init->Pull << (GPIO_Init->Pin * 2));

	// Configure the AF
	if (GPIO_Init->Alternate != GPIO_AF_NA)
	{
		// Check for AF Number
		VALIDATE((IS_GPIO_AF(GPIO_Init->Alternate)), "Wrong AF Configuration");
		// Check for Low or High Register
		if (GPIO_Init->Pin < PIN8)
		{
			// Set AF Value
			GPIOx->AFRL |= (GPIO_Init->Alternate<<(GPIO_Init->Pin * 4));
		}
		else if (GPIO_Init->Pin <= PIN15)
		{
			// Set AF Value
			GPIOx->AFRH |= (GPIO_Init->Alternate<<((GPIO_Init->Pin - 8) * 4));
		}
	}
}

void GPIO_WritePin( GPIO_t  *GPIOx, const GPIO_Pin_Number Pin_Number,const GPIO_Pin_State GPIO_state)
{
	// Check pin Number
	VALIDATE ((IS_GPIO_PIN(Pin_Number)),"Wrong Pin Number");
	// check on state
	VALIDATE ((IS_GPIO_PIN_ACTION(GPIO_state)),"Wrong Pin State");
	switch (GPIO_state)
	{
	case GPIO_SET:     GPIOx->BSRR = 1<<Pin_Number;      break;
	case GPIO_RESET  : GPIOx->BSRR = 1<<(Pin_Number+16); break;
	}
}

GPIO_Pin_State GPIO_ReadPin ( GPIO_t  *GPIOx, const GPIO_Pin_Number Pin_Number)
{
	GPIO_Pin_State pinStatus;

	// Check pin Number
	VALIDATE ((IS_GPIO_PIN(Pin_Number)),"Wrong Pin Number");

	// read the pin
	pinStatus = GET_BIT(GPIOx->IDR,Pin_Number);

	return pinStatus;
}

