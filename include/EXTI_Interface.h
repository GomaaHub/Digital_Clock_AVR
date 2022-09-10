/*
 * EXTI_Interface.h
 *
 *  Created on: Apr 28, 2022
 *      Author: Ahmad
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

void GLOBAL_INTERRUPT_ENABLE(void);
void EXTI_ENABLE(u8 INT_NUM);

#define INT0		6
#define INT1		7
#define INT2		5

#define ISC00		0
#define ISC01		1
#define ISC10		2
#define ISC11		3
#define ISC2		6

#define LOW_LEVEL			0
#define LOGICAL_CHANGE		1
#define FALLING_EDGE		2
#define RISING_EDGE			3




#endif /* EXTI_INTERFACE_H_ */
