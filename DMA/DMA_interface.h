
#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

typedef enum{
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3,
    DMA_CHANNEL_4,
    DMA_CHANNEL_5,
    DMA_CHANNEL_6,
    DMA_CHANNEL_7
}DMA_Channel_t;

typedef enum{
    DMA_DIR_MEM_TO_MEM,
    DMA_DIR_MEM_TO_PER,
    DMA_DIR_PER_TO_MEM,
    DMA_DIR_PER_TO_PER
}DMA_Direction_t;
typedef enum{
    DMA_MODE_CIRCULAR,
    DMA_MODE_NORMAL
}DMA_Mode_t;

typedef enum{
    DMA_PINC_ENABLE,
    DMA_PINC_DISABLE
}DMA_PINC_t;

typedef enum{
    DMA_MINC_ENABLE,
    DMA_MINC_DISABLE
}DMA_MINC_t;

typedef enum{
    DMA_MEMSIZE_8BITS,
    DMA_MEMSIZE_16BITS,
    DMA_MEMSIZE_32BITS
}DMA_MemSize_t;

typedef enum{
    DMA_PERSIZE_8BITS,
    DMA_PERSIZE_16BITS,
    DMA_PERSIZE_32BITS
}DMA_PerSize_t;

typedef enum{
    DMA_PRIORITY_LOW,
    DMA_PRIORITY_MEDIUM,
    DMA_PRIORITY_HIGH,
    DMA_PRIORITY_VERY_HIGH
}DMA_Priority_t;

typedef struct{
    u8 DMA_Channel;
    u8 DMA_Direction;
    u8 DMA_Mode;
    u8 DMA_PINC;
    u8 DMA_MINC;
    u8 DMA_MemSize;
    u8 DMA_PerSize;
    u8 Priority;
}DMA_Config_t;

ES_t DMA_VidSetConfiguration(const DMA_Config_t *Copy_DMA_Config);
ES_t DMA_VidStartAsynch(u8 Copy_u8Channel, u32 *Copy_u32SourceAddress, u32 *Copy_u32DestinationAddress, u16 Copy_u16BlockLength);
ES_t DMA_VidStartSynch(u8 Copy_u8Channel, u32 *Copy_u32SourceAddress, u32 *Copy_u32DestinationAddress, u16 Copy_u16BlockLength);
ES_t DMA_VidSetCallBack(void (*Copy_PVidFunc)(void), u8 Copy_u8Channel);
ES_t DMA_VidClearFlag(u8 Copy_u8Channel);
ES_t DMA_VidDisable(u8 Copy_u8Channel);










#endif