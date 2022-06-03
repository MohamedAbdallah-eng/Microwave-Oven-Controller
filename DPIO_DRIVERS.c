#include "MacrosH.h"
#include "tm4c123gh6pm.h"
void PORT_vInit(unsigned char portname) //intialize single port by passing the port charachter name of port 
// CAUTION YOU WILL NEED THIS FUNCTION TO INTIALIZE THE PORTS BEFORE USING ANY OTHER FUNCTION
{
	switch(portname)
	{
		case 'A':
		case 'a':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,0);
			while(READ_BIT(SYSCTL_RCGCGPIO_R,0)==0){}
			GPIO_PORTA_LOCK_R =0x4C4F434B;
			GPIO_PORTA_CR_R |= 0xFF;
			GPIO_PORTA_DEN_R|=0xFF;
			break;
		}
		case 'B':
		case 'b':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,1);
			while(READ_BIT(SYSCTL_RCGCGPIO_R,1)==0){}
			GPIO_PORTB_LOCK_R =0x4C4F434B;
			GPIO_PORTB_CR_R |= 0xFF;
			GPIO_PORTB_DEN_R|=0xFF;
			break;
		}
		case 'C':
		case 'c':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,2);
			while(READ_BIT(SYSCTL_RCGCGPIO_R,2)==0){}
			GPIO_PORTC_LOCK_R =0x4C4F434B;
			GPIO_PORTC_PCTL_R &= ~0xFFFF0000;
			GPIO_PORTC_CR_R |= 0xF0;
			GPIO_PORTC_DEN_R |= 0xF0;
			break;
		}
		case 'D':
		case 'd':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,3);
			while(READ_BIT(SYSCTL_PRGPIO_R,3)==0){}
			GPIO_PORTD_LOCK_R =0x4C4F434B;
			GPIO_PORTD_CR_R |= 0x0E;
			GPIO_PORTD_DEN_R |= 0x0E;
			GPIO_PORTD_PCTL_R &= ~0x0000FFF0;
			GPIO_PORTD_DIR_R |= 0x08;   					// Buzzer output
			GPIO_PORTD_DIR_R &= ~0x06;  					// SW2 & SW3 inputs
			GPIO_PORTD_PUR_R |= 0x04;							// SW3 pull-up
			GPIO_PORTD_PUR_R &= ~0x02;						// SW2 pull-down
			break;
		}
		case 'E':
		case 'e':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,4);
			while(READ_BIT(SYSCTL_RCGCGPIO_R,4)==0){}
			GPIO_PORTE_LOCK_R =0x4C4F434B;
			GPIO_PORTE_PCTL_R &= ~0x000FFFF0;
			GPIO_PORTE_CR_R |= 0x1E;
			GPIO_PORTE_DEN_R |= 0x1E;
			break;
		}
		case 'F':
		case 'f':
		{
			SET_BIT(SYSCTL_RCGCGPIO_R,5);
			while(READ_BIT(SYSCTL_RCGCGPIO_R,5)==0){}
			GPIO_PORTF_LOCK_R =0x4C4F434B;
			GPIO_PORTF_CR_R |= 0x1F;
			GPIO_PORTF_DIR_R |= 0x0E;  						// LEDs ouput
			GPIO_PORTF_DIR_R &= ~0x11; 						// sw1 & sw2 input
			GPIO_PORTF_DEN_R|=0x1F;
			GPIO_PORTF_AMSEL_R &= ~0x1F;
			GPIO_PORTF_AFSEL_R &= ~0x1F;
			GPIO_PORTF_PCTL_R &= ~0x000FFFFF;
			GPIO_PORTF_PUR_R |=0x11;
			break;
		}
	}
}
void DIO_vSETPINDIR ( unsigned char portname,unsigned char pinumber,unsigned char direction) //choose the direction of a single pin in a single port by passing the port charachter and direction 1 for output 0 for input 
{
	switch(portname)
	{
		case 'A':
		case 'a':
		{ if(direction==1)
				{
					SET_BIT(GPIO_PORTA_DIR_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTA_DIR_R,pinumber);
				}
			break;
	}
		case 'B':
		case 'b':
		{ if(direction==1)
				{
					SET_BIT(GPIO_PORTB_DIR_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTB_DIR_R,pinumber);
				}
			break;
			}
		case 'C':
		case 'c':
		{ if(direction==1)
				{
					SET_BIT(GPIO_PORTC_DIR_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTC_DIR_R,pinumber);
				}
			break;
			}	
		case 'D':
		case 'd':
		{ if(direction==1)
				{
					SET_BIT(GPIO_PORTD_DIR_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTD_DIR_R,pinumber);
				}
			break;
			}	
		case 'E':
		case 'e':
		{ if(direction==1)
				{
					SET_BIT(GPIO_PORTE_DIR_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTE_DIR_R,pinumber);
				}
			break;
			}	
		case 'F':
		case 'f':
		{ if(direction==1)
				{
					SET_BIT(GPIO_PORTF_DIR_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTF_DIR_R,pinumber);
				}
			break;
			}	
	
}}
void DIO_vWRITEPIN(unsigned char portname,unsigned char pinumber,unsigned char Data)//write the data you want on a single pin in a single port
{
	switch(portname)
	{
		case 'A':
		case 'a':
		{ if(Data==1)
				{
					SET_BIT(GPIO_PORTA_DATA_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTA_DATA_R,pinumber);
				}
			break;
	}
		case 'B':
		case 'b':
		{ if(Data==1)
				{
					SET_BIT(GPIO_PORTB_DATA_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTB_DATA_R,pinumber);
				}
			break;
			}
		case 'C':
		case 'c':
		{ if(Data==1)
				{
					SET_BIT(GPIO_PORTC_DATA_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTC_DATA_R,pinumber);
				}
			break;
			}	
		case 'D':
		case 'd':
		{ if(Data==1)
				{
					SET_BIT(GPIO_PORTD_DATA_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTD_DATA_R,pinumber);
				}
			break;
			}	
		case 'E':
		case 'e':
		{ if(Data==1)
				{
					SET_BIT(GPIO_PORTE_DATA_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTE_DATA_R,pinumber);
				}
			break;
			}	
		case 'F':
		case 'f':
		{ if(Data==1)
				{
					SET_BIT(GPIO_PORTF_DATA_R,pinumber);
				}
				else
				{
					CLR_BIT(GPIO_PORTF_DATA_R,pinumber);
				}
			break;
			}
			}	
			}
