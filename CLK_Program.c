#include "Library/types.h"
#include "Library/bit_math.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "EXTI_Interface.h"
#include "KPD_Interface.h"
#include "TMR_Interface.h"
#include "avr/delay.h"
#include "avr/interrupt.h"



extern u16 while_counter;
extern u8 SECONDS;
extern u8 MINUTES;
extern u8 HOURS;
extern u8 DAY;
extern u8 MONTH;
extern u8 key;
extern u8 ALARM;
extern u8 meridiem;
extern u16 YEAR;
extern u8 ringtone;

extern u8 HOURS_ALARM;
extern u8 MINUTES_ALARM;
extern u8 SECONDS_ALARM;
extern u8 meridiem_alarm;

void PrintTime(void)
{
	LCD_DISPLAY_CONTROL(1,0,0);
	LCD_GoToXY(0,0);
	LCD_Print_Char(0);
	LCD_Print_Char(1);
	LCD_Print_Char(2);

	LCD_GoToXY(0,1);
	LCD_Print_Char(3);
	LCD_Print_Char(4);
	LCD_Print_Char(5);
	LCD_GoToXY(4,0);

			if(HOURS < 10)
			{
				LCD_Print_Integer(HOURS);
			}
			else if(HOURS > 9 && HOURS < 13)
			{
				LCD_Print_Integer(HOURS);
			}

			LCD_Print_Char(':');

			if(MINUTES==0)
			{
				LCD_Print_String("00");
			}
			else if(MINUTES > 0 && MINUTES < 10 )
			{
				LCD_Print_Char('0');
				LCD_Print_Integer(MINUTES);
			}
			else if(MINUTES > 9)
			{
				LCD_Print_Integer(MINUTES);
			}

			LCD_Print_Char(':');



			if(SECONDS < 10)
			{
				LCD_Print_Char('0');
				LCD_Print_Integer(SECONDS);
			}
			else if(SECONDS >= 10 && SECONDS < 60)
			{
				LCD_Print_Integer(SECONDS);
			}

			LCD_Print_Char(' ');

			if(meridiem==0)
			{
				LCD_Print_String("AM");
			}
			else if(meridiem==1)
			{
				LCD_Print_String("PM");
			}

			if(HOURS<10)
			LCD_Print_String("  ");

			if(HOURS>9)
			LCD_Print_Char(' ');


}

void PrintCalendar(void)
{
	LCD_GoToXY(4,1);


	LCD_Print_Integer(DAY);

	LCD_Print_Char('/');

	LCD_Print_Integer(MONTH);

	LCD_Print_Char('/');

	LCD_Print_Year(YEAR);

	if(DAY < 10 || MONTH < 10)
		LCD_Print_Char(' ');

	if(DAY < 10 && MONTH < 10)
	{
		LCD_Print_Char(' ');
		LCD_Print_Char(' ');
	}

}

