#include "usart.h"

#ifndef USART_DISABLE_STD
FILE usart_in = FDEV_SETUP_STREAM(NULL, rx_usart, _FDEV_SETUP_READ);
FILE usart_out = FDEV_SETUP_STREAM(tx_usart, NULL, _FDEV_SETUP_WRITE);
#endif

void usart_init(void) {
	uint16_t ubrr_scaled = USART_SCALED_UBRR;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		UBRR0H |= (ubrr_scaled >> 8);
		UBRR0L |= ubrr_scaled;
	}

#ifdef USART_USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~_BV(U2X0);
#endif

	UCSR0B |= _BV(RXEN0)  | _BV(TXEN0)  | _BV(RXCIE0);
	UCSR0C |= _BV(URSEL0) | _BV(UCSZ10) | _BV(UCSZ00);

#ifndef USART_DISABLE_STD
	stdin = &usart_in;
	stdout = &usart_out;

	printf_P(PSTR("\n\nReady!\n"));
#ifdef DEBUG_USART
	printf_P(PSTR("\nUSART conf:\n\tBaud: %lu\n\tUBRR: 0x%X\n\n"),
		USART_BAUDRATE, ubrr_scaled);
#endif
#endif /* USART_DISABLE_STD */
}

int rx_usart(FILE *stream) {
	(void) stream;

	loop_until_bit_is_set(UCSR0A, RXC0);
	return USART_DATA_REG;
}

int tx_usart(char data, FILE *stream) {
	if (data == '\n')
		tx_usart('\r', stream);

	loop_until_bit_is_set(UCSR0A, UDRE0);
	USART_DATA_REG = data;

	return SUCCESS;
}

void flush_usart(void) {
	loop_until_bit_is_set(UCSR0A, RXC0);
	asm volatile(
		"in __tmp_reg__, %[reg_addr]"	"\n\t"
		::[reg_addr] "I" (_SFR_IO_ADDR(USART_DATA_REG))
	);
}

