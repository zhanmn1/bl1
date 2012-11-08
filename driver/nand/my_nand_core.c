#include <io.h>
#include <delay.h>
#include <flash/my_nand.h>

#define NAND_TIMEOUT	(1 << 14)

/*  asm test
void nand_cmd_ctrl(__u8 arg, __u32 ctrl)
{
	if (NAND_CLE == ctrl)
		writeb(NAND_CMMD_PORT, arg);
	else
		writeb(NAND_ADDR_PORT, arg);
}

__u8 nand_read_buff8()
{
	return readb(NAND_DATA_PORT);
}
*/

#if 0
static void nand_cmd_ctrl(struct nand_chip *nand, __u8 arg, __u32 ctrl)
{
	if (ctrl & NAND_CLE)
		writeb(NAND_CMMD_PORT, arg);
	else
		writeb(NAND_ADDR_PORT, arg);
}

static void *nand_read_buff8(struct nand_chip *nand, void *buff, size_t size
)
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

	if (NULL == nand->nand_ready) {
#ifdef CONFIG_NAND_DEBUG
		printf("nand_read() is NULL!\n");
#endif
		return -1;
	}
	for (i = 0; i < NAND_TIMEOUT; i++) {
		if (nand->nand_ready(nand))
			return i;

#ifdef CONFIG_NAND_DEBUG
		printf("Nand Timeout !\n");
#endif
		return -1;
	}

	udelay(0x500);

	return 0;
}

static void nand_commond(struct nand_chip *nand, __u32 cmd, int row, int col)
{
	nand_cmd_ctrl(nand, cmd, NAND_CLE);

	if (col != -1) {
		nand_cmd_ctrl(nand, col & 0xff, NAND_ALE);
		nand_cmd_ctrl(nand, (col >> 8) & 0xff, NAND_ALE);
	}

	if (row != -1) {
		nand_cmd_ctrl(nand, row & 0xff, NAND_ALE);
		nand_cmd_ctrl(nand, (row >> 8) & 0xff, NAND_ALE);
	}

	switch (cmd) {
	case NAND_CMMD_READ0:
		nand_cmd_ctrl(nand, NAND_CMMD_READSTART, NAND_ALE);
		break;

	default:
		break;
	}

	nand->nand_ready(nand);
}

//fix me
int nand_prebe(struct nand_chip *nand)
{
	__u8 dev_id, ven_id, ex_info;

	nand_commond(nand, NAND_CMMD_RESET, -1, -1);
	nand_commond(nand, NAND_CMMD_READID, 0, 0);

	dev_id = readb(nand->data_port);
	ven_id = readb(nand->data_port);

	ex_info = readb(nand->data_port);
	ex_info = readb(nand->data_port);

	nand->write_size = KB(1) << (ex_info & 0x3);
	if (ex_info & (1 << 6))
		nand->read_buff = nand_read_buff16;
	else
		nand->read_buff = nand_read_buff8;

}
#endif
