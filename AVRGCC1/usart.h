#ifndef _USART_H_
#define _USART_H_ 				1

//#define BAUD					38400
//#include <util/setbaud.h>
#include "typedef.h"

#define USART_BAUDRATE				9600UL
#define USART_SCALED_UBRR			(F_CPU / (USART_BAUDRATE * 16UL) -1)

#define USART_DATA_REG				UDR0	// используется в другим модулях, поэтому дадим этому регистру абстрактное имя

#define USART_CLEAR_RXC_FLAG()		(UCSR0A |= _BV(RXC0))
#define USART_CLEAR_TXC_FLAG()		(UCSR0A |= _BV(TXC0))

#define USART_IS_RX_COMPLETE()		(UCSR0A & _BV(RXC0))
#define USART_IS_TX_COMPLETE()		(UCSR0A & _BV(TXC0))
#define USART_IS_DATA_EMPTY()		(UCSR0A & _BV(UDRE0))
#define USART_RXC_INTRR_ENABLE()	(UCSR0B |=  _BV(RXCIE0))
#define USART_RXC_INTRR_DISABLE()	(UCSR0B &= ~_BV(RXCIE0))
#define USART_TXC_INTRR_ENABLE()	(UCSR0B |=  _BV(TXCIE0))
#define USART_TXC_INTRR_DISABLE()	(UCSR0B &= ~_BV(TXCIE0))
#define USART_UDRE_INTRR_ENABLE()	(UCSR0B |=  _BV(UDRIE0))
#define USART_UDRE_INTRR_DISABLE()	(UCSR0B &= ~_BV(UDRIE0))

#ifndef USART_DISABLE_STD
extern FILE usart_in;
extern FILE usart_out;
#endif

extern void usart_init(void);
extern int rx_usart(FILE *stream);
extern int tx_usart(char data, FILE *stream);
extern void flush_usart(void);

#endif /* _USART_H_ */
