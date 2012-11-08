#include <init.h>
#include <display/omap3_display.h>

static int __init_code render(void)
{
	int i, j;
	unsigned char *mem = (unsigned char *)MEM_START;

	omap_disp_init();

	for (i = 0; i < VM_WIDTH; i++) {
		for (j = 0; j < VM_HEIGH; j++) {
			*mem++ = 0x00;
			*mem++ = 0x00;
			*mem++ = 0xFF;
			mem++;
		}
	}

	return 0;
}

module_init(render);
