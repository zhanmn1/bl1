#pragma once

int uart_init(void);
int uart_send_byte(__u8);
__u8 uart_recv_byte();

#define DECLARE_UART_INIT(func) \
	int uart_init(void) __attribute__ ((alias(#func)))

#define DECLARE_UART_SEND(func) \
	int uart_send_byte(__u8 b) __attribute__ ((alias(#func)))

#define DECLARE_UART_RECV(func) \
	__u8 uart_recv_byte() __attribute__ ((alias(#func)))
