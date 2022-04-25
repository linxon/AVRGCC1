/*
 * commands.h
 *
 * Created: 22.01.2022 13:00:26
 *  Author: linxon
 */


#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "typedef.h"
#ifdef USART_DISABLE_STD
#include "usart.h"
#endif

#define AT_CMD_BUFF_SIZE		32
#define AT_CMD_DELIMITER		"="
#define AT_CMD_ARGS_DELIMITER	","

typedef struct intrnl_cmd {
	const char *name;
	int8_t (*call)(void *);
} INTERNAL_CMD_t[];

extern int8_t cmd_status;

extern void cmd_init(struct intrnl_cmd (*c)[], uint8_t cmd_size);
extern void cmd_ISR_handler(void);

int8_t _cmd_handler(char *cmd);

#endif /* COMMANDS_H_ */
