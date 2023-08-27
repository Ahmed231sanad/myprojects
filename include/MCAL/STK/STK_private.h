/*
 * STK_private.h

 *
 *  Created on: 11/8/2023þ
 *      Author: Ahmedsanad
 */

#ifndef STK_PRIVATE_H_
#define STK_PRIVATE_H_

typedef struct{
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
	volatile u32 CALIB;
}STK_t;

#define STK ((volatile STK_t *) 0xE000E010)


typedef enum{
	SINGLE_INTERVAL=0,
	PERIODIC_INTERVAL
}IntervalType_e;




#endif /* STK_PRIVATE_H_ */
