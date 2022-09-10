/*
 * EXIT_Private.h
 *
 *  Created on: Apr 28, 2022
 *      Author: Ahmad
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define	MCUCR_REG	*((volatile u8*)0x55)
#define	MCUCSR_REG	*((volatile u8*)0x54)
#define	GICR_REG	*((volatile u8*)0x5B)
#define	GIFR_REG	*((volatile u8*)0x5A)
#define SREG_REG	*((volatile u8*)0x5F)



#define INT0		6
#define INT1		7
#define INT2		5

#endif /* EXTI_PRIVATE_H_ */
