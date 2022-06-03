#include "TM4C123.h" /* include register definition file of TM4C123GH6PM */
#include "TimerH.h"
#include "MacrosH.h"
#include "tm4c123gh6pm.h"
#define LCD GPIOB   /* Define "LCD" as a symbolic name for GPIOB */
#define RS 0x01 /* PORTB BIT0 mask */
#define RW 0x02 /* PORTB BIT1 mask */
#define EN 0x04 /* PORTB BIT2 mask */


#define LCD_DATA       							(*((volatile unsigned long *)0x400053FC))
#define LCD_DIR                     (*((volatile unsigned long *)0x40005400))
#define LCD_DEN                     (*((volatile unsigned long *)0x4000551C))
#define SYSCTL_RCGCGPIO             (*((volatile unsigned long *)0x400FE608))
	
/*define useful symbolic names for LCD commands */
#define clear_display     0x01
#define returnHome        0x02
#define moveCursorRight   0x06
#define moveCursorLeft    0x08
#define shiftDisplayRight 0x1C
#define shiftDisplayLeft  0x18
#define cursorBlink       0x0F
#define cursorOff         0x0C
#define cursorOn          0x0E
#define Function_set_4bit 0x28
#define Function_set_8bit 0x38
#define Entry_mode        0x06
#define Function_8_bit    0x32
#define Set5x7FontSize    0x20
#define FirstRow          0x80


/* prototypes of LCD functions */
void LCD_init(void);  /* LCD initialization function */
void LCD_Cmd(unsigned char command); /*Used to send commands to LCD */
void LCD_Write_Char(unsigned char data); /* Writes ASCII character */
void LCD_Write_Nibble(unsigned char data, unsigned char control); /* Writes 4-bits */
void LCD_String (char *str);	/* Send string to LCD function */

/* LCD and GPIOB initialization Function */ 
void LCD_init(void)
{ 
 SYSCTL_RCGCGPIO |=(1<<1); /* Enable Clock to GPIOB */
 while(READ_BIT(SYSCTL_RCGCGPIO,1)==0){}
 GPIO_PORTB_LOCK_R =0x4C4F434B;
 GPIO_PORTB_PCTL_R &= ~0xFFFF0FFF;
 LCD_DIR |=0xF7; /* Set GPIOB all pins a digital output pins */
 LCD_DEN |=0xF7; /* Declare GPIOB pins as digital pins */

 LCD_Cmd(Function_set_4bit); /* Select 4-bit Mode of LCD */
 LCD_Cmd(moveCursorRight); /* shift cursor right */
 LCD_Cmd(clear_display); /* clear whatever is written on display */
 LCD_Cmd(cursorOff);  /* Enable Display and cursor off */
}

void LCD_Cmd(unsigned char command)
{
    LCD_Write_Nibble(command & 0xF0, 0);   /* Write upper nibble to LCD */
    LCD_Write_Nibble(command << 4, 0);     /* Write lower nibble to LCD */
    
    if (command < 4)
        TIMER_MS(2);         /* 2ms delay for commands 1 and 2 */
    else
        TIMER_uS(40);        /* 40us delay for other commands */
}


void LCD_Write_Nibble(unsigned char data, unsigned char control)
{

    data &= 0xF0;       /* Extract upper nibble for data */
    control &= 0x0F;    /* Extract lower nibble for control */
    LCD_DATA = data | control;       /* Set RS and R/W to zero for write operation */
    LCD_DATA = data | control | EN;  /* Provide Pulse to Enable pin to perform write operation */
    TIMER_uS(0);
    LCD_DATA = data | control; /*Send data */
    LCD_DATA = 0; /* stop writing data to LCD */
}
void LCD_Write_Char(unsigned char data)
{
    LCD_Write_Nibble(data & 0xF0, RS);    /* Write upper nibble to LCD and RS = 1 to write data */
    LCD_Write_Nibble(data << 4, RS);      /* Write lower nibble to LCD and RS = 1 to write data */
    TIMER_uS(40);
}


void LCD_Write_String (char *str)	/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!='\0';i++)  /* Send each char of string till the NULL */
	{
		LCD_Write_Char(str[i]);  /* Call LCD data write */
	}
}

void LCD_Write_Number(unsigned char data)
{
		unsigned char data_ascii = data + 48;
    LCD_Write_Nibble(data_ascii & 0xF0, RS);    /* Write upper nibble to LCD and RS = 1 to write data */
    LCD_Write_Nibble(data_ascii << 4, RS);      /* Write lower nibble to LCD and RS = 1 to write data */
    TIMER_uS(40);
}
