#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_

typedef enum{
    UART_9600,
    UART_115200
}UART_BAUDRATE_t;

typedef enum{
    UART_One_Stop_Bit,
    UART_Half_Stop_Bit,
    UART_Two_Stop_Bit,
    UART_One_And_Half_Stop_Bit
}UART_StopBits_t;

typedef enum{
    UART_No_Parity,
    UART_Even_Parity,
    UART_Odd_Parity
}UART_Parity_t;
typedef enum{
    UART_8_WORD_LENGTH,
    UART_9_WORD_LENGTH
}UART_WordLen_t;
typedef struct 
{
    u32 BaudRate;
    UART_WordLen_t WordLength;
    UART_Parity_t Parity;
    UART_StopBits_t StopBits;
}UART_Init_t;




ES_t UART_Init(const UART_Init_t *Copy_UART);
ES_t UART_SendCharSynchronous(u8 Copy_u8Data);
ES_t UART_SendCharASynchronous(u8 *Copy_pu8Data, void (*Copy_PVCallBack)(void));
ES_t UART_SendBufferASynchronous(u8 *Copy_pu8Data,u8 BufferSize, void (*Copy_PVCallBack)(void));
ES_t UART_SendBufferSynchronous(u8 *Copy_pu8Buffer, u8 BufferSize);
ES_t UART_ReceiveCharSynchronous(u8 *Copy_u8Data);


//TODO : Fix UART_SendBufferSynchronous doesn't Send First Char in Buffer when running but works good in debugging













#endif