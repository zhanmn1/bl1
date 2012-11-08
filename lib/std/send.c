#include <uart/uart.h>
#include <my_stdio.h>

static int my_itoa(__u32 num)
{
	int i, ret;
	char char_buff[32] = {0};

	i = 0;
	while (num) {
		char_buff[i++] = (num % 10) + '0';
		num /= 10;
	}

	ret = i--;
	do {
		uart_send_byte(char_buff[i]);
	} while (i--);

	uart_send_byte('\n');

	return ret;
}

static int my_htoa(__u32 num)
{
	int i, ret;
	char char_buff[32];

	i = 0;
	while (num) {
		char_buff[i++] = ((num % 16) > 9) ? num % 16 + 'a' - 10 : num % 16 + '0';
		num = num >> 4;
	}

	uart_send_byte('0');
	uart_send_byte('x');
	ret = i--;
	do {
		uart_send_byte(char_buff[i]);
	} while (i--);

	uart_send_byte('\n');

	return ret;
}

int send(__u32 num, int flag)
{
	int ret = 0;

	switch (flag) {
	case 10:
		ret = my_itoa(num);
		break;
	case 16:
		ret = my_htoa(num);
		break;
	default:
		break;
	}

	return ret;
}
