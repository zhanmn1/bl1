#pragma once
#include <io.h>

#define OMAP3_DSS_BASE            0x48050000
#define OMAP3_DISPC_CONTROL       0x440
#define OMAP3_DISPC_SIZE_LCD      0x47C
#define OMAP3_DISPC_GFX_BA0       0x480
#define OMAP3_DISPC_GFX_POSITION  0x488
#define OMAP3_DISPC_GFX_SIZE      0x48C
#define OMAP3_DISPC_GFX_ATTRBUTES 0x4A0

#define VM_HEIGH    480
#define VM_WIDTH    640
#define MEM_START   0x80000000

#define dss_writel(reg, val) \
	writel((OMAP3_DSS_BASE + reg), val);

int omap_disp_init();
