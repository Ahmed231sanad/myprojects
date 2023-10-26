
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/MEMORY_MAP.h"
#include "../../LIB/ERROR_STATUS.h"
#include "UART_private.h"
#include "../../Application/config.h"
#include "UART_interface.h"



u8 UART_State = UART_IDLE;
u8 UART_ISRSOURCE = UART_ISR_SOURCE_SEND_CHAR;
//Callback Function
void (*UART_PVCallBack)(void) = (void*)0;
u8 *UART_pu8Data = (void*)0;
u8 UART_BufferSize, UART_BufferCounter = 0;
ES_t UART_Init(const UART_Init_t *Copy_UART){
    ES_t Local_Error = ES_NOK;
    if(NULL != Copy_UART){
        //Configure Word Length
        if(Copy_UART->WordLength == UART_8_WORD_LENGTH){
            CLR_BIT(USART1->CR1,12);
        }
        else if(Copy_UART->WordLength == UART_9_WORD_LENGTH){
            SET_BIT(USART1->CR1,12);
        }
        else{
            Local_Error = ES_OUT_OF_RANGE;
            return Local_Error;
        }
        //Setting Parity
        if(Copy_UART->Parity == UART_No_Parity){
            CLR_BIT(USART1->CR1,10);
            CLR_BIT(USART1->CR1,12);
        }
        else if(Copy_UART->Parity == UART_Even_Parity){
            CLR_BIT(USART1->CR1,12);
            SET_BIT(USART1->CR1,10);
            CLR_BIT(USART1->CR1,9);
        }
        else if(Copy_UART->Parity == UART_Odd_Parity){
            CLR_BIT(USART1->CR1,12);
            SET_BIT(USART1->CR1,10);
            SET_BIT(USART1->CR1,9);
        }
        else{
            Local_Error = ES_OUT_OF_RANGE;
            return Local_Error;
        }
        //Configure Number of StopBits
        if(Copy_UART->StopBits == UART_One_Stop_Bit){
            CLR_BIT(USART1->CR2,12);
            CLR_BIT(USART1->CR2,13);
        }
        else if(Copy_UART->StopBits == UART_Half_Stop_Bit){
            CLR_BIT(USART1->CR2,12);
            SET_BIT(USART1->CR2,13);
        }
        else if(Copy_UART->StopBits == UART_Two_Stop_Bit){
            SET_BIT(USART1->CR2,12);
            CLR_BIT(USART1->CR2,13);
        }
        else if(Copy_UART->StopBits == UART_One_And_Half_Stop_Bit){
            SET_BIT(USART1->CR2,12);
            SET_BIT(USART1->CR2,13);
        }
        else{
            Local_Error = ES_OUT_OF_RANGE;
            return Local_Error;
        }
        //Setting BaudRate
        if(Copy_UART->BaudRate == UART_9600){
            USART1->BRR = 0x341;
        }
        else if(Copy_UART->BaudRate == UART_115200){
            USART1->BRR = 0x45;
        }
        //Enable Transmitter Block
        SET_BIT(USART1->CR1,3);
        //Enable Reciever Block
        SET_BIT(USART1->CR1,2);
        //Enable UART Peripheral
        SET_BIT(USART1->CR1,13);
        
        Local_Error = ES_OK;
    }
    else{
        Local_Error = ES_NULL_POINTER;
    }
    return Local_Error;
}

ES_t UART_SendCharSynchronous(u8 Copy_u8Data){
    ES_t Local_Error = ES_NOK;
    if(UART_State == UART_BUSY){
        Local_Error = ES_BUSY_FUNCTION;
    }
    else{
        UART_State = UART_BUSY;
        USART1->DR = Copy_u8Data;
        //Busy Wait
        while(!GET_BIT(USART1->SR,6));
        UART_State = UART_IDLE;
        Local_Error = ES_OK;
    }
    
    return Local_Error;
}

ES_t UART_SendBufferSynchronous(u8 *Copy_pu8Buffer, u8 BufferSize){
    ES_t Local_Error = ES_NOK;
    u8 i = 0;
    for(i = 0; i < BufferSize; i++){
        UART_SendCharSynchronous(Copy_pu8Buffer[i]);
    }
    return Local_Error;
}

ES_t UART_SendCharASynchronous(u8 *Copy_pu8Data, void (*Copy_PVCallBack)(void)){
    ES_t Local_Error = ES_NOK;
    if(UART_State == UART_BUSY){
        Local_Error = ES_BUSY_FUNCTION;
    }
    else{
        if(NULL == Copy_pu8Data || NULL == Copy_PVCallBack){
            Local_Error = ES_NULL_POINTER;
        }
        else{
        UART_ISRSOURCE = UART_ISR_SOURCE_SEND_CHAR;
        UART_State = UART_BUSY;
		UART_PVCallBack = Copy_PVCallBack;
        //Enable Transmit Interrupt
        SET_BIT(USART1->CR1,6);
        USART1->DR = *Copy_pu8Data;
        Local_Error = ES_OK;
        }
    }
    return Local_Error;
}

ES_t UART_SendBufferASynchronous(u8 *Copy_pu8Data,u8 BufferSize, void (*Copy_PVCallBack)(void)){
    ES_t Local_Error = ES_NOK;
    if(UART_State == UART_BUSY){
        Local_Error = ES_BUSY_FUNCTION;
    }
    else{
        if(NULL == Copy_pu8Data || NULL == Copy_PVCallBack){
            Local_Error = ES_NULL_POINTER;
        }
        else{
        UART_ISRSOURCE = UART_ISR_SOURCE_SEND_BUFFER;
        UART_State = UART_BUSY;
        UART_BufferCounter = 0;
        UART_BufferSize = BufferSize;
        UART_pu8Data = Copy_pu8Data;
        UART_PVCallBack = Copy_PVCallBack;
        //Enable Transmit Interrupt
        SET_BIT(USART1->CR1,6);
        USART1->DR = UART_pu8Data[UART_BufferCounter];
        Local_Error = ES_OK;
        }
    }
    return Local_Error;
}

ES_t UART_ReceiveCharSynchronous(u8 *Copy_u8Data){
    ES_t Local_Error = ES_NOK;
    //Busy Wait
    while(!GET_BIT(USART1->SR,5));
	*Copy_u8Data = USART1->DR;
    Local_Error = ES_OK;
    return Local_Error;
}



void USART1_IRQHandler(void){
    if(GET_BIT(USART1->SR,6)){
        if(UART_ISRSOURCE == UART_ISR_SOURCE_SEND_CHAR){
        //Disable Transmit Interrupt
        CLR_BIT(USART1->CR1,6);
        UART_PVCallBack();
        CLR_BIT(USART1->SR,6);
        UART_State = UART_IDLE;
        }
        else if(UART_ISRSOURCE == UART_ISR_SOURCE_SEND_BUFFER){
            if(UART_BufferCounter < UART_BufferSize){
                USART1->DR = UART_pu8Data[UART_BufferCounter];
                UART_BufferCounter++;
            }
            else{
                //Disable Transmit Interrupt
                CLR_BIT(USART1->CR1,6);
                UART_PVCallBack();
                CLR_BIT(USART1->SR,6);
                UART_State = UART_IDLE;
            }
        }
    }
}