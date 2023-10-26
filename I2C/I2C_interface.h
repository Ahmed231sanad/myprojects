#ifndef _I2C_INTERFACE_H_
#define _I2C_INTERFACE_H_
ES_t I2C_Init(void);
ES_t I2C_Start(void);
ES_t I2C_SendSlaveAddressWithWrite(u8 SlaveAddress);
ES_t I2C_SendSlaveAddressWithRead(u8 SlaveAddress);
ES_t I2C_SendData(u8 *buffer, u8 size);
ES_t I2C_Stop(void);
ES_t I2C_MasterSend(u8 SlaveAddress, u8 *buffer, u8 size);
ES_t I2C_MasterRecieve(u8 SlaveAddress, u8 *buffer, u8 size);











#endif