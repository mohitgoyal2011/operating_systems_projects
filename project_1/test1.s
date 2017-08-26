	.file	"test1.c"
	.text
	.type	RDTSC, @function
RDTSC:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
#APP
# 9 "test1.c" 1
	rdtsc
# 0 "" 2
#NO_APP
	movl	%eax, -8(%rbp)
	movl	%edx, -4(%rbp)
	movl	-4(%rbp), %eax
	salq	$32, %rax
	movq	%rax, %rdx
	movl	-8(%rbp), %eax
	orq	%rdx, %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	RDTSC, .-RDTSC
	.globl	functioncall
	.type	functioncall, @function
functioncall:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movl	%r8d, -36(%rbp)
	movl	%r9d, -40(%rbp)
	movl	-20(%rbp), %edx
	movl	-24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	functioncall, .-functioncall
	.section	.rodata
.LC0:
	.string	"\n%lu %lu %lu"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$2, -48(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdx
	movl	$8, %esi
	movl	$0, %edi
	movl	$0, %eax
	call	sched_setaffinity
	movq	$0, -40(%rbp)
	movq	$0, -32(%rbp)
	movq	$0, -40(%rbp)
	jmp	.L5
.L6:
	movl	$0, %eax
	call	RDTSC
	movq	%rax, -24(%rbp)
	subq	$8, %rsp
	pushq	$7
	movl	$6, %r9d
	movl	$5, %r8d
	movl	$4, %ecx
	movl	$3, %edx
	movl	$2, %esi
	movl	$1, %edi
	call	functioncall
	addq	$16, %rsp
	movl	$0, %eax
	call	RDTSC
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	subq	-24(%rbp), %rax
	movq	%rax, %rcx
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addq	$1, -40(%rbp)
.L5:
	cmpq	$9999999, -40(%rbp)
	jle	.L6
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L7
	call	__stack_chk_fail
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.1) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
