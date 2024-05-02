#include "StdTypes.h"
#include "Utils.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "HAL/RTC/RTC.h"
#include "HAL/LCD/LCD_Interface.h"
#include "avr/interrupt.h"
#include <util/delay.h>
#include "MCAL/I2C/TWI_Interface.h"

Date_t stdate = {
		24,12,FRIDAY,5
};

Time_t sttime = {
		22,12,25,FORMATE_24
};

int main() {

	//UART_Init();




	RTC_Init();
	RTC_SetTime(&sttime);
	RTC_SetDate(&stdate);

	RTC_GetTime(&sttime);
	RTC_GetDate(&stdate);




//	DIO_Init();
//	LCD_INIT();



//	M_TWI_voidInit();
//	Send_Start();
//
//	sendByte(100);
//
//	sendByte(0x55);
//
//	Send_Stop();
//
//	Send_Start();
//
//	sendByte(24);
//
//	sendByte(0x55);
//
//	Send_Stop();
//
//	Send_Start();
//
//	sendByte(44);
//
//	sendByte(0x55);
//
//	Send_Stop();

	while (1) {
//
//		LCD_WRITENUMBER((sttime.hour));
//		LCD_CLEAR();


	}
	return 0;
}

