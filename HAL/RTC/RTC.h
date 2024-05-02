/*
 * RTC.h
 *
 *  Created on: Mar 28, 2024
 *      Author: M.Moussa
 */

#ifndef HAL_RTC_RTC_H_
#define HAL_RTC_RTC_H_




#define         SECONDS_REGISTER_ADDRESS						0x00
#define         MINUTES_REGISTER_ADDRESS						0x01
#define         HOURS_REGISTER_ADDRESS							0x02
#define         DAY_REGISTER_ADDRESS							0x03
#define         DATE_REGISTER_ADDRESS							0x04
#define         MONTH_REGISTER_ADDRESS							0x05
#define         YEAR_REGISTER_ADDRESS							0x06
#define         SQW_REGISTER_ADDRESS							0x07

#define 		SETSLAVE_ADDRESS								0b11010000
#define 		GETSLAVE_ADDRESS								0b11010001



#define 	MASTER_WRITEBIT			0
#define 	MASTER_READBIT			1

#define 	WORD_ADDRESS			0x00

typedef enum {

	SATURDAY,
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY
}Day_t;

typedef enum{

	AM_12_FORMATE,
	PM_12_FORMATE,
	FORMATE_24

}HFormate_t;
typedef struct {
	u8 hour;
	u8 min;
	u8 sec;
	HFormate_t ampm;
} Time_t;

typedef struct {

	u16 year;
	u8 month;
	Day_t day;
	u8 day_val;
} Date_t;

void RTC_Init();

void RTC_SetTime(Time_t* time);

void RTC_GetTime(Time_t* time);

void RTC_SetDate(Date_t* date);

void RTC_GetDate(Date_t* date);

#endif /* HAL_RTC_RTC_H_ */
