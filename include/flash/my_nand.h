#pragma once
#include <io.h>

// standard nand commands
#define NAND_CMMD_READ0         0x00
#define NAND_CMMD_READ1         0x01
#define NAND_CMMD_RNDOUT        0x05
#define NAND_CMMD_PAGEPROG      0x10
#define NAND_CMMD_READOOB       0x50
#define NAND_CMMD_ERASE1        0x60
#define NAND_CMMD_STATUS        0x70
#define NAND_CMMD_STATUS_MULTI  0x71
#define NAND_CMMD_SEQIN         0x80
#define NAND_CMMD_RNDIN         0x85
#define NAND_CMMD_READID        0x90
#define NAND_CMMD_ERASE2        0xd0
#define NAND_CMMD_RESET         0xff

#define NAND_CMMD_READSTART     0x30
#define NAND_CMMD_RNDOUTSTART   0xE0
#define NAND_CMMD_CACHEDPROG    0x15

#define NAND_CMMD_DEPLETE1      0x100
#define NAND_CMMD_DEPLETE2      0x38
#define NAND_CMMD_STATUS_MULTI  0x71
#define NAND_CMMD_STATUS_ERROR  0x72
#define NAND_CMMD_STATUS_ERROR0 0x73
#define NAND_CMMD_STATUS_ERROR1 0x74
#define NAND_CMMD_STATUS_ERROR2 0x75
#define NAND_CMMD_STATUS_ERROR3 0x76
#define NAND_CMMD_STATUS_RESET  0x7f
#define NAND_CMMD_STATUS_CLEAR  0xff

#define NAND_CMMD_NONE          -1

// Nand description
#define SOFT_ECC_DATA_LEN  256
#define SOFT_ECC_CODE_NUM  3

#define NAND_MAX_CHIPS        8
#define NAND_MAX_OOB_SIZE    64
#define NAND_MAX_PAGESIZE    2048

#define NAND_CMMD_PORT VA(GPMC_BASE + GPMC_NAND_COMMAND_0)
#define NAND_ADDR_PORT VA(GPMC_BASE + GPMC_NAND_ADDRESS_0)
#define NAND_DATA_PORT VA(GPMC_BASE + GPMC_NAND_DATA_0)

#define NAND_NCE        0x01
#define NAND_CLE        0x02
#define NAND_ALE        0x04

struct nand_chip {
	void *cmmd_port;
	void *addr_port;
	void *data_port;

	size_t write_size;
	size_t chip_size;

	int (*nand_ready)(struct nand_chip *);
	void *(*read_buff)(struct nand_chip *, void *, size_t);
};
