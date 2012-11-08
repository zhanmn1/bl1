#include <init.h>
#include <uart/uart.h>

int sys_dev_init()
{
	char count = '0';
	init_func_t *init_call;
	extern init_func_t init_call_begin[], init_call_end[];

	uart_send_byte('B');
	uart_send_byte('\n');

	init_call = init_call_begin;
	while (init_call < init_call_end) {
		uart_send_byte(count++);
		uart_send_byte(':');

		(*init_call)();
		init_call++;

		uart_send_byte('\n');
	}

	uart_send_byte('E');
	uart_send_byte('\n');

	return 0;
}
