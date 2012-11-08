#include <io.h>
#include <delay.h>
#include <uart/uart.h>

static void omap3_uart_send_byte(__u8 b)
{
	while (readb(VA(UART_BASE + SSR_REG)) & 0X01);

	writeb(VA(UART_BASE + THR_REG),b);
}

static __u8 omap3_uart_recv_byte(void)
{
	while(!(readb(VA(UART_BASE + LSR_REG))) & 0x01);

	return readb(VA(UART_BASE + RHR_REG));
}

__u32 uart_rxbuf_count()
{
	return readb(VA(UART_BASE + LSR_REG));
}

static int omap3_uart_init(void)
{
	__u32 word;
	__u16 half;

	word = readl(VA(CM_CLKSEL3_PLL));
	word &= ~0x1f;
	word |= 0x09;
	writel(VA(CM_CLKSEL3_PLL), word);

	half = 1 << 8;
	writew(VA(PADCONF_UART3_RT), half);

	// GPIO_166 config mode 0.
	half = readw(VA(PADCONF_UART3_TX));
	half &= ~0x7;
	writew(VA(PADCONF_UART3_TX), half);

	// enable uart3's fclk
	word = readl(VA(CM_FCLKEN_PER));
	word |= 1 << 11;
	writel(VA(CM_FCLKEN_PER), word);

	return 0;
}

DECLARE_UART_INIT(omap3_uart_init);
DECLARE_UART_SEND(omap3_uart_send_byte);
DECLARE_UART_RECV(omap3_uart_recv_byte);
