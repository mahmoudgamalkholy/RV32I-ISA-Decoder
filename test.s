	.file	"test.cpp"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	_Z11my_functionv
	.type	_Z11my_functionv, @function
_Z11my_functionv:
.LFB0:
	.cfi_startproc
	addi	sp,sp,-32
	.cfi_def_cfa_offset 32
	sw	ra,28(sp)
	sw	s0,24(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	addi	s0,sp,32
	.cfi_def_cfa 8, 0
	sw	zero,-20(s0)
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	nop
	lw	ra,28(sp)
	.cfi_restore 1
	lw	s0,24(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 32
	addi	sp,sp,32
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE0:
	.size	_Z11my_functionv, .-_Z11my_functionv
	.align	2
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	addi	sp,sp,-80
	.cfi_def_cfa_offset 80
	sw	ra,76(sp)
	sw	s0,72(sp)
	.cfi_offset 1, -4
	.cfi_offset 8, -8
	addi	s0,sp,80
	.cfi_def_cfa 8, 0
	li	a5,15
	sw	a5,-20(s0)
	li	a5,20
	sw	a5,-24(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	add	a5,a4,a5
	sw	a5,-28(s0)
	lw	a4,-24(s0)
	lw	a5,-20(s0)
	sub	a5,a4,a5
	sw	a5,-32(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	and	a5,a4,a5
	sw	a5,-36(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	or	a5,a4,a5
	sw	a5,-40(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	xor	a5,a4,a5
	sw	a5,-44(s0)
	lw	a5,-20(s0)
	slli	a5,a5,2
	sw	a5,-48(s0)
	lw	a5,-24(s0)
	srai	a5,a5,1
	sw	a5,-52(s0)
	lw	a4,-20(s0)
	li	a5,15
	bne	a4,a5,.L3
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L3:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	beq	a4,a5,.L4
	lw	a5,-20(s0)
	addi	a5,a5,2
	sw	a5,-20(s0)
.L4:
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	bge	a4,a5,.L5
	lw	a5,-20(s0)
	sw	a5,-24(s0)
.L5:
	call	_Z11my_functionv
	li	a5,100
	sw	a5,-68(s0)
	li	a5,200
	sw	a5,-64(s0)
	li	a5,300
	sw	a5,-60(s0)
	lw	a5,-64(s0)
	sw	a5,-56(s0)
	lw	a5,-56(s0)
	sw	a5,-60(s0)
	li	a5,0
	mv	a0,a5
	lw	ra,76(sp)
	.cfi_restore 1
	lw	s0,72(sp)
	.cfi_restore 8
	.cfi_def_cfa 2, 80
	addi	sp,sp,80
	.cfi_def_cfa_offset 0
	jr	ra
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (14.2.0+19) 14.2.0"
	.section	.note.GNU-stack,"",@progbits
