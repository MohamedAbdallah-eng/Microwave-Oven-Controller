#include "DPIOH.h"
#include "MacrosH.h"
#include "tm4c123gh6pm.h"
void BUTTON_vINIT(unsigned char portname,unsigned char pinumber)// this function intialize single pin in single port as a button CAUTION NOT a pull up button
{
		DIO_vSETPINDIR(portname,pinumber,0);
}
unsigned char BUTTON_u8READ(unsigned char portname,unsigned char pinumber)// this function reads the values of the button ' if it is pressed or not'
{
	return DIO_u8READPIN(portname,pinumber);
}
void BUTTON_vINIT_PULLUP(unsigned char portname,unsigned char pinumber)// use this function as defaullt to intialize the button .it intialize a single pin in a single port as a pull up button
{		
	  DIO_vEABLEPULLUP(portname,pinumber);
		DIO_vSETPINDIR(portname,pinumber,0);
}
