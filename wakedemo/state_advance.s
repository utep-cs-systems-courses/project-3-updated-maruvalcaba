	.arch msp430g2553
	.p2align 2
	.text
jt:
	.word case0
	.word case1
	.word case2
	.word case3
	.word case4

	
	.global state_advance
state_advance:
	sub #2, r1
	mov.b #0, 0(r1)		;char led_changed = 0
	cmp.b #5, r12
	jhs done
	add.b r12, r12
	mov jt(r12), r0

case0:	call #red_on_all
	mov.b r12, 0(r1)
	jmp done

case1:	call #red_66
	mov.b r12, 0(r1)
	jmp done

case2:	call #toggle_red
	mov.b r12, 0(r1)
	jmp done

case3:	call #red_33
	mov.b r12, 0(r1)
	jmp done

case4:	call #red_25
	mov.b r12, 0(r1)
	jmp done

done:	mov.b 0(r1), r12
	add #2, r1
	pop r0
