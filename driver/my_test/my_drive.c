#include <init.h>
#include <my_stdio.h>

static int __init_code send_test()
{
	__u32 ret;
	__u32 num = 123;

	ret = send(num, 10);
	send(ret, 10);

	num = 0xabc;
	ret = send(num, 16);
	send(ret, 10);

	return 0;
}

module_init(send_test);
