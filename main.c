#include "Library/types.h"
#include "Library/bit_math.h"
#include "include/DIO_Interface.h"
#include "include/LCD_Interface.h"
#include "include/LCD_CustomChar.h"
#include "include/EXTI_Interface.h"
#include "include/KPD_Interface.h"
#include "include/TMR_Interface.h"
#include "include/CLK_Interface.h"
#include "avr/delay.h"
#include "avr/interrupt.h"


u8 key=0;


int main(void)
{
	DIO_SetPortDirection(DIO_PORTB,0xFF);	// LCD PORT
	DIO_SetPortDirection(DIO_PORTA,0xFF);	// LEDs PORT
	DIO_SetPortDirection(DIO_PORTC,0x0F);	// KPD PORT
	DIO_SetPortValue(DIO_PORTC,0xF0);		// Enable pull-up resistors for KPD


	LCD_Init();

	GLOBAL_INTERRUPT_ENABLE();
	TMR0_Init(NORMAL,NORMAL,CLOCK_64);

	TMR0_TCNTSet(184);

	TMR0_Start(NORMAL_MODE);


	LCD_DISPLAY_CONTROL(1,1,1);
	LCD_CLEAR();

	LCD_CreateNewChar(calendar_shape0,0);
	LCD_GoToXY(0,0);
	LCD_CreateNewChar(calendar_shape1,1);
	LCD_GoToXY(0,0);
	LCD_CreateNewChar(calendar_shape2,2);
	LCD_GoToXY(0,0);
	LCD_CreateNewChar(calendar_shape3,3);
	LCD_GoToXY(0,0);
	LCD_CreateNewChar(calendar_shape4,4);
	LCD_GoToXY(0,0);
	LCD_CreateNewChar(calendar_shape5,5);
	LCD_GoToXY(0,0);


	LCD_GoToXY(0,0);
	LCD_Print_Char(0);
	LCD_Print_Char(1);
	LCD_Print_Char(2);

	LCD_GoToXY(0,1);
	LCD_Print_Char(3);
	LCD_Print_Char(4);
	LCD_Print_Char(5);

	while(1)
	{
		key=KPD_GET_KEY_PRESSED();

		if(key!=NOT_PRESSED)
		{
			if(key=='1')
			SetTime();

			if(key=='2')
			SetCalendar();

			if(key=='3')
			SetAlarm();

			if(key=='4')
			TurnOnAlarm();

			if(key=='5')
			TurnOffAlarm();

			if(key=='6')
			AlarmTone();

			if(key=='=')
			continue;
		}

		PrintTime();
		PrintCalendar();
		CheckAlarm();
	}

	return 0;
}

