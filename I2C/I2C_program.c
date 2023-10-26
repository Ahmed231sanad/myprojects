

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/MEMORY_MAP.h"
#include "../../LIB/ERROR_STATUS.h"
#include "I2C_interface.h"
#include "I2C_private.h"
#include "../../Application/config.h"
#include "../RCC/RCC_interface.h"
#include "../GPIO/GPIO_interface.h"


ES_t I2C_Init(void){
    ES_t Local_Error = ES_NOK;
    
    RCC_EnablePeripheralClock(RCC_APB2, RCC_IOPB);
    RCC_EnablePeripheralClock(RCC_APB2, RCC_AFIO);
    GPIO_SetPinMode(GPIO_PORTB, GPIO_PIN6, GPIO_OUTPUT_50MHZ_AFOD);  //SCL
    GPIO_SetPinMode(GPIO_PORTB, GPIO_PIN7, GPIO_OUTPUT_50MHZ_AFOD);  //SDA
    //Enable I2C1 Clock
    RCC_EnablePeripheralClock(RCC_APB1, RCC_I2C1);

    //Disable I2C Peripheral
     I2C1->CR1.PE = 0;
    //I2C Under Reset Mode
    I2C1->CR1.SWRST = 1;
    //I2C Not Under Reset Mode
    I2C1->CR1.SWRST = 0;
    /*---------------------------- I2Cx CR Configuration ----------------------*/
    //Set Own Address
    I2C1->OAR1.ADD = I2C_SLAVE_ADDRESS;
    //No Dual Address
    I2C1->OAR2.ENDUAL = 0;
    //Freq
    I2C1->CR2 = 0x30;
    //Standard Mode
    I2C1->CCR.CCR = 0b101000;
    I2C1->CCR.DUTY = 0;
    I2C1->CCR.FS = 1;
    I2C1->TRISE = 0xf;
    I2C1->CR1.PE = 1;
    return Local_Error;
}

ES_t I2C_Start(void){
    ES_t Local_Error = ES_NOK;
    u16 reg;
    //Clear POS
    I2C1->CR1.POS = 0;
    //Generate Start Condition
    I2C1->CR1.START = 1;
    //Wait for Start Condition to be generated
    while(GET_BIT(I2C1->SR1,I2C_SR1_SB) == 0);
    //Clear Start Bit
    reg = I2C1->SR1;
    return Local_Error;
}

ES_t I2C_Stop(void){
    ES_t Local_Error = ES_NOK;
    u16 reg = 0;
    //Generate Stop Condition
    I2C1->CR1.STOP = 1;
    //Clear Stop Bit
    reg = I2C1->SR1;
    reg = I2C1->SR2;
    return Local_Error;
}

ES_t I2C_SendSlaveAddressWithWrite(u8 SlaveAddress){
    ES_t Local_Error = ES_NOK;
    u16 reg = 0;
    //Send Slave Address with Write Bit
    I2C1->DR.DATA = (SlaveAddress << 1);
    //Wait for Address to be sent
    while(!GET_BIT(I2C1->SR1,I2C_SR1_ADDR));
    //Clear Address Bit
    reg = I2C1->SR1;
    reg = I2C1->SR2;
    while(!GET_BIT(I2C1->SR1,I2C_SR1_TXE));
    return Local_Error;
}

ES_t I2C_SendSlaveAddressWithRead(u8 SlaveAddress){
    ES_t Local_Error = ES_NOK;
    u16 reg = 0;
    //Send Slave Address with Read Bit
    I2C1->DR.DATA = (SlaveAddress << 1) | 0x1;
    //Wait for Address to be sent
    while(!GET_BIT(I2C1->SR1,I2C_SR1_ADDR));
    //Clear Address Bit
    reg = I2C1->SR1;
    reg = I2C1->SR2;
    while(!GET_BIT(I2C1->SR1,I2C_SR1_TXE));
    return Local_Error;
}

ES_t I2C_SendData(u8 *buffer, u8 size){
    ES_t Local_Error = ES_NOK;
    u16 reg = 0;
    u8 Local_u8Counter = 0;
    for(Local_u8Counter = 0;Local_u8Counter < size;Local_u8Counter++){
        //Send Data
        I2C1->DR.DATA = buffer[Local_u8Counter];
        //Wait for Data to be sent
        while(!GET_BIT(I2C1->SR1,I2C_SR1_TXE) && !GET_BIT(I2C1->SR1,I2C_SR1_BTF));
        //Clear TXE Bit
        reg = I2C1->SR1;
        reg = I2C1->SR2;
    }
    Local_Error = ES_OK;
    return Local_Error;
}
ES_t I2C_MasterSend(u8 SlaveAddress, u8 *buffer, u8 size){
    ES_t Local_Error = ES_NOK;
    I2C_Start();
    I2C_SendSlaveAddressWithWrite(SlaveAddress);
    I2C_SendData(buffer, size);
    I2C_Stop();
    Local_Error = ES_OK;
    return Local_Error;
}
