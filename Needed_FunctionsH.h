void LCD_error_msg(void);
void LCD_error_msg2(void);
void LCD_error_msg3(void);
void LCD_error_msg4(void);
unsigned char Valid_Input(unsigned char Input);
unsigned char Valid_Input2(unsigned char Input);
void Display_Start(void);
void Valid_time(unsigned char minutes,unsigned char seconds);
void Flash_LEDs_Buzzer(unsigned char Number_Flashes);
void LCD_Write_Weight(unsigned char weight);
unsigned char Time_to_Sec(unsigned char minutes_big,unsigned char minutes_small,unsigned char seconds_big,unsigned char seconds_small);
void Cooking(unsigned char minutes, unsigned char seconds);
unsigned char check_SWITCHES (unsigned char portname,unsigned char pinumber);
void check_SW3(unsigned char portname,unsigned char pinumber);
unsigned char Display_LCD_D(unsigned char seconds_small, unsigned char seconds_big, unsigned char minutes_small, unsigned char minutes_big);
void pause_display(unsigned char minutes, unsigned char seconds) ;
void Stopcooking_dispaly (void);
void Finish_Cooking(void);
void Continue_cooking(unsigned char minutes, unsigned char seconds);
void LCD_WRITE_MINUTES_SECONDS(unsigned char minutes,unsigned char seconds);
void Count_Down(unsigned char minutes, unsigned char seconds);
