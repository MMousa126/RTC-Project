/*
 * TWI_Private.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Amgad Mariy
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define      TWDR               *((volatile u8*)0x23)
#define      TWAR               *((volatile u8*)0x22)
#define      TWSR               *((volatile u8*)0x21)
#define      TWBR               *((volatile u8*)0x20)
#define      TWCR               *((volatile u8*)0x56)


#define      TWEA              6
#define      TWEN              2
#define      TWSTO             4
#define      TWSTA             5
#define      TWINT             7

#endif /* TWI_PRIVATE_H_ */
