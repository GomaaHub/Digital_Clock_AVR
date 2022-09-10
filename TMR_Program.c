#include "Library/types.h"
#include "DIO_Interface.h"
#include "TMR_Private.h"
#include "TMR_Interface.h"
#include "KPD_Interface.h"
#include "avr/interrupt.h"

u16 while_counter=0;
u32 OV_COUNTS=0;
u8 SECONDS=40;
u8 MINUTES=58;
u8 HOURS=11;
u8 DAY=4;
u8 MONTH=5;

u8 ALARM=1;
u8 meridiem=0;
u16 YEAR=2022;
u8 ringtone=1;

u8 HOURS_ALARM=11;
u8 MINUTES_ALARM=59;
u8 SECONDS_ALARM=0;
u8 meridiem_alarm=0;



void TMR0_Start (u8 MODE)
{
	TIMSK_REG &=0b11111100;
	TIMSK_REG |= (MODE << TOIE0);
}

void TMR0_Init(u8 MODE, u8 OC0_MODE, u8 CLOCK_SELECT)
{
	MODE &= 0x03;
	OC0_MODE &= 0x03;
	CLOCK_SELECT &= 0x07;


	switch(MODE)
	{
		case 0:
		{
			TCCR0_REG &= ~(1 << WGM00);
			TCCR0_REG &= ~(1 << WGM01);
			break;
		}
		case 1:
		{
			TCCR0_REG |=  (1 << WGM00);
			TCCR0_REG &= ~(1 << WGM01);
			break;
		}
		case 2:
		{
			TCCR0_REG &= ~(1 << WGM00);
			TCCR0_REG |=  (1 << WGM01);
			break;
		}
		case 3:
		{
			TCCR0_REG |= (1 << WGM00);
			TCCR0_REG |= (1 << WGM01);
			break;
		}
	}

		TCCR0_REG &= 0b11001111;
		TCCR0_REG |= (OC0_MODE << COM00);

		TCCR0_REG &= 0b11111000;
		TCCR0_REG |= CLOCK_SELECT;
}

void TMR0_TCNTSet(u8 start)
{
	TCNT0_REG = start;
}

void TMR0_OCRSet(u8 ocr0)
{
	OCR0_REG = ocr0;
}

/********************************************TIMER 2 DRIVERS********************************************/
void TMR2_Start (u8 MODE)
{
	TIMSK_REG &=0b00111111;
	TIMSK_REG |= (MODE << TOIE2);
}
void TMR2_Init(u8 MODE, u8 OC0_MODE, u8 CLOCK_SELECT)
{
	MODE &= 0x03;
	OC0_MODE &= 0x03;
	CLOCK_SELECT &= 0x07;

	switch(MODE)
	{
		case 0:
		{
			TCCR2_REG &= ~(1 << WGM20);
			TCCR2_REG &= ~(1 << WGM21);
			break;
		}
		case 1:
		{
			TCCR2_REG |=  (1 << WGM20);
			TCCR2_REG &= ~(1 << WGM21);
			break;
		}
		case 2:
		{
			TCCR2_REG &= ~(1 << WGM20);
			TCCR2_REG |=  (1 << WGM21);
			break;
		}
		case 3:
		{
			TCCR2_REG |= (1 << WGM20);
			TCCR2_REG |= (1 << WGM21);
			break;
		}
	}

		TCCR2_REG &= 0b11001111;
		TCCR2_REG |= (OC0_MODE << COM20);

		TCCR2_REG &= 0b11111000;
		TCCR2_REG |= CLOCK_SELECT;
}

void TMR2_TCNTSet(u8 start)
{
	TCNT2_REG = start;
}

void TMR2_OCRSet(u8 ocr2)
{
	OCR2_REG = ocr2;
}

ISR(TIMER0_OVF_vect)
{
	OV_COUNTS++;
	while_counter++;

	if(OV_COUNTS==489)
	{
		TMR0_TCNTSet(184);
		SECONDS++;
		OV_COUNTS=0;
		while_counter=0;
	}

	if(SECONDS==60)
	{
		SECONDS=0;
		MINUTES++;
	}

	if(MINUTES==60)
	{
		MINUTES=0;
		HOURS++;
	}

	if(HOURS==12 && MINUTES==0 && SECONDS==0 && meridiem==0 && OV_COUNTS==0)
	{
		meridiem=1;
	}

	else if(HOURS==12  && MINUTES==0 && SECONDS==0 && meridiem==1 && OV_COUNTS==0)
	{
		DAY++;
		meridiem=0;
	}

	if(HOURS==13)
	{
		HOURS=1;
	}

	if((DAY==30) && (MONTH==2) && (YEAR%4==0))
	{
		MONTH++;
		DAY=1;
	}

	if((DAY==29) && (MONTH==2) && (YEAR%4!=0))
	{
		MONTH++;
		DAY=1;
	}

	if(DAY==31 && (MONTH==4 || MONTH==6 || MONTH==9 || MONTH==11))
	{
		MONTH++;
		DAY=1;
	}

	if(DAY>31 && (MONTH==1 || MONTH==3 || MONTH==5 || MONTH==7 || MONTH==8|| MONTH==10 || MONTH==12))
	{
		MONTH++;
		DAY=1;
	}

	if(MONTH==13)
	{
		MONTH=1;
		DAY=1;
		YEAR++;
	}
}





