#include "ButtonH.h"
#include "LEDH.h"
#include "DPIOH.h"
#include "TimerH.h"
#include "MacrosH.h"
#include "tm4c123gh6pm.h"
void KEYPAD_INIT(unsigned char IN_portname,unsigned char OUT_portname)//Intialize 2 ports to be used for keypad , firt 4 pins in OUT_portname is intialized to be output
{		//Intialize 2 ports to be used for keypad , highest 4 pins in IN_portname is intialized to be input pull up bottons	
	PORT_vInit('C');
	PORT_vInit('E');
	DIO_vSETPINDIR (OUT_portname,1,1);
	DIO_vSETPINDIR (OUT_portname,2,1);
	DIO_vSETPINDIR (OUT_portname,3,1);
	DIO_vSETPINDIR (OUT_portname,4,1);
	DIO_vSETPINDIR (IN_portname,4,0);
	DIO_vSETPINDIR (IN_portname,5,0);
	DIO_vSETPINDIR (IN_portname,6,0);
	DIO_vSETPINDIR (IN_portname,7,0);
	DIO_vEABLEPULLUP(IN_portname,4);
	DIO_vEABLEPULLUP(IN_portname,5);
	DIO_vEABLEPULLUP(IN_portname,6);
	DIO_vEABLEPULLUP(IN_portname,7);
}
unsigned char KEYPAD_u8READ(unsigned char IN_portname,unsigned char OUT_portname)
	// this function reads what is pressed on keypad *send to this function port names that the keypad is connected to it*
{
	unsigned char row,coloumn,temp;
	unsigned char returnValue=0xFF;
	unsigned char array[4][4]={{'D','C','B','A'},
															{'#','9','6','3'},
															{'0','8','5','2'},
															{'*','7','4','1'}};
														do
														{
															for(row=0;row<4;row++)
															{
																DIO_vWRITELOWPINS(OUT_portname,0x1E);
																DIO_vWRITEPIN(OUT_portname,row+1,0);
																for(coloumn=0;coloumn<4;coloumn++)
																{
																	temp=DIO_u8READPIN(IN_portname,coloumn+4);
																	if(temp==0)
																	{
																		returnValue=array[row][coloumn];
																		break;
																	}	
																}
																	if(temp==0)
																	{
																		break;
																	}	
																	
															}
															 
														}	
														while(returnValue==0xFF);
														return returnValue;
													}

unsigned char KEYPAD_u8READ2(unsigned char IN_portname,unsigned char OUT_portname)
								// this function reads what is pressed on keypad *send to this function port names that the keypad is connected to it*
																			// it return the charachter pressed and it returns 0xFF if no key is pressed
{
	unsigned char row,coloumn,temp;
	unsigned char returnValue=0xFF;
	unsigned char array[4][4]={{'D','C','B','A'},
															{'#','9','6','3'},
															{'0','8','5','2'},
															{'*','7','4','1'}};
	
															for(row=0;row<4;row++)
															{
																DIO_vWRITELOWPINS(OUT_portname,0x1E);
																DIO_vWRITEPIN(OUT_portname,row+1,0);
																for(coloumn=0;coloumn<4;coloumn++)
																{
																	temp=DIO_u8READPIN(IN_portname,coloumn+4);
																	if(temp==0)
																	{
																		returnValue=array[row][coloumn];
																		break;
																	}	
																}
																	if(temp==0)
																	{
																		break;
																	}	
																}
															return returnValue; 
	}
