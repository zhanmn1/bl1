#include <display/omap3_display.h>

int omap_disp_init(void)
{
	dss_writel(VA(DISPC_SIZE_LCD), (VM_HEIGH - 1) << 16 | (VM_WIDTH - 1));
	dss_writel(VA(DISPC_GFX_BA0), MEM_START);
	dss_writel(VA(DISPC_GFX_POSITION), 0);
	dss_writel(VA(DISPC_GFX_SIZE), ((VM_HEIGH - 1) << 16 | (VM_WIDTH - 1)));
	dss_writel(VA(DISPC_GFX_ATTRIBUTES), 0X0C << 1 | 1);
	dss_writel(VA(DISPC_CONTROL), 1 << 16 | 1 << 15 | 1 << 8 | 1 << 3 | 1);

	return 0;
}
