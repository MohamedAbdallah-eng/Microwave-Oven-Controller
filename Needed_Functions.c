#include "LCDH.h"
#include "TimerH.h"
#include "KeyPadH.h"
#include "Needed_FunctionsH.h"
#include "ButtonH.h"
#include "LEDH.h"
#include "BuzzerH.h"
#include "Option_FunctionsH.h"

void LCD_error_msg(void)					// Error msg occurs when the input weight from the is not equal to a number from 1 to 9
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x87);
	LCD_Write_String("Err");
	TIMER_SEC(2);
}

void LCD_error_msg2(void)				 // Error msg occurs when the user enters an invalid time
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x80);
	LCD_Write_String("Please enter");
	LCD_Cmd(0xC0);
	LCD_Write_String("a valid time");
	TIMER_SEC(2);
	Button_D_Pushed();
}

void LCD_error_msg3(void)				// Error msg occurs when the user enters an invalid char as a time
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x80);
	LCD_Write_String("Please enter");
	LCD_Cmd(0xC0);
	LCD_Write_String("a valid number");
	TIMER_SEC(2);
}

void LCD_error_msg4(void)				// Error msg occurs when the user choose anything rather than A,B,C or D
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x80);
	LCD_Write_String("Please enter");
	LCD_Cmd(0xC0);
	LCD_Write_String("a valid option");
	check_SW3('D',2);
}

unsigned char Valid_Input(unsigned char Input)  // Checks if the weight given is valid or not
{
		if ((48<Input) && (Input<58))
			return 1;
		else
			return 0;
}

unsigned char Valid_Input2(unsigned char Input)	// Checks if the time given is a number or not
{
		if((48<=Input) && (Input<58))
		{
			return 1;
		}
			else
			{
				return 0;
			}
}

void Display_Start(void)													
{
		LCD_Cmd(0x01);
		LCD_Cmd(0x80);
	  LCD_Write_String("Please choose");
	  LCD_Cmd(0xC0);
	  LCD_Write_String("A,B,C or D");
}

void Valid_time(unsigned char minutes,unsigned char seconds) // Checks if the time given is valid or not
{
	if(minutes>30 || ((minutes == 0) && (seconds == 0)))
	{
		LCD_error_msg2();
	}
	else if(minutes==30)
	{
		if(seconds>0)
		{
			LCD_error_msg2();
		}
		else
		{}
	}
	else
	{}
}

void Flash_LEDs_Buzzer(unsigned char Number_Flashes)				// Blinks LEDs and Buzzer
{
	unsigned char i;
	for (i = Number_Flashes;i>0;i--)
	{
		LED_vON('F',1); 
	  LED_vON('F',2);
	  LED_vON('F',3);
		BUZZER_vON('D',3);
	  TIMER_MS(500);
		LED_vOFF('F',1);
		LED_vOFF('F',2);
		LED_vOFF('F',3);
		BUZZER_vOFF('D',3);
		TIMER_MS(500);
	}
}
void LCD_Write_Weight(unsigned char weight)  // Writes the given weight on the LCD screen
{
	LCD_Write_String("Weight = ");
	LCD_Write_Char(weight);
	LCD_Write_String(" Kg");
	TIMER_SEC(2);
}

unsigned char Time_to_Sec(unsigned char minutes_big,unsigned char minutes_small,unsigned char seconds_big,unsigned char seconds_small)
{
	unsigned char time_sec;
	unsigned char minutes=(minutes_big-48)*10+(minutes_small-48);
	unsigned char seconds=(seconds_big-48)*10+(seconds_small-48);
	Valid_time(minutes,seconds);
	time_sec = 60*minutes+seconds;
	return time_sec;
	//if choose (D) enter Total time in seconds in function Start Cooking
}

void Cooking( unsigned char minutes, unsigned char seconds )
{
	check_SW3('D',2);
	TIMER_MS(200);
	LCD_Cmd(0x01);
	LCD_Cmd(0x80);
	LCD_Write_String("Cooking...");
	Count_Down(minutes,seconds);
	
}

unsigned char check_SWITCHES (unsigned char portname,unsigned char pinumber)
{ 
	unsigned char x;
  x = BUTTON_u8READ(portname,pinumber);    // read the value of SW1
  if(x == 1)
  {
   return 0;
  }
  else
   return 1;
}

