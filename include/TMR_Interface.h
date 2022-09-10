/*
 * TMR_Interface.h
 *
 *  Created on: May 2, 2022
 *      Author: Ahmad
 */

#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_


void TMR0_Init(u8 MODE, u8 CTC_MODE, u8 CLOCK_SELECT);
void TMR0_TCNTSet(u8 start);
void TMR0_OCRSet(u8 ocr0);
void TMR2_Init(u8 MODE, u8 OC0_MODE, u8 CLOCK_SELECT);
void TMR2_TCNTSet(u8 start);
void TMR2_OCRSet(u8 ocr2);
void TMR0_Start (u8 MODE);
void TMR2_Start (u8 MODE);


#define NORMAL		0
#define PWM_PC		1
#define CTC			2
#define FAST_PWM	3
#define NORMAL_MODE	1
#define OC_MODE		2

#define TOGGLE_OC0	1
#define CLEAR_OC0	2
#define SET_OC0		3

#define NO_CLOCK			0
#define CLOCK_NO_PRESCALE	1
#define CLOCK_8				2
#define CLOCK_64			3
#define CLOCK_256			4
#define CLOCK_1024			5
#define EXT_CLOCK_FALL		6
#define EXT_CLOCK_RISE		7

#define NO_CLOCK				0
#define CLOCK_NO_PRESCALE		1
#define TMR2_CLOCK_8			2
#define TMR2_CLOCK_32			3
#define TMR2_CLOCK_64			4
#define TMR2_CLOCK_128			5
#define TMR2_CLOCK_256			6
#define TMR2_CLOCK_1024			7



#endif /* TMR_INTERFACE_H_ */