void SetTime(void)
{
	u8 i=3;

	s8 hours[2]={HOURS/10,HOURS%10};
	s8 minutes[2]={MINUTES/10,MINUTES%10};
	s8 seconds[2]={SECONDS/10,SECONDS%10};





		 LCD_CLEAR();
		 LCD_DISPLAY_CONTROL(1,1,0);
		 LCD_GoToXY(0,0);
		 LCD_Print_String("    SET CLOCK   ");
		 LCD_GoToXY(0,1);
		 LCD_Print_String("   ");
		 LCD_Print_Integer(hours[0]);
		 LCD_Print_Integer(hours[1]);
		 LCD_Print_Char(':');
		 LCD_Print_Integer(minutes[0]);
		 LCD_Print_Integer(minutes[1]);
		 LCD_Print_Char(':');
		 LCD_Print_Integer(seconds[0]);
		 LCD_Print_Integer(seconds[1]);
		 LCD_Print_Char(' ');

		 if(meridiem==0)
		 LCD_Print_Char('A');

		 if(meridiem==1)
		 LCD_Print_Char('P');

		 LCD_Print_Char('M');

		 while(1)
		 {

			 LCD_GoToXY(i,1);
			 key=KPD_GET_KEY_PRESSED();

			 if(key=='6')
			 {
				 i++;

				 if(i==5 || i==8 || i==11)
					 i++;

				 if(i>12)
					 i=3;

				 LCD_GoToXY(i,1);
			 }

			 if(key=='4')
			 {
			 	 i--;

			 	 if(i==5 || i==8 || i==11)
			 		 i--;

			 	 if(i<3)
			 		i=12;

			 	 LCD_GoToXY(i,1);
			 }

			 if(key=='-')
			 {
				 LCD_DISPLAY_CONTROL(1,0,1);

				 while(1)
				 {
					 key=KPD_GET_KEY_PRESSED();
					 if(key=='2')
					 {
					  switch(i)
					 	 {
					  	   case 3:
					  		   {
					  			  hours[0]+=1;

					  			 if(hours[1]==0 && hours[0]==0)
								 {
									 hours[1]=1;
									 LCD_GoToXY(i+1,1);
									 LCD_Print_Integer(hours[1]);
									 LCD_GoToXY(i,1);
								 }

					  			  if(hours[0]>1)
					  				  hours[0]=0;

					  			  if(hours[1]>2 && hours[0]==1)
					  			  {
					  				  hours[1]=2;
					  				  LCD_GoToXY(i+1,1);
					  				  LCD_Print_Integer(hours[1]);
					  				  LCD_GoToXY(i,1);
					  			  }
					  			  LCD_Print_Integer(hours[0]);
					  			  LCD_GoToXY(i,1);
					  			  break;
					  		   }
					  	   case 4:
					  		   {
					  			   hours[1]+=1;

					  			 if(hours[0]==0 && hours[1]>9)
									 hours[1]=1;

					  			   if(hours[0]==1 && hours[1]>2)
					  				   hours[1]=0;

					  			   if(hours[1]>9)
					  				   hours[1]=0;

					  			   LCD_Print_Integer(hours[1]);
					  			   LCD_GoToXY(i,1);
					  			   break;
					  		   }
					  	   case 6:
					  		   {
					  			   minutes[0]+=1;

					  			   if(minutes[0] > 5)
					  				   minutes[0]=0;

					  			   LCD_Print_Integer(minutes[0]);
					  			   LCD_GoToXY(i,1);
					  			   break;
					  		   }
					  	   case 7:
					  		   {
					  			   minutes[1]+=1;

					  			 if(minutes[1] > 9)
								     minutes[1]=0;

					  			   LCD_Print_Integer(minutes[1]);
					  			   LCD_GoToXY(i,1);
					  			   break;
					  		   }
					  	   case 9:
					  		   {
					  			   seconds[0]+=1;

					  			   if(seconds[0]>5)
					  				   seconds[0]=0;

					  			   LCD_Print_Integer(seconds[0]);
					  			   LCD_GoToXY(i,1);
					  			   break;
					  		   }
					  	   case 10:
					  		   {
					  			   seconds[1]+=1;

					  			 if(seconds[1]>9)
									   seconds[1]=0;

					  			   LCD_Print_Integer(seconds[1]);
					  			   LCD_GoToXY(i,1);
					  			   break;
					  		   }
					  	 case 12:
							 {
								 meridiem^=1;

								 if(meridiem==0)
								 LCD_Print_Char('A');

								 if(meridiem==1)
									 LCD_Print_Char('P');

								 LCD_GoToXY(i,1);
								break;
							 }
					 	 }
					 }
					 else if(key=='8')
					 {
						 switch(i)
						 {
						 case 3:
							 {
								 hours[0]-=1;



								 if(hours[1]==0 && hours[0]==0)
								 {
									 hours[1]=1;
									 LCD_GoToXY(i+1,1);
								     LCD_Print_Integer(hours[1]);
								     LCD_GoToXY(i,1);
								 }

								 if(hours[0]==-1)
									 hours[0]=1;

								 if(hours[1]>2 && hours[0]==1)
								  {
									  hours[1]=2;
									  LCD_GoToXY(i+1,1);
									  LCD_Print_Integer(hours[1]);
									  LCD_GoToXY(i,1);
								  }
								 LCD_Print_Integer(hours[0]);
								 LCD_GoToXY(i,1);
								 break;
							 }
					     case 4:
					    	 {
					    		 hours[1]-=1;

					    		 if(hours[0]==1 && hours[1]<0)
								   hours[1]=2;

					    		 if(hours[1]==-1)
								   hours[1]=9;

					    		 if(hours[0]==0 && hours[1]<1)
					    			 hours[1]=9;

					    		 LCD_Print_Integer(hours[1]);
					    		 LCD_GoToXY(i,1);
					    		 break;
					    	 }
					     case 6:
					    	 {
					    		 minutes[0]-=1;

					    		 if(minutes[0]==-1)
					    			 minutes[0]=5;

					    		 LCD_Print_Integer(minutes[0]);
					    		 LCD_GoToXY(i,1);
					    		 break;
					    	 }
					     case 7:
					    	 {
					    		 minutes[1]-=1;

					    		 if(minutes[1]==-1)
					    			 minutes[1]=9;

					    		 LCD_Print_Integer(minutes[1]);
					    		 LCD_GoToXY(i,1);
					    		 break;
					    	 }
					     case 9:
					    	 {
					    		 seconds[0]-=1;

					    		 if(seconds[0]==-1)
					    			 seconds[0]=5;

					    		 LCD_Print_Integer(seconds[0]);
					    		 LCD_GoToXY(i,1);
					    		 break;
					    	 }
					     case 10:
					    	 {
					    		 seconds[1]-=1;

					    		 if(seconds[1]==-1)
					    			 seconds[1]=9;

					    		 LCD_Print_Integer(seconds[1]);
					    		 LCD_GoToXY(i,1);
					    		 break;
					    	 }
					     case 12:
					     {
					    	 meridiem^=1;

					    	 if(meridiem==0)
					    	 LCD_Print_Char('A');

					    	 if(meridiem==1)
					    		 LCD_Print_Char('P');

					    	 LCD_GoToXY(i,1);
					    	break;
					     }

						 }
					 }

					  if(key=='-')
					  {
						  LCD_DISPLAY_CONTROL(1,1,0);
						  break;
					  }

				 }
			 }

			 if(key=='=')
				 break;
		 }

		 HOURS=(hours[0]*10) + (hours[1]);
		 MINUTES=(minutes[0]*10)+(minutes[1]);
		 SECONDS=(seconds[0]*10)+(seconds[1]);

		LCD_CLEAR();
		LCD_GoToXY(0,0);
		LCD_Print_Char(0);
		LCD_Print_Char(1);
		LCD_Print_Char(2);

		LCD_GoToXY(0,1);
		LCD_Print_Char(3);
		LCD_Print_Char(4);
		LCD_Print_Char(5);

}

