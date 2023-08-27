/*
 * private file.h
 *
 */
#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define EXTI ((volatile EXTI_t *)0x40013C00)
#define SYSCFG ((volatile SYSCFG_t *)0x40013800)

typedef struct
{
    volatile u32 IMR;
    volatile u32 EMR;
    volatile u32 RTSR;
    volatile u32 FTSR;
    volatile u32 SWIER;
    volatile u32 PR;
} EXTI_t;

typedef struct
{
    volatile u32 MEMRMP;
    volatile u32 PMC;
    volatile u32 EXTICR1;
    volatile u32 EXTICR2;
    volatile u32 EXTICR3;
    volatile u32 EXTICR4;
} SYSCFG_t;

#endif /* EXTI_PRIVATE_H_ */
