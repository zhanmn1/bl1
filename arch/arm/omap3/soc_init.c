#include <io.h>
#include <arm/omap3.h>

int soc_init(void)
{
	writel(VA(CM_FCLKEN_WKUP), 1 << 5);
	writel(VA(CM_ICLKEN_WKUP), 1 << 5);
	while (readl(VA(CM_IDLEST_WKUP)) & (1 << 5));

	writel(VA(WDTTIMER2 + WSPR), 0xaaaa);
	while (readl(VA(WDTTIMER2 + WWPS)));
	writel(VA(WDTTIMER2 + WSPR), 0x5555);

	return 0;
}