void DIO_vTOGGLEPIN(unsigned char portname,unsigned char pinumber)//toggle a pin in a port
{
	switch(portname)
	{
		case 'A':
		case 'a':
		{ 
					TOG_BIT(GPIO_PORTA_DATA_R,pinumber);
	
			break;
	}
		case 'B':
		case 'b':
		{
				
					TOG_BIT(GPIO_PORTB_DATA_R,pinumber);
	
			break;
			}
		case 'C':
		case 'c':

				{
					TOG_BIT(GPIO_PORTC_DATA_R,pinumber);

			break;
			}	
		case 'D':
		case 'd':
		{ 
					TOG_BIT(GPIO_PORTD_DATA_R,pinumber);
			break;

				}

		case 'E':
		case 'e':
		{ 
					TOG_BIT(GPIO_PORTE_DATA_R,pinumber);
						break;

				}
	
		case 'F':
		case 'f':
		{ 
					TOG_BIT(GPIO_PORTF_DATA_R,pinumber);
						break;

				}
			}	
			}
void DIO_vSETPORTDIR(unsigned char portname,unsigned char direction)//set the whole direction 'all pins' of a port choose 1 for output 0 for input
{
	switch(portname)
	{
		case 'A':
		case 'a':
		{ 
					GPIO_PORTA_DIR_R=direction;

			break;
	}
		case 'B':
		case 'b':
		{ 					GPIO_PORTB_DIR_R=direction;

			break;
			}
		case 'C':
		case 'c':
		{ 
								GPIO_PORTC_DIR_R=direction;

			break;
			}	
		case 'D':
		case 'd':
		{					GPIO_PORTD_DIR_R=direction;

			break;
			}	
		case 'E':
		case 'e':
		{
								GPIO_PORTE_DIR_R=direction;

			break;
			}	
		case 'F':
		case 'f':
		{
								GPIO_PORTF_DIR_R=direction;

			break;
			}	
	
}}
void DIO_vWRITEPORT(unsigned char portname,unsigned data)//write 8 bits in a single port
{
	switch(portname)
	{
		case 'A':
		case 'a':
		{ 
					GPIO_PORTA_DATA_R=data;

			break;
	}
		case 'B':
		case 'b':
		{ 					GPIO_PORTB_DATA_R=data;

			break;
			}
		case 'C':
		case 'c':
		{ 
								GPIO_PORTC_DATA_R=data;

			break;
			}	
		case 'D':
		case 'd':
		{					GPIO_PORTD_DATA_R=data;

			break;
			}	
		case 'E':
		case 'e':
		{
								GPIO_PORTE_DATA_R=data;

			break;
			}	
		case 'F':
		case 'f':
		{
								GPIO_PORTF_DATA_R=data;

			break;
			}	
	
}}
unsigned char DIO_u8READPIN(unsigned char portname,unsigned char pinumber) //function reutrn the read bit from the selected port name and pin number 
{
		switch(portname)
	{
		case 'A':
		case 'a':
		{ 
					return READ_BIT(GPIO_PORTA_DATA_R,pinumber);
	}
		case 'B':
		case 'b':
		{ 
					return READ_BIT(GPIO_PORTB_DATA_R,pinumber);
	}
		case 'C':
		case 'c':
		{ 
					return READ_BIT(GPIO_PORTC_DATA_R,pinumber);
	}
		case 'D':
		case 'd':
		{ 
					return READ_BIT(GPIO_PORTD_DATA_R,pinumber);
	}
		case 'E':
		case 'e':
		{ 
					return READ_BIT(GPIO_PORTE_DATA_R,pinumber);
	}
		case 'F':
		case 'f':
		{ 
					return READ_BIT(GPIO_PORTF_DATA_R,pinumber);
	}
	}
}