void SetCalendar(void)
{
	u8 i=3;

	s8 day[2]={DAY/10,DAY%10};
	s8 month[2]={MONTH/10,MONTH%10};
	s8 year[4]={YEAR/1000,(YEAR%1000)/100,(YEAR%100)/10,YEAR%10};





		 LCD_CLEAR();
		 LCD_DISPLAY_CONTROL(1,1,0);
		 LCD_GoToXY(0,0);
		 LCD_Print_String("    SET DATE  ");
		 LCD_GoToXY(0,1);
		 LCD_Print_String("   ");
		 LCD_Print_Integer(day[0]);
		 LCD_Print_Integer(day[1]);
		 LCD_Print_Char('/');
		 LCD_Print_Integer(month[0]);
		 LCD_Print_Integer(month[1]);
		 LCD_Print_Char('/');
		 LCD_Print_Integer(year[0]);
		 LCD_Print_Integer(year[1]);
		 LCD_Print_Integer(year[2]);
		 LCD_Print_Integer(year[3]);
		 LCD_Print_Char(' ');
		 LCD_Print_Char(' ');

		 while(1)
		 {


			 LCD_GoToXY(i,1);
			 key=KPD_GET_KEY_PRESSED();

			 if(key=='6')
			 {
				 i++;

				 if(i==5 || i==8)
					 i++;

				 if(i>12)
					 i=3;

				 LCD_GoToXY(i,1);
			 }

			 if(key=='4')
			 {
			 	 i--;

			 	 if(i==5 || i==8)
			 		 i--;

			 	 if(i<3)
			 		i=12;

			 	 LCD_GoToXY(i,1);
			 }

			 if(key=='-')
			 {
				 LCD_DISPLAY_CONTROL(1,0,1);

				 while(1)
				 {
					 key=KPD_GET_KEY_PRESSED();
					 if(key=='2')
					 {
					  switch(i)
					 	 {
					  	   case 3:
					  		   {
					  			  day[0]+=1;

					  			  if(day[0]==4)
					  				  day[0]=0;

					  			if(day[1]==0 && day[0]==0)
								 {
									 day[1]=1;
									 LCD_GoToXY(i+1,1);
									 LCD_Print_Integer(day[1]);
								 }

					  			  LCD_GoToXY(i,1);

					  			if(day[1]>1 && day[0]==3 && (MONTH==1 ||MONTH==3 || MONTH==5 ||MONTH==7||MONTH==8||MONTH==10||MONTH==12))
								   {
									 day[1]=1;
									LCD_GoToXY(i+1,1);
									LCD_Print_Integer(day[1]);

								   }

								  LCD_GoToXY(i,1);

								  if(day[1]>1 && day[0]==3 && (MONTH==4 || MONTH==6 || MONTH==9 || MONTH==11))
								   {
									 day[1]=0;
									LCD_GoToXY(i+1,1);
									LCD_Print_Integer(day[1]);

								   }

								  LCD_GoToXY(i,1);

								  if(day[1]>-1 && day[0]==3 && MONTH==2 && (YEAR%4==0))
								   {
									 day[1]=9;
									 day[0]=2;
									LCD_GoToXY(i+1,1);
									LCD_Print_Integer(day[1]);

								   }

								  LCD_GoToXY(i,1);

								  if(day[1]>-1 && day[0]==3 && MONTH==2 && (YEAR%4!=0))
								   {
									 day[1]=8;
									 day[0]=2;
									LCD_GoToXY(i+1,1);
									LCD_Print_Integer(day[1]);

								   }
								  LCD_GoToXY(i,1);
					  			  LCD_Print_Integer(day[0]);
					  			  LCD_GoToXY(i,1);
					  			DAY=(day[0]*10) + (day[1]);
					  			  break;

					  		   }
					  	   case 4:
					  		   {
					  			   day[1]+=1;

					  			   if(day[0]==3 && day[1]>1)
					  				   day[1]=0;

					  			   if((day[0]==1 || day[0]==2) && day[1] > 9)
					  				   day[1]=0;

					  			   if(day[0]==0 && day[1]>9)
					  				   day[1]=1;

					  			   LCD_Print_Integer(day[1]);
					  			   LCD_GoToXY(i,1);
					  			 DAY=(day[0]*10) + (day[1]);
					  			   break;
					  		   }
					  	   case 6:
					  		   {
					  			   month[0]+=1;

					  			 if(month[0]==0 && month[1]==2 && day[0]>2 && (YEAR%4==0))
								   {
									   day[0]=2;
									   day[1]=9;
									   LCD_GoToXY(3,1);
									   LCD_Print_Integer(day[0]);
									   LCD_GoToXY(4,1);
									   LCD_Print_Integer(day[1]);
									   LCD_GoToXY(i,1);
								   }

								 if(month[0]==0 && month[1]==2 && day[0]>2 && (YEAR%4!=0))
								   {
									   day[0]=2;
									   day[1]=8;
									   LCD_GoToXY(3,1);
									   LCD_Print_Integer(day[0]);
									   LCD_GoToXY(4,1);
									   LCD_Print_Integer(day[1]);
									   LCD_GoToXY(i,1);
								   }
								 if(month[0]==0 && (month[1]==4 ||(month[0]==1 && month[1]==1) ||month[1]==4||month[1]==9) && (day[0]>2 && day[1]>0))
								   {
									   day[0]=3;
									   day[1]=0;
									   LCD_GoToXY(3,1);
									   LCD_Print_Integer(day[0]);
									   LCD_GoToXY(4,1);
									   LCD_Print_Integer(day[1]);
									   LCD_GoToXY(i,1);
								   }
					  			   if(month[0] > 1)
					  				   month[0]=0;

					  			   if(month[0]==0 && month[1]==0)
					  				   {
					  				   	 month[1]=1;
					  				   	 LCD_GoToXY(i+1,1);
					  				   	 LCD_Print_Integer(month[1]);
					  				   }
					  			   LCD_GoToXY(i,1);

					  			   if(month[1]>2 && month[0]==1)
					  			   {
					  				 month[1]=2;
					  				LCD_GoToXY(i+1,1);
					  				LCD_Print_Integer(month[1]);

					  			   }
					  			   LCD_GoToXY(i,1);
					  			   LCD_Print_Integer(month[0]);
					  			   LCD_GoToXY(i,1);
					  			 MONTH=(month[0]*10)+(month[1]);
					  			   break;
					  		   }
					  	   case 7:
					  		   {
					  			   month[1]+=1;

					  			   if(month[0]==0 && month[1]==2 && day[0]>2 && (YEAR%4==0))
					  			   {
					  				   day[0]=2;
					  				   day[1]=9;
					  				   LCD_GoToXY(3,1);
					  				   LCD_Print_Integer(day[0]);
					  				   LCD_GoToXY(4,1);
					  				   LCD_Print_Integer(day[1]);
					  				   LCD_GoToXY(i,1);
					  			   }

					  			 if(month[0]==0 && month[1]==2 && day[0]>2 && (YEAR%4!=0))
								   {
									   day[0]=2;
									   day[1]=8;
									   LCD_GoToXY(3,1);
									   LCD_Print_Integer(day[0]);
									   LCD_GoToXY(4,1);
									   LCD_Print_Integer(day[1]);
									   LCD_GoToXY(i,1);
								   }
					  			 if(month[0]==0 && (month[1]==4 ||(month[0]==1 && month[1]==1) ||month[1]==4||month[1]==9) && (day[0]>2 && day[1]>0))
					  										   {
					  											   day[0]=3;
					  											   day[1]=0;
					  											   LCD_GoToXY(3,1);
					  											   LCD_Print_Integer(day[0]);
					  											   LCD_GoToXY(4,1);
					  											   LCD_Print_Integer(day[1]);
					  											   LCD_GoToXY(i,1);
					  										   }
					  			 if(month[0]==0 && month[1] > 9)
								     month[1]=1;

					  			 if(month[0]==1 && month[1]>2)
					  				 month[1]=0;

					  			   LCD_Print_Integer(month[1]);
					  			   LCD_GoToXY(i,1);
					  			 MONTH=(month[0]*10)+(month[1]);
					  			   break;
					  		   }
					  	   case 9:
					  		   {
					  			   year[0]+=1;

					  			   if(year[0]>9)
					  				   year[0]=0;

					  			   LCD_Print_Integer(year[0]);
					  			   LCD_GoToXY(i,1);
					  			 YEAR=(year[0]*1000)+(year[1]*100)+(year[2]*10)+(year[3]);
					  			   break;
					  		   }
					  	   case 10:
					  		   {
					  			   year[1]+=1;

					  			 if(year[1]>9)
									   year[1]=0;

					  			   LCD_Print_Integer(year[1]);
					  			   LCD_GoToXY(i,1);
					  			 YEAR=(year[0]*1000)+(year[1]*100)+(year[2]*10)+(year[3]);
					  			   break;
					  		   }
					  	   case 11:
					  	   { year[2]+=1;

				  			 if(year[2]>9)
								   year[2]=0;

				  			   LCD_Print_Integer(year[2]);
				  			   LCD_GoToXY(i,1);
				  			 YEAR=(year[0]*1000)+(year[1]*100)+(year[2]*10)+(year[3]);
					  		   break;
					  	   }
					  	   case 12:
					  	   {
					  		 year[3]+=1;

							 if(year[3]>9)
								   year[3]=0;

							   LCD_Print_Integer(year[3]);
							   LCD_GoToXY(i,1);
							   YEAR=(year[0]*1000)+(year[1]*100)+(year[2]*10)+(year[3]);
					  		   break;
					  	   }
					 	 }
					 }
					 else if(key=='8')
					 {
						 switch(i)
						 {
						 case 3:
							 {
								 day[0]-=1;

								 if(day[0]==-1)
									 day[0]=3;

								 if(day[1]==0 && day[0]==0)
								 {
									 day[1]=1;
									 LCD_GoToXY(i+1,1);
									 LCD_Print_Integer(day[1]);
								 }
								 LCD_GoToXY(i,1);

								 if(day[1]>1 && day[0]==3 && (MONTH==1 ||MONTH==3 || MONTH==5 ||MONTH==7||MONTH==8||MONTH==10||MONTH==12))
								   {
									 day[1]=1;
									LCD_GoToXY(i+1,1);
									LCD_Print_Integer(day[1]);

								   }

								  LCD_GoToXY(i,1);

								  if(day[1]>1 && day[0]==3 && (MONTH==4 || MONTH==6 || MONTH==9 || MONTH==11))
								   {
									 day[1]=0;
									LCD_GoToXY(i+1,1);
									LCD_Print_Integer(day[1]);

								   }

								  LCD_GoToXY(i,1);

								  if(day[1]>-1 && day[0]==3 && MONTH==2 && (YEAR%4==0))
								   {
									 day[1]=9;
									 day[0]=2;
									LCD_GoToXY(i+1,1);
									LCD_Print_Integer(day[1]);

								   }

								  LCD_GoToXY(i,1);

								  if(day[1]>-1 && day[0]==3 && MONTH==2 && (YEAR%4!=0))
								   {
									 day[1]=8;
									 day[0]=2;
									LCD_GoToXY(i+1,1);
									LCD_Print_Integer(day[1]);

								   }


								 LCD_GoToXY(i,1);
								 LCD_Print_Integer(day[0]);
								 LCD_GoToXY(i,1);
								 DAY=(day[0]*10) + (day[1]);
								 break;
							 }
					     case 4:
					    	 {
					    		 day[1]-=1;

					    		 if(day[1]==-1 && day[0]==3)
								   day[1]=1;

					    		 if(day[1]==-1 && (day[0]==1 || day[0]==2))
								   day[1]=9;

					    		 if(day[1]==0 && day[0]==0)
								   day[1]=9;



					    		 LCD_Print_Integer(day[1]);
					    		 LCD_GoToXY(i,1);
					    		 DAY=(day[0]*10) + (day[1]);
					    		 break;
					    	 }
					     case 6:
					    	 {
					    		 month[0]-=1;

					    		 if(month[0]==0 && month[1]==2 && day[0]>2 && (YEAR%4==0))
							   {
								   day[0]=2;
								   day[1]=9;
								   LCD_GoToXY(3,1);
								   LCD_Print_Integer(day[0]);
								   LCD_GoToXY(4,1);
								   LCD_Print_Integer(day[1]);
								   LCD_GoToXY(i,1);
							   }

							 if(month[0]==0 && month[1]==2 && day[0]>2 && (YEAR%4!=0))
							   {
								   day[0]=2;
								   day[1]=8;
								   LCD_GoToXY(3,1);
								   LCD_Print_Integer(day[0]);
								   LCD_GoToXY(4,1);
								   LCD_Print_Integer(day[1]);
								   LCD_GoToXY(i,1);
							   }
							 if(month[0]==0 && (month[1]==4 ||(month[0]==1 && month[1]==1) ||month[1]==4||month[1]==9) && (day[0]>2 && day[1]>0))
								   {
									   day[0]=3;
									   day[1]=0;
									   LCD_GoToXY(3,1);
									   LCD_Print_Integer(day[0]);
									   LCD_GoToXY(4,1);
									   LCD_Print_Integer(day[1]);
									   LCD_GoToXY(i,1);
								   }
					    		 if(month[0]==-1)
					    			 month[0]=1;

					    		 if(month[0]==0 && month[1]==0)
								   {
									 month[1]=1;
									 LCD_GoToXY(i+1,1);
									 LCD_Print_Integer(month[1]);
								   }
					    		 LCD_GoToXY(i,1);

					    		 if(month[1]>2 && month[0]==1)
								   {
									 month[1]=2;
									LCD_GoToXY(i+1,1);
									LCD_Print_Integer(month[1]);

								   }
					    		 LCD_GoToXY(i,1);
					    		 LCD_Print_Integer(month[0]);
					    		 LCD_GoToXY(i,1);

					    		 MONTH=(month[0]*10)+(month[1]);



					    		 break;
					    	 }
					     case 7:
					    	 {
					    		 month[1]-=1;
					    		 if(month[0]==0 && month[1]==2 && day[0]>2 && (YEAR%4==0))
							   {
								   day[0]=2;
								   day[1]=9;
								   LCD_GoToXY(3,1);
								   LCD_Print_Integer(day[0]);
								   LCD_GoToXY(4,1);
								   LCD_Print_Integer(day[1]);
								   LCD_GoToXY(i,1);
							   }

							 if(month[0]==0 && month[1]==2 && day[0]>2 && (YEAR%4!=0))
							   {
								   day[0]=2;
								   day[1]=8;
								   LCD_GoToXY(3,1);
								   LCD_Print_Integer(day[0]);
								   LCD_GoToXY(4,1);
								   LCD_Print_Integer(day[1]);
								   LCD_GoToXY(i,1);
							   }
							 if((month[0]==1 && month[1]==1) || (((month[0]==0) && ((month[1]==4) || (month[1]==4) || (month[1]==9))) && ((day[0]>2) && (day[1]>0))))
							   {
								   day[0]=3;
								   day[1]=0;
								   LCD_GoToXY(3,1);
								   LCD_Print_Integer(day[0]);
								   LCD_GoToXY(4,1);
								   LCD_Print_Integer(day[1]);
								   LCD_GoToXY(i,1);
							   }
					    		 if(month[1]==-1 && month[0]==1)
					    			 month[1]=2;

					    		 if(month[0]==0 && month[1]==0)
					    			 month[1]=9;

					    		 LCD_Print_Integer(month[1]);
					    		 LCD_GoToXY(i,1);
					    		 MONTH=(month[0]*10)+(month[1]);
					    		 break;
					    	 }
					     case 9:
					    	 {
					    		 year[0]-=1;

					    		 if(year[0]==-1)
					    			 year[0]=9;

					    		 LCD_Print_Integer(year[0]);
					    		 LCD_GoToXY(i,1);
					    		 YEAR=(year[0]*1000)+(year[1]*100)+(year[2]*10)+(year[3]);
					    		 break;
					    	 }
					     case 10:
					    	 {
					    		 year[1]-=1;

					    		 if(year[1]==-1)
					    			 year[1]=9;

					    		 LCD_Print_Integer(year[1]);
					    		 LCD_GoToXY(i,1);
					    		 YEAR=(year[0]*1000)+(year[1]*100)+(year[2]*10)+(year[3]);
					    		 break;
					    	 }
					     case 11:
					     {
					    	 year[2]-=1;

							 if(year[2]==-1)
								 year[2]=9;

							 LCD_Print_Integer(year[2]);
							 LCD_GoToXY(i,1);
							 YEAR=(year[0]*1000)+(year[1]*100)+(year[2]*10)+(year[3]);
					    	 break;
					     }
					     case 12:
					     {
					    	 year[3]-=1;

							 if(year[3]==-1)
								 year[3]=9;

							 LCD_Print_Integer(year[3]);
							 LCD_GoToXY(i,1);
							 YEAR=(year[0]*1000)+(year[1]*100)+(year[2]*10)+(year[3]);
					    	 break;
					     }

						 }
					 }

					  if(key=='-')
					  {
						  LCD_DISPLAY_CONTROL(1,1,0);
						  break;
					  }

				 }
			 }

			 if(key=='=')
				 break;

		 }

		 DAY=(day[0]*10) + (day[1]);
		 MONTH=(month[0]*10)+(month[1]);
		 YEAR=(year[0]*1000)+(year[1]*100)+(year[2]*10)+(year[3]);

		LCD_CLEAR();
		LCD_GoToXY(0,0);
		LCD_Print_Char(0);
		LCD_Print_Char(1);
		LCD_Print_Char(2);

		LCD_GoToXY(0,1);
		LCD_Print_Char(3);
		LCD_Print_Char(4);
		LCD_Print_Char(5);

}
void SetAlarm(void)
{
	u8 i=3;

	s8 hours_alarm[2]={HOURS_ALARM/10,HOURS_ALARM%10};
	s8 minutes_alarm[2]={MINUTES_ALARM/10,MINUTES_ALARM%10};
	s8 seconds_alarm[2]={SECONDS_ALARM/10,SECONDS_ALARM%10};





		 LCD_CLEAR();
		 LCD_DISPLAY_CONTROL(1,1,0);
		 LCD_GoToXY(0,0);
		 LCD_Print_String("    SET ALARM  ");
		 LCD_GoToXY(0,1);
		 LCD_Print_String("   ");
		 LCD_Print_Integer(hours_alarm[0]);
		 LCD_Print_Integer(hours_alarm[1]);
		 LCD_Print_Char(':');
		 LCD_Print_Integer(minutes_alarm[0]);
		 LCD_Print_Integer(minutes_alarm[1]);
		 LCD_Print_Char(':');
		 LCD_Print_Integer(seconds_alarm[0]);
		 LCD_Print_Integer(seconds_alarm[1]);
		 LCD_Print_Char(' ');

		 if(meridiem_alarm==0)
		 LCD_Print_Char('A');

		 if(meridiem_alarm==1)
		 LCD_Print_Char('P');

		 LCD_Print_Char('M');

		 while(1)
				 {

					 LCD_GoToXY(i,1);
					 key=KPD_GET_KEY_PRESSED();

					 if(key=='6')
					 {
						 i++;

						 if(i==5 || i==8 || i==11)
							 i++;

						 if(i>12)
							 i=3;

						 LCD_GoToXY(i,1);
					 }

					 if(key=='4')
					 {
					 	 i--;

					 	 if(i==5 || i==8 || i==11)
					 		 i--;

					 	 if(i<3)
					 		i=12;

					 	 LCD_GoToXY(i,1);
					 }

					 if(key=='-')
					 {
						 LCD_DISPLAY_CONTROL(1,0,1);

						 while(1)
						 {
							 key=KPD_GET_KEY_PRESSED();
							 if(key=='2')
							 {
							  switch(i)
							 	 {
							  	   case 3:
							  		   {
							  			  hours_alarm[0]+=1;

							  			  if(hours_alarm[0]>1)
							  				  hours_alarm[0]=0;

							  			if(hours_alarm[1]==0 && hours_alarm[0]==0)
										 {
											 hours_alarm[1]=1;
											 LCD_GoToXY(i+1,1);
											 LCD_Print_Integer(hours_alarm[1]);
											 LCD_GoToXY(i,1);
										 }

							  			if(hours_alarm[0]==1 && hours_alarm[1]>2)
							  			{
											  hours_alarm[1]=2;
											  LCD_GoToXY(i+1,1);
											  LCD_Print_Integer(hours_alarm[1]);
											  LCD_GoToXY(i,1);
							  			}
							  			  LCD_Print_Integer(hours_alarm[0]);
							  			  LCD_GoToXY(i,1);
							  			  break;
							  		   }
							  	   case 4:
							  		   {
							  			   hours_alarm[1]+=1;

							  			 if(hours_alarm[1]>9 && hours_alarm[0]==0)
											  hours_alarm[1]=1;

							  			   if(hours_alarm[0]==1 && hours_alarm[1]>2)
							  				   hours_alarm[1]=0;

							  			   if(hours_alarm[1]==10)
							  				   hours_alarm[1]=0;

							  			   LCD_Print_Integer(hours_alarm[1]);
							  			   LCD_GoToXY(i,1);
							  			   break;
							  		   }
							  	   case 6:
							  		   {
							  			   minutes_alarm[0]+=1;

							  			   if(minutes_alarm[0] > 5)
							  				   minutes_alarm[0]=0;

							  			   LCD_Print_Integer(minutes_alarm[0]);
							  			   LCD_GoToXY(i,1);
							  			   break;
							  		   }
							  	   case 7:
							  		   {
							  			   minutes_alarm[1]+=1;

							  			 if(minutes_alarm[1] > 9)
										     minutes_alarm[1]=0;

							  			   LCD_Print_Integer(minutes_alarm[1]);
							  			   LCD_GoToXY(i,1);
							  			   break;
							  		   }
							  	   case 9:
							  		   {
							  			   seconds_alarm[0]+=1;

							  			   if(seconds_alarm[0]>5)
							  				   seconds_alarm[0]=0;

							  			   LCD_Print_Integer(seconds_alarm[0]);
							  			   LCD_GoToXY(i,1);
							  			   break;
							  		   }
							  	   case 10:
							  		   {
							  			   seconds_alarm[1]+=1;

							  			 if(seconds_alarm[1]>9)
											   seconds_alarm[1]=0;

							  			   LCD_Print_Integer(seconds_alarm[1]);
							  			   LCD_GoToXY(i,1);
							  			   break;
							  		   }
							  	   case 12:
							  	   {
							  		 meridiem_alarm^=1;

									 if(meridiem_alarm==0)
									 LCD_Print_Char('A');

									 if(meridiem_alarm==1)
										 LCD_Print_Char('P');

									 LCD_GoToXY(i,1);
									break;

							  	   }
							 	 }
							 }
							 else if(key=='8')
							 {
								 switch(i)
								 {
								 case 3:
									 {
										 hours_alarm[0]-=1;

										 if(hours_alarm[0]<0)
											 hours_alarm[0]=1;

										 if(hours_alarm[0]==0 && hours_alarm[1]==0)
										{
											  hours_alarm[1]=1;
											  LCD_GoToXY(i+1,1);
											  LCD_Print_Integer(hours_alarm[1]);
											  LCD_GoToXY(i,1);
										}
										 if(hours_alarm[0]==1 && hours_alarm[1]>2)
										{
											  hours_alarm[1]=2;
											  LCD_GoToXY(i+1,1);
											  LCD_Print_Integer(hours_alarm[1]);
											  LCD_GoToXY(i,1);
										}


										 LCD_Print_Integer(hours_alarm[0]);
										 LCD_GoToXY(i,1);
										 break;
									 }
							     case 4:
							    	 {
							    		 hours_alarm[1]-=1;



							    		 if(hours_alarm[1]==0 && hours_alarm[0]==0)
										   hours_alarm[1]=9;

							    		 if(hours_alarm[1]<0 && hours_alarm[0]==1)
										   hours_alarm[1]=2;

							    		 LCD_Print_Integer(hours_alarm[1]);
							    		 LCD_GoToXY(i,1);
							    		 break;
							    	 }
							     case 6:
							    	 {
							    		 minutes_alarm[0]-=1;

							    		 if(minutes_alarm[0]==-1)
							    			 minutes_alarm[0]=5;

							    		 LCD_Print_Integer(minutes_alarm[0]);
							    		 LCD_GoToXY(i,1);
							    		 break;
							    	 }
							     case 7:
							    	 {
							    		 minutes_alarm[1]-=1;

							    		 if(minutes_alarm[1]==-1)
							    			 minutes_alarm[1]=9;

							    		 LCD_Print_Integer(minutes_alarm[1]);
							    		 LCD_GoToXY(i,1);
							    		 break;
							    	 }
							     case 9:
							    	 {
							    		 seconds_alarm[0]-=1;

							    		 if(seconds_alarm[0]==-1)
							    			 seconds_alarm[0]=5;

							    		 LCD_Print_Integer(seconds_alarm[0]);
							    		 LCD_GoToXY(i,1);
							    		 break;
							    	 }
							     case 10:
							    	 {
							    		 seconds_alarm[1]-=1;

							    		 if(seconds_alarm[1]==-1)
							    			 seconds_alarm[1]=9;

							    		 LCD_Print_Integer(seconds_alarm[1]);
							    		 LCD_GoToXY(i,1);
							    		 break;
							    	 }
							     case 12:
								   {
									 meridiem_alarm^=1;

									 if(meridiem_alarm==0)
									 LCD_Print_Char('A');

									 if(meridiem_alarm==1)
										 LCD_Print_Char('P');

									 LCD_GoToXY(i,1);
									break;

								   }
								 }
							 }

							  if(key=='-')
							  {
								  LCD_DISPLAY_CONTROL(1,1,0);
								  break;
							  }

						 }
					 }

					 if(key=='=')
						 break;
				 }

				 HOURS_ALARM=(hours_alarm[0]*10) + (hours_alarm[1]);
				 MINUTES_ALARM=(minutes_alarm[0]*10)+(minutes_alarm[1]);
				 SECONDS_ALARM=(seconds_alarm[0]*10)+(seconds_alarm[1]);
				 ALARM=1;

				LCD_CLEAR();
				LCD_DISPLAY_CONTROL(1,0,0);
				LCD_Print_String("   ALARM SET!  ");

				while(while_counter!=2);
				while(while_counter!=1);
				while(while_counter!=0);

				LCD_CLEAR();
				LCD_GoToXY(0,0);
				LCD_Print_Char(0);
				LCD_Print_Char(1);
				LCD_Print_Char(2);

				LCD_GoToXY(0,1);
				LCD_Print_Char(3);
				LCD_Print_Char(4);
				LCD_Print_Char(5);


}

