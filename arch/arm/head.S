    .global _start

    .word (_end - _start)
    .word _start

_start:
	ldr sp, =0x40204000

@	bl soc_init
@	bl nand_probe
@	mov r0, #'a'
@	bl uart_send_byte
	
	bl  sys_dev_init
	@bl render
	@bl omap_disp_init


@@@@@@@c call ID
@	mov r0, #0x90
@	mov r1, #2
@	bl nand_cmd_ctrl
@
@	mov r0, #0
@	mov r1, #4
@	bl nand_cmd_ctrl
@
@	bl nand_read_buff8
@	and r0, #0xff
@	bl itoa
@
@	mov r0, #'\n'
@	bl uart_send_byte
@
@	bl nand_read_buff8
@	and r0, #0xff
@	bl itoa


@@@@@@@@@@load oneslef
@	ldr r6, =0x6e00007c @CMD
@	ldr r7, =0x90
@	strb r7, [r6]
@
@	ldr r6, =0x6e000080 @ADR
@	ldr r7, =0x00
@	strb r7, [r6]
@
@	ldr r6, =0x6e000084 @DATA
@	ldrb r0, [r6]
@	ldrb r7, [r6]
@
@	and r0, #0xff
@	bl itoa
@
@	mov r0, #'\n'
@	bl uart_send_byte
@
@	mov r0, r7
@	and r0, #0xff
@	bl itoa
@
@	mov r0, #'\n'
@	bl uart_send_byte
@	
@	ldr r6, =0x6e00007c @CMD
@	mov r0, #0x00
@	strb r0, [r6]
@
@	ldr r6, =0x6e000080 @ADR
@	mov r0, #0x00
@	strb r0, [r6]
@	strb r0, [r6]
@	strb r0, [r6]
@	strb r0, [r6]
@	strb r0, [r6]
@
@	ldr r6, =0x6e00007c @CMD
@	mov r0, #0x30
@	strb r0, [r6]
@
@busy:
@	ldr r6, =0x6e000054 @BUSY
@	ldr r1, [r6]
@	and r1, #0x01
@	cmp r1, #0
@	beq busy
@
@	ldr r0, =_end
@	ldr r1, =_start
@	sub r7, r0, r1
@
@	ldr r6, =0x6e000084 @DATA
@
@	ldr r5, =0x40201000
@	mov r4, r5
@	mov r7, #12
@
@copy:
@	ldr r0, [r6]
@	bl itoa
@	@str r0, [r5], #4	
@
@	sub r7, r7, #4
@	cmp r7, #0
@	bne   copy 
@
@	@mov pc, r4
loop:
	sub pc, pc, #8
@
@itoa:
@	stmfd sp!, {fp, lr}
@
@	mov r3, r0
@	mov r2, #0
@	l2:
@	mov r0, r3, lsl r2
@	mov r0, r0, lsr #28
@	and r0, #0x0f
@	cmp r0, #10
@	blo next
@	add r0, r0, #'A'
@	sub r0, r0, #10
@	b   put
@next:
@	add r0, r0, #'0'
@put:
@	bl uart_send_byte
@	add r2, r2, #4
@	cmp r2, #32
@	bne l2
@
@	mov r0, #'\n'
@	bl uart_send_byte
@
@	ldmfd sp!, {fp, pc}
@
@uart_send_byte:
@	stmfd sp!, {fp, lr}
@
@	ldr r1, thr @used
@	strb r0, [r1]
@
@	ldmfd sp!, {fp, pc}
@
thr:
	.word 0x49020000
str:
	.asciz "hello, world!"
	.align 2

	.data
space:
	.space 2048, 0xff
