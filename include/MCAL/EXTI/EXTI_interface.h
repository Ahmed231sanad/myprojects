
#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


typedef enum{
	EXTI0 = 0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	EXTI5,
	EXTI6,
	EXTI7,
	EXTI8,
	EXTI9,
	EXTI10,
	EXTI11,
	EXTI12,
	EXTI13,
	EXTI14,
	EXTI15
}EXTI_LINES_e;


typedef enum{
	FALLING_EDGE =0,
	RISING_EDGE ,
	ON_CHANGE
}SENSE_CONTROL_e;


void MEXTI_voidConfig (EXTI_LINES_e A_EXTILine, GPIO_t  *A_GPIOx, SENSE_CONTROL_e A_SenseMode);
void MEXTI_voidSetCallBack (void(*A_ptrToFunc)(void));
void MEXTI_voidDisable (EXTI_LINES_e A_EXTILine);









#endif /* EXTI_INTERFACE_H_ */
