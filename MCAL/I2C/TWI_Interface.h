/*
 * TWI_Interface.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Amgad Mariy
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_


void M_TWI_voidInit(void);
void Send_Start(void);
void sendByte(u8 copy_u8data);
void receiveByte_ACK(u8 * ptr);
void receiveByte_NoACK(u8 * ptr);
void Send_Stop(void);
void getStatus(u8* Status );
void sendrepeatedstart(void);
u8 M_U8_I2C_ReadWithAck();
u8 M_U8_I2C_ReadWithNack();
u8 M_U8_I2C_Repeated_Start();
#endif /* TWI_INTERFACE_H_ */
