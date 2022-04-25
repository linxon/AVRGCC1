/*
 * functions.h
 *
 * Created: 08.01.2022 12:01:35
 *  Author: linxon
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <ctype.h>

#include "typedef.h"

/*
#define my_isdigit_asm(c)		\
	__asm__ __volatile__ (		\
		"nop" "\n\t"			\
	)
*/

#define my_toupper(c)		(((c) >= 'a' && (c) <= 'z')? (c) + 'A' - 'a': (c))
#define my_tolower(c)		(((c) >= 'A' && (c) <= 'Z')? (c) + 'a' - 'A': (c))
#define my_isdigit_asm1(c, r)						\
	__asm__ __volatile__(							\
		"cpi %[sign], 0x30"					"\n\t"	\
		"brlt L1_%="						"\n\t"	\
		"cpi %[sign], 0x3A"					"\n\t"	\
		"brge L1_%="						"\n\t"	\
		"rjmp L2_%="						"\n\t"	\
		"L1_%=: "	"clr %[retval]"			"\n\t"	\
		"L2_%=: "	""								\
													\
		: [retval] "=r" (r)							\
		: [sign] "d" (c)							\
	);

extern bool my_isdigit_asm(char _c);

extern void my_delay_us(uint8_t us);
extern void my_delay_ms(uint8_t ms);
extern uint8_t my_atoi_u8(const char *s);
extern uint16_t my_atoi_u16(const char *s);
extern uint32_t my_atoi_u32(const char *s);
extern int8_t my_atoi_8(const char *s);
extern int16_t my_atoi_16(const char *s);
extern void my_itoa_u8(uint8_t num, char *dst);
extern void my_itoa_u16(uint16_t num, char *dst);
extern void my_itoa_u32(uint32_t num, char *dst);
extern void my_itoa_8(int8_t num, char *dst);
extern void my_itoa_16(int16_t num, char *dst);
extern void my_itoa_32(int32_t num, char *dst);
extern void my_itohex_u16(uint16_t num, char *dst);
extern void my_itohex_u32(uint32_t num, char *dst);
extern float my_atof(const char *s);
extern void my_strrev(char *s);
extern bool my_strcmp(const char *s1, const char *s2);
extern uint16_t crc_chk(byte *data, uint8_t length);
//extern char my_itoa(char *s);


//bool _isdigit(char c);

#endif /* FUNCTIONS_H_ */