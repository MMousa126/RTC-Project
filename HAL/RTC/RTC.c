/*
 * RTC.c
 *
 *  Created on: Mar 28, 2024
 *      Author: M.Moussa
 */

#include "../../StdTypes.h"
#include "../../Utils.h"
#include "RTC.h"
#include "../../MCAL/I2C/TWI_Interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

static u8 convertdectobcd(u8 var) {
	u8 c;
	c = var % 10;
	var /= 10;

	c = (var << 4) | c;

	return c;

}

static u8 convertbcdtodec(u8 var) {

	u8 temp = 0;

	temp = var & 0b11110000;

	var &= 0b00001111;

	temp = var + ((temp >> 4) * 10);

	return temp;
}
void RTC_Init() {

	/* direction pins as output */

	M_TWI_voidInit();
//	Send_Start();
//	sendByte(SETSLAVE_ADDRESS);
//	/* select second register */
////	sendByte(SECONDS_REGISTER_ADDRESS);
//	/* select ch */
//	sendByte(SECONDS_REGISTER_ADDRESS);
//	Send_Stop();
}

void RTC_SetTime(Time_t* time) {

	u8 second = convertdectobcd(time->sec);

	u8 minutes = convertdectobcd(time->min);

	u8 hour = 0;



	Send_Start();
	sendByte(SETSLAVE_ADDRESS);
	sendByte(SECONDS_REGISTER_ADDRESS);
	sendByte(second);
	sendByte(minutes);

	/* checking the hours format */
	if (time->ampm == FORMATE_24) {
		CLR_BIT(hour, 6);

		hour = convertdectobcd(time->hour);

	} else {

		SET_BIT(hour, 6);
		if (time->ampm == AM_12_FORMATE) {
			CLR_BIT(hour, 5);
		} else if (time->ampm == PM_12_FORMATE) {
			SET_BIT(hour, 5);
		}
		hour = convertdectobcd(time->hour);
	}


	sendByte(hour);
	Send_Stop();

}

void RTC_GetTime(Time_t* time) {

	u8 second = 0;
	u8 minute = 0;
	u8 hour = 0;

	Send_Start();
	sendByte(SETSLAVE_ADDRESS);
	sendByte(SECONDS_REGISTER_ADDRESS);

	M_U8_I2C_Repeated_Start();
	sendByte(GETSLAVE_ADDRESS);

	receiveByte_ACK(&second);
	time->sec = convertbcdtodec(second);
	receiveByte_ACK(&minute);
	time->min = convertbcdtodec(minute);
	receiveByte_NoACK(&hour);

	/* 12 AM / PM format */
	if (READ_BIT(hour,6) == 1) {
		/* 12 PM format */
		if (READ_BIT(hour , 5) == 1) {
			time->ampm = PM_12_FORMATE;
			time->hour = convertbcdtodec(hour);

		}
		/* 12 AM format */
		else {
			time->ampm = AM_12_FORMATE;
			time->hour = convertbcdtodec(hour);
		}

	}
	/* 24 format */
	else {


		time->hour = convertbcdtodec(hour);
		time->ampm = FORMATE_24;

	}

	Send_Stop();

}

void RTC_SetDate(Date_t* date) {

	Day_t day = date->day;
	u8 month = 0;
	u8 year = 0;
	u8 date2 = 0;

	date2 = convertdectobcd(date->day_val);

	month = convertdectobcd(date->month);

	year = convertdectobcd(date->year);

	Send_Start();
	sendByte(SETSLAVE_ADDRESS);
	sendByte(DAY_REGISTER_ADDRESS);
	sendByte(day);
	sendByte(date2);
	sendByte(month);
	sendByte(year);
	Send_Stop();

}

void RTC_GetDate(Date_t* date) {

	Day_t day = 0;
	u8 month = 0;
	u8 year = 0;
	u8 date2 = 0;
	Send_Start();
	sendByte(SETSLAVE_ADDRESS);
	sendByte(DAY_REGISTER_ADDRESS);

	M_U8_I2C_Repeated_Start();
	sendByte(GETSLAVE_ADDRESS);

	receiveByte_ACK(&day);
	date->day = day;

	receiveByte_ACK(&date2);
	date->day_val = convertbcdtodec(date2);

	receiveByte_ACK(&month);
	date->month = convertbcdtodec(month);

	receiveByte_NoACK(&year);
	date->year = convertbcdtodec(year);
	Send_Stop();

}
