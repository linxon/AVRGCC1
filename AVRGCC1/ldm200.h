/*
 * ldm200.h
 *
 * Created: 09.03.2022 20:39:16
 *  Author: linxon
 */


#ifndef LDM200_H_
#define LDM200_H_

#include "typedef.h"
#include "functions.h"

// LDM206 + LDM206 = 12
#define LDM200_MAX_LED_SUPPORT	6 // LDM205 = 5; LDM206 = 6; LDM208 = 8; ...

#define LDM200_LOAD_PIN			PD5
#define LDM200_D_IN_PIN			PD6
#define LDM200_CLK_PIN			PD7
#define LDM200_GPIO				GPIO_D

typedef struct ldm200_digital_led {
	const char sign;
	const byte led_mask;
} LDM200_DIGITAL_LED_t[];

void ldm200_pulse_clk(void);
void ldm200_pulse_load(void);
byte ldm200_get_mask(char sign);

extern void ldm200_init(void);

//extern char ldm200_get_sign(uint8_t pos);
extern void ldm200_set_sign(char sign, uint8_t pos, bool doten);
extern void ldm200_set_str(const char *s);
extern void ldm200_set_num_u32(uint32_t number);
extern void ldm200_set_num_32(int32_t number);
extern void ldm200_set_hex(uint32_t number);
extern void ldm200_buff_fill(char sign);
extern void ldm200_buff_clear(void);

extern void ldm200_display(void);

#endif /* LDM200_H_ */
