/*
 * timer.c
 *
 * Created: 03.03.2022 18:23:03
 *  Author: linxon
 */

#include "timer.h"

static TIMER_COUNTER_t *tmr_data;
static bool loop_end = FALSE;

static TIMER_TASK_t *tmr_task_list;

bool timer_loop_begin(struct timer_counter_t *t_cnt_d) {
	tmr_data = t_cnt_d;

	if (loop_end == TRUE)
		return loop_end = FALSE;

	if (tmr_data->work_cnt == 0) {
		loop_end = FALSE;
		tmr_data->work_cnt = tmr_data->count;
	}

	return TRUE;
}

bool timer_loop_until_is_set(TIMER_DELAY_MODE_t mode) {
	(void) --tmr_data->work_cnt;

	if (tmr_data->work_cnt == 0) {
		loop_end = TRUE;
		return FALSE;
	}

	if (mode == TIMER_DELAY_MODE_MS)
		my_delay_ms(tmr_data->div);
	else
		my_delay_us(tmr_data->div);

	return TRUE;
}

inline void timer_reset_counter(void) {
	tmr_data->work_cnt = 0;
}

void timer_ISR_next_task(void) {
	//if task > 3; then 0; fi
}

void timer_task_run(struct timer_task_t (*t)[], uint8_t size) {
	tmr_task_list = t;
}