void check_SW3(unsigned char portname,unsigned char pinumber)
{	
	if(BUTTON_u8READ('D',2)==0)
	{
	LCD_Cmd(0x01);
	LCD_Cmd(0x80);
	LCD_Write_String("Close the Door!");
	while ( BUTTON_u8READ('D',2) == 0)
		{}
	}
}

unsigned char Display_LCD_D(unsigned char seconds_small, unsigned char seconds_big, unsigned char minutes_small, unsigned char minutes_big)
	// Prints the time given by the user on the LCD
{
	unsigned char K;
	K = Valid_Input2(seconds_small);
	if (K == 0)
	{
		LCD_error_msg3();
		return 1;
	}
	LCD_Cmd(0xC5);
	LCD_Write_Char(minutes_big);
	LCD_Write_Char(minutes_small);
	LCD_Write_String(":");
	LCD_Write_Char(seconds_big);
	LCD_Write_Char(seconds_small);
	return 0;
}

void pause_display( unsigned char minutes, unsigned char seconds ) // pauses cooking if SW1 is pressed once
{  
   LCD_Cmd(0x01);
   LCD_Cmd(0x80);
   LCD_Write_String("Paused!");
   LCD_Cmd(0xC5);
   LCD_Write_String("left");
   LCD_WRITE_MINUTES_SECONDS(minutes,seconds);
	 TIMER_MS(500);
	 while((BUTTON_u8READ('D',1)==0) && (check_SWITCHES('F',4)==0)) {}
	 if(check_SWITCHES('F',4)==1)  /*checks sw1*/
		{
			Stopcooking_dispaly();
		}
		if(BUTTON_u8READ('D',1) == 1) /*checks sw2*/
		{
			TIMER_MS(200);
			Continue_cooking(minutes,seconds);
		}
}

void Stopcooking_dispaly ()											// Stops the cooking operation if SW1 is pressed twice
{
   LCD_Cmd(0x01);
   LCD_Cmd(0x80);
   LCD_Write_String("Cooking");
   LCD_Cmd(0xc0);
   LCD_Write_String("stopped!");
	 TIMER_SEC(3);
	 Microwave_States();
}

void Finish_Cooking(void)												// Indicates that the cooking operation has finished
{
	LCD_Cmd(0x01);
	LCD_Cmd(0x80);
	LCD_Write_String("Cooking");
	LCD_Cmd(0xC0);
	LCD_Write_String("Done");
	Flash_LEDs_Buzzer(3);
}

void Continue_cooking( unsigned char minutes, unsigned char seconds )			// Continue cooking from the time it was paused at
{ 
     LCD_Cmd(0x01);
     LCD_Cmd(0x80);
     LCD_Write_String("Cooking...");
     Count_Down(minutes,seconds);
     Finish_Cooking();
		 Microwave_States();
}

void Count_Down(unsigned char minutes, unsigned char seconds)					// Counts down the remaining cooking time
{
unsigned char i,temp,j ;
	for (i=minutes;i>=0;i--)
	{
				if(i !=minutes)
				{
					temp=59;
				}
				else
				{		
				temp=seconds;
				}

					for(j=temp;j>=0;j--)
					{
						LCD_WRITE_MINUTES_SECONDS(i,j);										// writes minutes and seconds on the LCD
						TIMER_SEC2(1);																		// delay 1 sec and checks on SW1 & SW3
						if(BUTTON_u8READ('D',2)==0)
						{
						check_SW3('D',2);
						Continue_cooking(i,j);
						}
						if(check_SWITCHES('F',4) == 1)
						{
						pause_display(i,j);
						}
						if(j==0)
						{
							break;
						}
						
					}
					if(i==0)
						{
							break;
						}
	}
}

void LCD_WRITE_MINUTES_SECONDS(unsigned char minutes,unsigned char seconds) 		// Prints minutes and seconds on the LCD
{
		unsigned char minutes_big,minutes_small,seconds_big,seconds_small;

		minutes_big=(minutes/10);															// minutes_big equals the most significant bit of the minuts
		minutes_small=(minutes%10);													 // minutes_small equals the least significant bit of the minuts
		seconds_big=(seconds/10);														// seconds_big equals the most significant bit of the seconds
		seconds_small=(seconds%10);												 // seconds_small equals the least significant bit of the seconds
		LCD_Cmd(0xC5);
		LCD_Write_Number(minutes_big);
		LCD_Write_Number(minutes_small);
	  LCD_Write_String(":");
		LCD_Write_Number(seconds_big);
		LCD_Write_Number(seconds_small);
}
