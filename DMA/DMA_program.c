/*******************************************************************/
/*  Author :Ahmed Sanad                                      */
/*  Date : 15 / 10 / 2023                                            */                                               */
/*******************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/MEMORY_MAP.h"
#include "../../LIB/ERROR_STATUS.h"

#include "DMA_interface.h"
#include "DMA_private.h"
#include "../../Application/config.h"

void (*DMA_CallBack[7])(void);


ES_t DMA_VidSetConfiguration(const DMA_Config_t *Copy_DMA_Config){
    ES_t Local_enumError = ES_NOK;
    //Disable DMA
    CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,0);
    //Wait for disable
    while(GET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,0));
    //Direction
    if(Copy_DMA_Config->DMA_Direction == DMA_DIR_MEM_TO_MEM){
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,14);
    }
    else if(Copy_DMA_Config->DMA_Direction == DMA_DIR_MEM_TO_PER){
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,4);
    }
    else if(Copy_DMA_Config->DMA_Direction == DMA_DIR_PER_TO_MEM){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,4);
    }
    else{
        Local_enumError = ES_OUT_OF_RANGE;
    }
    //Mode
    if(Copy_DMA_Config->DMA_Mode == DMA_MODE_CIRCULAR){
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,5);
    }
    else if(Copy_DMA_Config->DMA_Mode == DMA_MODE_NORMAL){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,5);
    }
    else{
        Local_enumError = ES_OUT_OF_RANGE;
    }
    //Peripheral increment
    if(Copy_DMA_Config->DMA_PINC == DMA_PINC_ENABLE){
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,6);
    }
    else if(Copy_DMA_Config->DMA_PINC == DMA_PINC_DISABLE){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,6);
    }
    else{
        Local_enumError = ES_OUT_OF_RANGE;
    }
    //Memory increment
    if(Copy_DMA_Config->DMA_MINC == DMA_MINC_ENABLE){
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,7);
    }
    else if(Copy_DMA_Config->DMA_MINC == DMA_MINC_DISABLE){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,7);
    }
    else{
        Local_enumError = ES_OUT_OF_RANGE;
    }
    //Memory size
    if(Copy_DMA_Config->DMA_MemSize == DMA_MEMSIZE_8BITS){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,8);
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,9);
    }
    else if(Copy_DMA_Config->DMA_MemSize == DMA_MEMSIZE_16BITS){
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,8);
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,9);
    }
    else if(Copy_DMA_Config->DMA_MemSize == DMA_MEMSIZE_32BITS){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,8);
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,9);
    }
    else{
        Local_enumError = ES_OUT_OF_RANGE;
    }
    //Peripheral size
    if(Copy_DMA_Config->DMA_PerSize == DMA_PERSIZE_8BITS){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,10);
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,11);
    }
    else if(Copy_DMA_Config->DMA_PerSize == DMA_PERSIZE_16BITS){
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,10);
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,11);
    }
    else if(Copy_DMA_Config->DMA_PerSize == DMA_PERSIZE_32BITS){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,10);
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,11);
    }
    else{
        Local_enumError = ES_OUT_OF_RANGE;
    }
    //Priority
    if(Copy_DMA_Config->Priority == DMA_PRIORITY_LOW){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,12);
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,13);
    }
    else if(Copy_DMA_Config->Priority == DMA_PRIORITY_MEDIUM){
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,12);
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,13);
    }
    else if(Copy_DMA_Config->Priority == DMA_PRIORITY_HIGH){
        CLR_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,12);
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,13);
    }
    else if(Copy_DMA_Config->Priority == DMA_PRIORITY_VERY_HIGH){
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,12);
        SET_BIT(DMA->Channel[Copy_DMA_Config->DMA_Channel].DMA_CCR,13);
    }
    else{
        Local_enumError = ES_OUT_OF_RANGE;
    }
    return Local_enumError;
}
ES_t DMA_VidStartAsynch(u8 Copy_u8Channel, u32 *Copy_u32SourceAddress, u32 *Copy_u32DestinationAddress, u16 Copy_u16BlockLength) {
    ES_t Local_enumError = ES_OK;
    
    // Check DMA channel validity
    if (Copy_u8Channel >= NUM_DMA_CHANNELS) {
        return ES_OUT_OF_RANGE;
    }

    // Disable DMA channel
    CLR_BIT(DMA->Channel[Copy_u8Channel].DMA_CCR, 0);
    
    // Wait for disable
    while (GET_BIT(DMA->Channel[Copy_u8Channel].DMA_CCR, 0));

    // Set source address
    DMA->Channel[Copy_u8Channel].DMA_CPAR = (u32)Copy_u32SourceAddress;
    
    // Set destination address
    DMA->Channel[Copy_u8Channel].DMA_CMAR = (u32)Copy_u32DestinationAddress;
    
    // Set block length
    DMA->Channel[Copy_u8Channel].DMA_CNDTR = Copy_u16BlockLength;
    
    // Enable Complete Interrupt
    SET_BIT(DMA->Channel[Copy_u8Channel].DMA_CCR, 1);
    
    // Enable DMA
    SET_BIT(DMA->Channel[Copy_u8Channel].DMA_CCR, 0);

    return Local_enumError;
}
ES_t DMA_VidStartSynch(u8 Copy_u8Channel, u32 *Copy_u32SourceAddress, u32 *Copy_u32DestinationAddress, u16 Copy_u16BlockLength){
    ES_t Local_enumError = ES_OK;
    // Check DMA channel validity
    if (Copy_u8Channel >= NUM_DMA_CHANNELS) {
        return ES_OUT_OF_RANGE;
    }

    // Disable DMA channel
    CLR_BIT(DMA->Channel[Copy_u8Channel].DMA_CCR, 0);
    
    // Wait for disable
    while (GET_BIT(DMA->Channel[Copy_u8Channel].DMA_CCR, 0));

    // Set source address
    DMA->Channel[Copy_u8Channel].DMA_CPAR = (u32)Copy_u32SourceAddress;
    
    // Set destination address
    DMA->Channel[Copy_u8Channel].DMA_CMAR = (u32)Copy_u32DestinationAddress;
    
    // Set block length
    DMA->Channel[Copy_u8Channel].DMA_CNDTR = Copy_u16BlockLength;
    
    // Enable DMA
    SET_BIT(DMA->Channel[Copy_u8Channel].DMA_CCR, 0);

    // Wait for transfer complete
    while (!GET_BIT(DMA->DMA_ISR, (1 + (4 * Copy_u8Channel))));

    // Clear transfer complete flag
    SET_BIT(DMA->DMA_IFCR, ( 4 * Copy_u8Channel ));

    return Local_enumError;
}


ES_t DMA_VidSetCallBack(void (*Copy_PVidFunc)(void), u8 Copy_u8Channel){
    ES_t Local_enumError = ES_NOK;
    if(Copy_PVidFunc != NULL){
        DMA_CallBack[Copy_u8Channel] = Copy_PVidFunc;
        Local_enumError = ES_OK;
    }
    return Local_enumError;
}

ES_t DMA_VidClearFlag(u8 Copy_u8Channel){
    ES_t Local_enumError = ES_NOK;
    if(Copy_u8Channel < 7){
        SET_BIT(DMA->DMA_IFCR,Copy_u8Channel*4);
        Local_enumError = ES_OK;
    }
    return Local_enumError;
}

ES_t DMA_VidDisable(u8 Copy_u8Channel){
    ES_t Local_enumError = ES_NOK;
    if(Copy_u8Channel < 7){
        CLR_BIT(DMA->Channel[Copy_u8Channel].DMA_CCR,0);
        Local_enumError = ES_OK;
    }
    return Local_enumError;
}

void DMA1_Channel1_IRQHandler(void){
    DMA_CallBack[0]();
    SET_BIT(DMA->DMA_IFCR,0);
}
void DMA1_Channel2_IRQHandler(void){
    DMA_CallBack[1]();
    SET_BIT(DMA->DMA_IFCR,4);
}
void DMA1_Channel3_IRQHandler(void){
    DMA_CallBack[2]();
    SET_BIT(DMA->DMA_IFCR,8);
}
void DMA1_Channel4_IRQHandler(void){
    DMA_CallBack[3]();
    SET_BIT(DMA->DMA_IFCR,12);
}
void DMA1_Channel5_IRQHandler(void){
    DMA_CallBack[4]();
    SET_BIT(DMA->DMA_IFCR,16);
}
void DMA1_Channel6_IRQHandler(void){
    DMA_CallBack[5]();
    SET_BIT(DMA->DMA_IFCR,20);
}
void DMA1_Channel7_IRQHandler(void){
    DMA_CallBack[6]();
    SET_BIT(DMA->DMA_IFCR,24);
}
