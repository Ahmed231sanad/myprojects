
#ifndef RCC_CONFIGURATION_H_
#define RCC_CONFIGURATION_H_

#define RDY_WAIT_TIME 3000

#define CFG_HSI 0
#define CFG_HSE 1
#define CFG_PLL 2


#define CLK_SOURCE CFG_HSI

#define PLL_SOURCE CFG_HSI

/*
 * 0xxx: system clock not divided
 * 1000: system clock divided by 2
 * 1001: system clock divided by 4
 * 1010: system clock divided by 8
 * 1011: system clock divided by 16
 * 1100: system clock divided by 64
 * 1101: system clock divided by 128
 * 1110: system clock divided by 256
 * 1111: system clock divided by 512
 */
#define AHB_PRESCALER 0b1000

/*
 * 0xx: AHB clock not divided
 * 100: AHB clock divided by 2
 * 101: AHB clock divided by 4
 * 110: AHB clock divided by 8
 * 111: AHB clock divided by 16
 */
#define APB1_PRESCALER 0b100
#define APB2_PRESCALER 0


/* 2 - 3 - 4 - .....63 */
#define PLLM_VALUE	25

/* 50 ..... 432 */
#define PLLN_VALUE	160

/* 2 - 3 - 4 - ...... 15 */
#define PLLQ_VALUE 2

/*
 * 00: PLLP = 2
 * 01: PLLP = 4
 * 10: PLLP = 6
 * 11: PLLP = 8
 */
#define PLLP_VALUE 2
#endif /* RCC_CONFIGURATION_H_ */
