/*
 * main.h
 *
 * Created: 21.01.2022 21:40:29
 *  Author: linxon
 */


#ifndef _MAIN_H_
#define _MAIN_H_ 1

#include "typedef.h"

// Модули
//#include "usart.h"
//#include "eeprom.h"
#include "ir_remote.h"
#include "rs485.h"

#define IR_DU_TV_DEVICE_ADDR			0x40
#define IR_REDMI_DEVICE_ADDR			0x08

#define LED_ON()		(GPIO_B.port |=  _BV(PB1))
#define LED_OFF()		(GPIO_B.port &= ~_BV(PB1))

void init_me(void);
void blink_led(void);

#endif /* _MAIN_H_ */
