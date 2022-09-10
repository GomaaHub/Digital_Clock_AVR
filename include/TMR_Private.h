/*
 * TMR_Private.h
 *
 *  Created on: May 2, 2022
 *      Author: Ahmad
 */

#ifndef TMR_PRIVATE_H_
#define TMR_PRIVATE_H_

#define TIMSK_REG	*((volatile u8*)0x59)

/***************************************TIMER0 REGISTERS AND MACROS****************************************/

#define TCCR0_REG	*((volatile u8*)0x53)
#define TCNT0_REG 	*((volatile u8*)0x52)
#define OCR0_REG	*((volatile u8*)0x5C)


#define CS00		0
#define CS01		1
#define CS02		2
#define WGM01		3
#define	COM00		4
#define COM01		5
#define WGM00		6
#define FOC0		7
#define TOIE0		0
#define OCIE0		1

/**********************************************TIMER1 REGISTERS*******************************************/

//#define TCCR0_REG	*((volatile u8*)0x53)
//#define TCNT0_REG *((volatile u8*)0x52)
//#define OCR0_REG	*((volatile u8*)0x5C)

/**********************************************TIMER2 REGISTERS*******************************************/

#define TCCR2_REG	*((volatile u8*)0x45)
#define TCNT2_REG 	*((volatile u8*)0x44)
#define OCR2_REG	*((volatile u8*)0x43)


#define CS20		0
#define CS21		1
#define CS22		2
#define WGM21		3
#define	COM20		4
#define COM21		5
#define WGM20		6
#define FOC2		7
#define TOIE2		6
#define OCIE2		7



#endif /* TMR_PRIVATE_H_ */
