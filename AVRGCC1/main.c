/*
 * main.c
 *
 * Created: 21.01.2022 21:40:29
 *  Author: linxon
 */


#include "main.h"

static IR_DATA_t ir_d;

static RS485_CFG_t rs485_cfg;
static RS485_TX_t rs485_tx;

ISR(USART0_RXC_vect)  { rs485_ISR_reader();     };
ISR(USART0_UDRE_vect) { rs485_ISR_writer();     };
ISR(TIMER0_COMP_vect) { ir_ISR_timer_counter(); };
ISR(ANA_COMP_vect)    { ir_ISR_handler();       };

void main(void) {
	init_me();

	do {

		ir_NEC_decode(&ir_d.addr, &ir_d.command);

		if (ir_d.addr == IR_DU_TV_DEVICE_ADDR
				|| ir_d.addr == IR_REDMI_DEVICE_ADDR)
		{
			rs485_tx.data = ir_d.command;
			rs485_send_d(0, &rs485_tx);

			blink_led();
			ir_d.addr = ir_d.command = 0;
		}

	} while(1);
}

void init_me(void) {
	ir_d.cfg.frame_type = IR_CFG_FRAME_TYPE_NEC;
	ir_d.cfg.polarity   = IR_CFG_POLARITY_ACTIVE_LOW;
	ir_d.cfg.source_pin = PB2;
	ir_d.cfg.gpio_ptr   = &GPIO_B;

	ir_d.callback.pulse_mode          = &_ir_pulse_mode_by;
	ir_d.callback.setup_timer         = &_ir_setup_timer0;
	ir_d.callback.timer_intrr_enable  = &_ir_timer_intrr_enable;
	ir_d.callback.timer_intrr_disable = &_ir_timer_intrr_disable;

	ir_d.addr = ir_d.command = 0;

	ir_init(&ir_d);

	rs485_cfg.mode = RS485_CFG_MASTER_MODE;
	rs485_cfg.device_addr = 0x01;
	rs485_cfg.slave_addr[0] = 0x02;  // Slave устройство с релюшками, герконом и кнопкой

	rs485_init(&rs485_cfg);

	// пин LED индикатора
	GPIO_B.ddr |= _BV(PB1);
	LED_ON();

	sei();
}

void blink_led(void) {
	for (register uint8_t i = 0; i < 2; i++) {
		LED_OFF();
		my_delay_ms(30);
		LED_ON();
		my_delay_ms(30);
	}
}






