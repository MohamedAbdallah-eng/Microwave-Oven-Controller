#include "DPIOH.h"
#include "MacrosH.h"
#include "tm4c123gh6pm.h"
#include "TimerH.h"
void BUZZER_vINIT(unsigned char portname,unsigned char pinumber) // this function initialize pin in a port as Buzzer 
{
	DIO_vSETPINDIR(portname,pinumber,1);
}
void BUZZER_vON(unsigned char portname,unsigned char pinumber)	// this function turns  the Buzzer on
{
	DIO_vWRITEPIN(portname,pinumber,1);
}	
void BUZZER_vOFF(unsigned char portname,unsigned char pinumber)// this function turn Buzzer off
{
	DIO_vWRITEPIN(portname,pinumber,0);
}
void BUZZER_vTOG(unsigned char portname,unsigned char pinumber)//this function toggle the property of the Buzzer >> if it was on it will be off 
{
	DIO_vTOGGLEPIN(portname,pinumber);
}
void BUZZER_vON_xSec(unsigned char portname,unsigned char pinumber,unsigned char seconds)	// this function turns  the Buzzer on for x seconds
{
	DIO_vWRITEPIN(portname,pinumber,1);
	TIMER_SEC(seconds);
	DIO_vWRITEPIN(portname,pinumber,0);

}	