void CheckAlarm(void)
{


	if(HOURS==HOURS_ALARM && MINUTES==MINUTES_ALARM && SECONDS==SECONDS_ALARM && ALARM==1 && ((meridiem_alarm==0 && meridiem==0) || (meridiem_alarm==1 && meridiem==1)) )
	{


		DIO_SetPinValue(DIO_PORTA,DIO_PIN1,DIO_HIGH);



		LCD_CLEAR();
		LCD_DISPLAY_CONTROL(1,0,0);
		LCD_GoToXY(0,0);
		LCD_Print_String("     ALARM     ");
		LCD_GoToXY(3,1);

		if(HOURS_ALARM < 10)
		{
			LCD_Print_Char('0');
			LCD_Print_Integer(HOURS_ALARM);
		}
		else if(HOURS_ALARM > 9)
		{
			LCD_Print_Integer(HOURS_ALARM);
		}


		LCD_Print_Char(':');

		if(MINUTES_ALARM < 10)
		{
			LCD_Print_Char('0');
			LCD_Print_Integer(MINUTES_ALARM);
		}
		else if(MINUTES_ALARM > 9)
		{
			LCD_Print_Integer(MINUTES_ALARM);
		}
		LCD_Print_Char(':');

		if(SECONDS_ALARM < 10)
		{
			LCD_Print_Char('0');
			LCD_Print_Integer(SECONDS_ALARM);
		}
		else if(SECONDS_ALARM > 9)
		{
			LCD_Print_Integer(SECONDS_ALARM);
		}
		LCD_Print_Char(' ');

		if(meridiem_alarm==0)
		 LCD_Print_Char('A');

		 if(meridiem_alarm==1)
			 LCD_Print_Char('P');

		 LCD_Print_Char('M');



		do
		{
			if(key!=NOT_PRESSED)
								break;

			TOGG_BIT(PORTD,7);
			while(while_counter!=1)
			{
				key=KPD_GET_KEY_PRESSED();
				if(key!=NOT_PRESSED)
									break;
			}
			while(while_counter!=250)
			{
				key=KPD_GET_KEY_PRESSED();

				if(key!=NOT_PRESSED)
					break;
			}

			if(key!=NOT_PRESSED)
				break;

			/*
			if(ringtone==1)
			{
				TONE_iphone_tone();
			}
			else if(ringtone==2)
			{
				TONE_samsung_tone();
			}*/

		}while(key==NOT_PRESSED);

		DIO_SetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
		DIO_SetPinValue(DIO_PORTA,DIO_PIN1,DIO_LOW);

		ALARM=0;

		LCD_CLEAR();
		LCD_GoToXY(0,0);
		LCD_Print_Char(0);
		LCD_Print_Char(1);
		LCD_Print_Char(2);

		LCD_GoToXY(0,1);
		LCD_Print_Char(3);
		LCD_Print_Char(4);
		LCD_Print_Char(5);
	}
}

