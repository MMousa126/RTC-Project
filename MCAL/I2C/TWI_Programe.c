/*
 * TWI_Programe.c
 *
 *  Created on: Mar 23, 2024
 *      Author: Amgad Mariy
 */

#include "../../StdTypes.h"
#include "../../Utils.h"
#include "TWI_Private.h"
#include "TWI_Interface.h"
#include "TWI_Config.h"

void M_TWI_voidInit(void)
{
	/*set prescaler to 1*/
	TWSR = 0;
	/*this is to make clock = 100khz*/
	TWBR = 32;
}

void Send_Start(void)
{
	CLR_BIT(TWCR,TWSTA);
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWEA);
	while((!READ_BIT(TWCR,TWINT)));
//	TWDR = SLAVE_ADDRESS<<1 | SLAVE_READ_WRITE;
//	TWCR = (1<<TWINT) | (1<<TWEN);
//    switch(SLAVE_READ_WRITE)
//    {
//    case SLAVE_WRITE:
//    	while((!READ_BIT(TWCR,TWINT)) && (TWSR != 0x18));
//    	break;
//    case SLAVE_READ:
//    	while((!READ_BIT(TWCR,TWINT)) && (TWSR != 0x40));
//    	break;
//    }

}

void sendByte(u8 copy_u8data)
{
	TWDR = copy_u8data;
	CLR_BIT(TWCR,TWSTA);
	TWCR = (1<<TWINT) | (1<<TWEN);
	while((!READ_BIT(TWCR,TWINT))/* && (TWSR != 0x28)*/);
}

void receiveByte_ACK(u8 * ptr)
{
	CLR_BIT(TWCR,TWSTA);
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
    while((!READ_BIT(TWCR,TWINT)) /*&& (TWSR != 0x50)*/);
    *ptr = TWDR;
}
void receiveByte_NoACK(u8 * ptr)
{
	CLR_BIT(TWCR,TWSTA);
	TWCR = (1<<TWINT) | (1<<TWEN);
	while((!READ_BIT(TWCR,TWINT)) /*&& (TWSR != 0x58)*/);
	*ptr = TWDR;

}
void Send_Stop(void)
{
//	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	CLR_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWSTO);
	SET_BIT(TWCR,TWINT);
//	while(!READ_BIT(TWCR,TWINT));
}
void getStatus(u8* Status )
{
	*Status = TWSR & 0xF8;
}
void sendrepeatedstart(void)
{

	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWEA);

	while(READ_BIT(TWCR,TWINT)==0);
}
u8 M_U8_I2C_ReadWithAck(){
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
    while(!(TWCR&(1<<TWINT)));
    return TWDR;
}
u8 M_U8_I2C_ReadWithNack(){
	TWCR =(1<<TWEN)|(1<<TWINT);
    while(!(TWCR&(1<<TWINT)));
    return TWDR;
}


u8 M_U8_I2C_Repeated_Start(){
	u8 transmit_status;
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while(!(TWCR& (1<<TWINT)));
	transmit_status = TWSR & 0xF8;
	if(transmit_status!= 0x10)
	transmit_status = 0x00;

	return transmit_status;
}