unsigned char DIO_u8READPORT(unsigned char portname)//function return the read 8 bits of the port selected
{
		switch(portname)
	{
		case 'A':
		case 'a':
		{ 
					return GPIO_PORTA_DATA_R;
	}
		case 'B':
		case 'b':
		{ 
					return GPIO_PORTB_DATA_R;
	}
		case 'C':
		case 'c':
		{ 
					return GPIO_PORTC_DATA_R;
	}
		case 'D':
		case 'd':
		{ 
					return GPIO_PORTD_DATA_R;
	}
		case 'E':
		case 'e':
		{ 
					return GPIO_PORTE_DATA_R;
	}
		case 'F':
		case 'f':
		{ 
					return GPIO_PORTF_DATA_R;
	}
	}
}
void DIO_vEABLEPULLUP(unsigned char portname,unsigned char pinumber) //function enable 1 bit "1 pin" of a port to be pull up
{
		switch(portname)
	{
		case 'A':
		case 'a':
		{ 
					SET_BIT(GPIO_PORTA_PUR_R,pinumber);
	
			break;
	}
		case 'B':
		case 'b':
		{
				
					SET_BIT(GPIO_PORTB_PUR_R,pinumber);
	
			break;
			}
		case 'C':
		case 'c':

				{
					SET_BIT(GPIO_PORTC_PUR_R,pinumber);

			break;
			}	
		case 'D':
		case 'd':
		{ 
					TOG_BIT(GPIO_PORTD_PUR_R,pinumber);
			break;

				}

		case 'E':
		case 'e':
		{ 
					SET_BIT(GPIO_PORTE_PUR_R,pinumber);
						break;

				}
	
		case 'F':
		case 'f':
		{ 
					SET_BIT(GPIO_PORTF_PUR_R,pinumber);
						break;

				}
			}	
			}

void DIO_vWRITEHIGHPINS(unsigned char portname,unsigned data) //*send 4 bits*this function writes on the highest 4 pins of the port ( it takes argument of 2 hexadecimal)
{
	data<<=4;
	switch(portname)
	{
		case 'A':
		case 'a':
		{ 		GPIO_PORTA_DATA_R&=0x0F;
					GPIO_PORTA_DATA_R|=data;

			break;
	}
		case 'B':
		case 'b':
		{ 		GPIO_PORTB_DATA_R&=0x0F;
					GPIO_PORTB_DATA_R|=data;
			break;
			}
		case 'C':
		case 'c':
		{ 		GPIO_PORTC_DATA_R&=0x0F;
					GPIO_PORTC_DATA_R|=data;
			break;
			}	
		case 'D':
		case 'd':
		{ 		GPIO_PORTD_DATA_R&=0x0F;
					GPIO_PORTD_DATA_R|=data;
			break;
			}	
		case 'E':
		case 'e':
		{
			 		GPIO_PORTE_DATA_R&=0x0F;
					GPIO_PORTE_DATA_R|=data;
			break;
			}	
		case 'F':
		case 'f':
		{
			 		GPIO_PORTF_DATA_R&=0x0F;
					GPIO_PORTF_DATA_R|=data;
			break;
			}	
	
}}
void DIO_vWRITELOWPINS(unsigned char portname,unsigned data) // *send 4 bits*this function writes on the lowest 4 pins of the port (it takes argument of 2 hexadecimal)
{

	switch(portname)
	{
		case 'A':
		case 'a':
		{ 		GPIO_PORTA_DATA_R&=0xF0;
					GPIO_PORTA_DATA_R|=data;

			break;
	}
		case 'B':
		case 'b':
		{ 		GPIO_PORTB_DATA_R&=0xF0;
					GPIO_PORTB_DATA_R|=data;
			break;
			}
		case 'C':
		case 'c':
		{ 		GPIO_PORTC_DATA_R&=0xF0;
					GPIO_PORTC_DATA_R|=data;
			break;
			}	
		case 'D':
		case 'd':
		{ 		GPIO_PORTD_DATA_R&=0xF0;
					GPIO_PORTD_DATA_R|=data;
			break;
			}	
		case 'E':
		case 'e':
		{
			 		GPIO_PORTE_DATA_R&=~0x1E;
					GPIO_PORTE_DATA_R|=data;
			break;
			}	
		case 'F':
		case 'f':
		{
			 		GPIO_PORTF_DATA_R&=0xF0;
					GPIO_PORTF_DATA_R|=data;
			break;
			}	
	
}}	

