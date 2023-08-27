
#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_


typedef struct
{
    volatile u32 ISER[8];
    volatile u32 Reserved0[24];
    volatile u32 ICER[8];
    volatile u32 Reserved1[24];
    volatile u32 ISPR[8];
    volatile u32 Reserved2[24];
    volatile u32 ICPR[8];
    volatile u32 Reserved3[24];
    volatile u32 IABR[8];
    volatile u32 Reserved4[56];
    //Byte  Accessible
    volatile u8 IPR[240];
    volatile u32 Reserved5[580];
    volatile u32 STIR;
}NVIC_t;

#define MNVIC ((volatile NVIC_t *)0xE000E100)

#define MNVIC_STIR ((volatile u32 *)0xE000EF00)

// SCB
typedef struct
{

    volatile u32 CPUID;
    volatile u32 ICSR;
    volatile u32 VTOR;
    volatile u32 AIRCR;
    volatile u32 SCR;
    volatile u32 CCR;
    volatile u32 SHPR1;
    volatile u32 SHPR2;
    volatile u32 SHPR3;
    volatile u32 SHCSR;
    volatile u32 CFSR;
    volatile u32 HFSR;
    volatile u32 RESERVED;
    volatile u32 MMFAR;
    volatile u32 BFAR;

} SCB_Type;

#define SCB ((volatile SCB_Type *)0xE000ED0C)

#endif /* NVIC_PRIVATE_H_ */
