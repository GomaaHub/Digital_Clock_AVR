#include "Library/types.h"
#include "DIO_Interface.h"
#include "EXTI_Interface.h"
#include "EXTI_Private.h"
#include <avr/interrupt.h>
#include <avr/delay.h>



void GLOBAL_INTERRUPT_ENABLE(void)
{
	SREG_REG |= (1 << 7);
}

void EXTI_ENABLE(u8 EXTI_NUM)
{
	switch(EXTI_NUM)
	{
		case 0: GICR_REG |= (1 << INT0); break;
		case 1: GICR_REG |= (1 << INT1); break;
		case 2: GICR_REG |= (1 << INT2); break;
	}
}

void EXTI_SENSE_CONTROL(u8 EXTI_NUM,u8 MODE)
{
	EXTI_NUM &= (0x03);
	MODE &= (0x03);

	switch(EXTI_NUM)
	{
		case 0: MCUCR_REG |= (MODE << ISC00); break;
		case 1: MCUCR_REG |= (MODE << ISC10); break;
		case 2:
		{
			if(MODE==0 || MODE==1)
			{
				MODE=0;
			}
			else if(MODE==2)
			{
				MODE=0;
			}
			else if(MODE==3)
			{
				MODE=1;
			}

			MCUCSR_REG |= (MODE << ISC2);

			break;
		}
	}
}

ISR(INT0_vect)
{
	DIO_SetPortValue(DIO_PORTA,0x00);

	u8 i;
	do
				{
					for(i=0;i<4;i++)
					{

						DIO_SetPinValue(DIO_PORTA,i,DIO_HIGH);
						DIO_SetPinValue(DIO_PORTA,7-i,DIO_HIGH);

						_delay_ms(300);
						DIO_SetPinValue(DIO_PORTA,i,DIO_LOW);
						DIO_SetPinValue(DIO_PORTA,7-i,DIO_LOW);

					}
					for(i=2;i>=0;i--)
					{


						DIO_SetPinValue(DIO_PORTA,i,DIO_HIGH);
						DIO_SetPinValue(DIO_PORTA,7-i,DIO_HIGH);

						_delay_ms(300);
						DIO_SetPinValue(DIO_PORTA,i,DIO_LOW);
						DIO_SetPinValue(DIO_PORTA,7-i,DIO_LOW);
						if(i==1)
							break;
					}
				i=0;

				}while(1);

	GIFR &= ~(1<<6);
}

ISR(INT1_vect)
{
	DIO_SetPortValue(DIO_PORTA,0x00);

	u8 i;

	do{
				for(i=0;i<8;i++)
				{

					DIO_SetPinValue(DIO_PORTA,i,DIO_HIGH);

					_delay_ms(250);
					DIO_SetPinValue(DIO_PORTA,i,DIO_LOW);



				}
				for(i=6;i>=0;i--)
				{

					DIO_SetPinValue(DIO_PORTA,i,DIO_HIGH);

					_delay_ms(250);
					DIO_SetPinValue(DIO_PORTA,i,DIO_LOW);


					if(i==1)
						break;

				}
				i=0;
				}while(1);

	GIFR &= ~(1<<7);

}

ISR(INT2_vect)
{
	DIO_SetPortValue(DIO_PORTA,0x00);

	u8 i;

	while(1)
		{

			for(i=0;i<8;i++)
				{
					DIO_SetPinValue(DIO_PORTA,i,DIO_HIGH);
					_delay_ms(200);
				}

			for(i=7;i>=-1;i--)
			{
				DIO_SetPinValue(DIO_PORTA,i,DIO_LOW);
				_delay_ms(200);

				if(i==0)
					break;
			}
		}

	GIFR &= ~(1<<5);
}
