#include "ButtonH.h"
#include "LEDH.h"
#include "DPIOH.h"
#include "TimerH.h"
#include "LCDH.h"
#include "KeyPadH.h"
#include "BuzzerH.h"
#include "Needed_FunctionsH.h"
#include "Option_FunctionsH.h"

int main (void)
{	
PORT_vInit('d');
PORT_vInit('f');
LCD_init();
KEYPAD_INIT('C','E');
while(1)
{		
		Microwave_States();
}
}

