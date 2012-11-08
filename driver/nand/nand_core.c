#include <io.h>
#include <delay.h>
#include <flash/nand.h>

#define NAND_TIMEOUT         (1 << 14)
#define IS_LARGE_PAGE(nand)  (nand->write_size >= KB(1))

#if 0
static void nand_cmd_ctrl(struct nand_chip *nand, __u8 arg, __u32 ctrl)
{
	if (ctrl & NAND_CLE)
		writeb(nand->cmmd_port, arg);
	else // if (ctrl & NAND_ALE)
		writeb(nand->addr_port, arg);
}

static void *nand_read_buff8(struct nand_chip *nand, void *buff, size_t size)
{
	__u8 *data;

	for (data = buff; data < (__u8 *)(buff + size); data++)
		*data = readb(nand->data_port);

	return data;
}

static void *nand_read_buff16(struct nand_chip *nand, void *buff, size_t size)
{
	__u16 *data;

	for (data = buff; data < (__u16 *)(buff + size); data++)
		*data = readw(nand->data_port);

	return data;
}

static int nand_wait_ready(struct nand_chip *nand)
{
	int i;

	if (nand->nand_ready) {
		for (i = 0; i < NAND_TIMEOUT; i++) {
			if (nand->nand_ready(nand))
				return i;
		}

#ifdef CONFIG_NAND_DEBUG
		printf("Nand Timeout!\n");
#endif
		return -1;
	}

	udelay(0x500);

	return 0;
}

static void nand_command(struct nand_chip *nand,
		__u32 cmd, int row, int col)
{
	nand_cmd_ctrl(nand, cmd, NAND_CLE);

	if (col != -1) {
		nand_cmd_ctrl(nand, col & 0xff, NAND_ALE);

		if (IS_LARGE_PAGE(nand))
			nand_cmd_ctrl(nand, (col >> 8) & 0xff, NAND_ALE);
	}

	if (row != -1) {
		nand_cmd_ctrl(nand, row & 0xff, NAND_ALE);
		nand_cmd_ctrl(nand, (row >> 8) & 0xff, NAND_ALE);

		if (nand->chip_size > (1 << 27))
			nand_cmd_ctrl(nand, (row >> 16) & 0xff, NAND_ALE);
	}

	switch (cmd) {
		case NAND_CMMD_READ0:
			if (IS_LARGE_PAGE(nand))
				nand_cmd_ctrl(nand, NAND_CMMD_READSTART, NAND_CLE);

		default:
			break;
	}

	nand_wait_ready(nand); // fixme: not need for READID
}

static inline void config_nand(struct nand_chip *nand,
		const struct nand_desc *desc)
{
	__u8 ext_id;

	nand->chip_size  = desc->size & 0xFFF00000;
	nand->write_size = desc->size & 0x000FFFFF;

	if (!nand->write_size) {
		ext_id = readb(nand->data_port);
		ext_id = readb(nand->data_port);

		nand->write_size = KB(1) << (ext_id & 0x3);
	}

#ifdef CONFIG_NAND_DEBUG
	printf("NAND page size = 0x%x, chip size = 0x%x\n",
			nand->write_size, nand->chip_size);
#endif

	if (!nand->read_buff) {
		if (desc->flags & NAND_BUSWIDTH_16)
			nand->read_buff = nand_read_buff16;
		else
			nand->read_buff = nand_read_buff8;
	}
}

static int omap3_nand_ready(struct nand_chip *nand)
{
	return readl(VA(GPMC_BASE + GPMC_STATUS)) & (1 << 8);
}

int nand_init(struct nand_chip *nand)
{
	writel(VA(GPMC_BASE + SYSCONFIG), 0x10);
	writel(VA(GPMC_BASE + IRQENABLE), 0x0);
	writel(VA(GPMC_BASE + TIMEOUT), 0x0);
	writel(VA(GPMC_BASE + GPMC_CONFIG_CS0 + GPMC_CONFIG_7), 0x0);

	udelay(0x100);

	writel(VA(GPMC_BASE + GPMC_CONFIG_CS0 + GPMC_CONFIG_1), 0x1800);
	writel(VA(GPMC_BASE + GPMC_CONFIG_CS0 + GPMC_CONFIG_2), 0x00141400);
	writel(VA(GPMC_BASE + GPMC_CONFIG_CS0 + GPMC_CONFIG_3), 0x00141400);
	writel(VA(GPMC_BASE + GPMC_CONFIG_CS0 + GPMC_CONFIG_4), 0x0F010F01);
	writel(VA(GPMC_BASE + GPMC_CONFIG_CS0 + GPMC_CONFIG_5), 0x010C1414);
	writel(VA(GPMC_BASE + GPMC_CONFIG_CS0 + GPMC_CONFIG_6), 0x1F0F0A80);

	writel(VA(GPMC_BASE + GPMC_CONFIG_CS0 + GPMC_CONFIG_7), (0x8 & 0xf) << 8 | ((0x0c000000 >> 24) & 0x3f) | 1 << 6);

	udelay(0x100);

	nand->cmmd_port = VA(GPMC_BASE + GPMC_NAND_COMMAND_0);
	nand->addr_port = VA(GPMC_BASE + GPMC_NAND_ADDRESS_0);
	nand->data_port = VA(GPMC_BASE + GPMC_NAND_DATA_0);
	nand->nand_ready = omap3_nand_ready;

	return 0;
}

int nand_probe(struct nand_chip *nand)
{
	int i;
	__u8 dev_id, ven_id;

	nand_init(nand);

//	nand_command(nand, NAND_CMMD_RESET, -1, -1);

//	nand_command(nand, NAND_CMMD_READID, -1, 0);

//	ven_id = readb(nand->data_port);
//	dev_id = readb(nand->data_port);

//	return ven_id;
	return 0;
}
#endif
