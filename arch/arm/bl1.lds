ENTRY(_start)

SECTIONS
{
    .text ALIGN(4):
    {
	*(.text)
    }

    .bl1_init ALIGN(4):
    {
		*(.code.init)
		init_call_begin = .;
        *(.Level4.bl1)
		init_call_end = ALIGN(4);
    }

    .data ALIGN(4):
    {
        *(.data)
    }

    .rodata ALIGN(4):
    {
        *(.rodata)
    }

    .bss ALIGN(4):
    {
        *(.bss)
    }

    _end = ALIGN(4);
}
