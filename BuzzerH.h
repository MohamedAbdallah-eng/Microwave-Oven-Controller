void BUZZER_vINIT(unsigned char portname,unsigned char pinumber); // this function initialize pin in a port as Buzzer
void BUZZER_vON(unsigned char portname,unsigned char pinumber);	// this function turns  the Buzzer on
void BUZZER_vOFF(unsigned char portname,unsigned char pinumber);// this function turn Buzzer off
void BUZZER_vTOG(unsigned char portname,unsigned char pinumber);//this function toggle the property of the Buzzer >> if it was on it will be off 
void BUZZER_vON_xSec(unsigned char portname,unsigned char pinumber,unsigned char seconds);	// this function turns  the Buzzer on for x seconds
