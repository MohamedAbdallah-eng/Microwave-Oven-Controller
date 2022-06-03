#include "LCDH.h"
#include "TimerH.h"
#include "KeyPadH.h"
#include "Needed_FunctionsH.h"
#include "ButtonH.h"
#include "Option_FunctionsH.h"

void Button_A_Pushed(void)
{
  LCD_Cmd( 0x01 ); 									 // clears LCD display
  LCD_Cmd( 0x84 );  								// Takes cursor to beginning of first row 
	LCD_Write_String ("Popcorn");			// display popcorn on the screen
	TIMER_SEC(2);  										// delay for 2 seconds
}

unsigned long Button_B_Pushed (void)
{
	unsigned char Kilos;
	unsigned char Check_Result;
	unsigned long Defrosted_Time;
	Check:
	LCD_Cmd(0x01);												// Clears the LCD display
	LCD_Cmd(0x82);												// Takes cursor to beginning of first row
	LCD_Write_String("Beef Weight?");
	TIMER_SEC(1);
	Kilos = KEYPAD_u8READ( 'C','E'); 			// gets the weight from the keypad
	Check_Result = Valid_Input(Kilos);		// checks if the input weight is a valid number
	if (Check_Result == 1)
	{
		LCD_Cmd(0x01);
		LCD_Write_Weight(Kilos);						// prints the input weight on the LCD
		Defrosted_Time = (Kilos-48) * 0.5 * 60;
		return Defrosted_Time;
	}
	else
	{
		LCD_error_msg();
		goto Check;
	}
}
		
unsigned char Button_C_Pushed (void)
{
	unsigned char Kilos;
	unsigned char Check_Result;
	unsigned char Defrosted_Time;
	Check:
	LCD_Cmd(0x01);												// Clears the LCD display
	LCD_Cmd(0x80);												// Takes cursor to beginning of first row
	LCD_Write_String("Chicken Weight?");
	TIMER_SEC(1);            
	Kilos = KEYPAD_u8READ( 'C','E'); 			// gets the weight from the keypad
	Check_Result = Valid_Input(Kilos);		// checks if the input weight is a valid number
	if (Check_Result == 1)
	{
		LCD_Cmd(0x01);
		LCD_Write_Weight(Kilos);						// prints the input weight on the LCD
		Defrosted_Time = (Kilos-48) * 0.2 * 60;
		return Defrosted_Time;
	}
	else
	{
		LCD_error_msg();
		goto Check;
	}
}
		
unsigned char Button_D_Pushed()
{
	loop:
	LCD_Cmd(0x01);
	LCD_Cmd(0x81);
  LCD_Write_String("Cooking time?") ;
  unsigned char seconds_small=48;
	unsigned char seconds_big=48; 
	unsigned char minutes_small=48;
	unsigned char minutes_big =48 ;
  unsigned char i;
	unsigned char K;
	LCD_Cmd(0xC5);
	LCD_Write_String("00:00");
  for(i=0;i<4;i++)
	{
	 minutes_big=minutes_small;
   minutes_small=seconds_big;
   seconds_big=seconds_small;
   seconds_small=KEYPAD_u8READ('C','E');
	 K = Display_LCD_D(seconds_small,seconds_big,minutes_small,minutes_big);
	 if(K == 1)
	 {
		 goto loop;																		// starts from the beginning if the user entered an invalid char as a number like '*'
	 }
	 TIMER_SEC(1);
   while(KEYPAD_u8READ2('C','E') ==0xFF)					// while no Key is entered at the keypad check switches
   {
    if(check_SWITCHES('F',4)==1)									// Checks SW1
		{
	   LCD_Cmd(0x01);
		 goto loop;
		}
    if(BUTTON_u8READ('D',1)==1)										// Checks SW3
    {
     TIMER_MS(200);
		 unsigned char Total_Time=Time_to_Sec(minutes_big,minutes_small,seconds_big,seconds_small);
		 unsigned char minutes = Total_Time/60;
		 unsigned char seconds = Total_Time%60;
	   Cooking(minutes,seconds);
		 Finish_Cooking();
		 Microwave_States();
    }
	 }
  }
	unsigned char Total_Time;
	Total_Time=Time_to_Sec(minutes_big,minutes_small,seconds_big,seconds_small);
	return(Total_Time);
}
		
void Microwave_States(void)
{
		unsigned char Keypad_Input;
		start:
		Display_Start();
		Keypad_Input=KEYPAD_u8READ('C','E');
		switch (Keypad_Input)
		{
			case 'A':
			{
			  Button_A_Pushed();
			  while(BUTTON_u8READ('D',1)==0) {} // wait until SW2 is pressed to start cooking
				TIMER_MS(200);
			  Cooking(1,0);
			  break;
			}
		  case 'B':
			{
				unsigned long Defrosted_Time;
				unsigned char minutes;
				unsigned char seconds;
				Defrosted_Time=Button_B_Pushed();
				minutes = Defrosted_Time/60;
				seconds = Defrosted_Time%60;
				while(BUTTON_u8READ('D',1)==0) {} // wait until SW2 is pressed to start cooking
				TIMER_MS(200);
				Cooking(minutes,seconds);
				break;
			}
			case 'C':
			{
				unsigned char Defrosted_Time;
				unsigned char minutes;
				unsigned char seconds;
				Defrosted_Time=Button_C_Pushed();
				minutes = Defrosted_Time/60;
				seconds = Defrosted_Time%60;
				while(BUTTON_u8READ('D',1)==0) {}  // wait until SW2 is pressed to start cooking
				TIMER_MS(200);
				Cooking(minutes,seconds);
				break;
			}
			case 'D':
			{
				unsigned char Total_Time;
				unsigned char minutes;
				unsigned char seconds;
				TIMER_MS(500);
				Total_Time=Button_D_Pushed();
				minutes = Total_Time/60;
				seconds = Total_Time%60;
				while(BUTTON_u8READ('D',1)==0) {}  // wait until SW2 is pressed to start cooking
				TIMER_MS(200);
				Cooking(minutes,seconds);
				break;
			}
			default:
			{
				LCD_error_msg4();
				TIMER_SEC(2);
				goto start;
			}
   }
		Finish_Cooking();
		goto start;
}