void TurnOnAlarm(void)
{
	ALARM=1;
	LCD_CLEAR();
	LCD_DISPLAY_CONTROL(1,0,0);
	LCD_GoToXY(0,0);
	LCD_Print_String("ALARM TURNED ON");

	while(while_counter!=2);
	while(while_counter!=1);
	while(while_counter!=0);

	LCD_CLEAR();
	LCD_GoToXY(0,0);
	LCD_Print_Char(0);
	LCD_Print_Char(1);
	LCD_Print_Char(2);

	LCD_GoToXY(0,1);
	LCD_Print_Char(3);
	LCD_Print_Char(4);
	LCD_Print_Char(5);

}

void TurnOffAlarm(void)
{
	ALARM=0;
	LCD_CLEAR();
	LCD_DISPLAY_CONTROL(1,0,0);
	LCD_GoToXY(0,0);
	LCD_Print_String("ALARM TURNED OFF");

	while(while_counter!=2);
	while(while_counter!=1);
	while(while_counter!=0);

	LCD_CLEAR();
	LCD_GoToXY(0,0);
	LCD_Print_Char(0);
	LCD_Print_Char(1);
	LCD_Print_Char(2);

	LCD_GoToXY(0,1);
	LCD_Print_Char(3);
	LCD_Print_Char(4);
	LCD_Print_Char(5);
}

void AlarmTone(void)
{
	LCD_CLEAR();
	LCD_DISPLAY_CONTROL(1,0,0);
	LCD_GoToXY(0,0);
	LCD_Print_String("   ALARM TONE  ");
	LCD_GoToXY(0,1);

	while(1)
	{
		LCD_GoToXY(0,1);
		key=KPD_GET_KEY_PRESSED();

		if(ringtone==1)
		{
			LCD_Print_String("iPhone Ringtone ");
		}
		else if(ringtone==2)
		{
			LCD_Print_String("Samsung Ringtone");
		}

		if(key=='6')
		{
			ringtone++;

			if(ringtone>2)
				ringtone=1;
		}

		if(key=='4')
		{
			ringtone--;

			if(ringtone<1)
				ringtone=2;
		}

		if(key=='=')
		{
			LCD_CLEAR();
			LCD_GoToXY(0,0);
			LCD_Print_String("ALARM TONE SET!");
			while(while_counter!=0);

			LCD_CLEAR();

			break;
		}

	}
}


