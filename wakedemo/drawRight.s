	.arch msp430g2553
	.p2align 2
	.text

	.extern y
	.global drawRight
drawRight:
	sub #6, r1		;make room for local vars
	cmp.b #0,&y		;y-0
	jge skip		;if(y >= 0), skip
	add.b #128, &y		;y+=128
skip:
	mov.b #30, 0(r1)	;r=30
loop1:
	mov.b #0, 2(r1)		; c=0
loop2:	
	mov.b &y, 4(r1)		;s=y
	add.b 2(r1), 4(r1)	;s+=c
	cmp.b #0, 4(r1)		;s-0
	jge skip2
	add.b #128, 4(r1)	;s+=128
	mov.b 4(r1), r12	;parameter 1 = s
	mov.b 0(r1), r13	;parameter 2 = r
	mov #0x0000, r14	;parameter 3 = COLOR_BLACK
	call #drawPixel
	jmp endloop2
	
skip2:
	mov.b &y, r12		;r12 = y
	add.b 2(r1), r12	;y+c = r12
	mov.b 0(r1), r13	;p2 = r
	mov #0x0000, r14	;p3 = COLOR_BLACK
	call #drawPixel

endloop2:
	add.b #1, 2(r1)		;c++
	cmp.b #10, 2(r1)		;c-10
	jlo loop2 
	add.b #1, 0(r1)		;r++
	cmp.b #40, 0(r1)		;r-40
	jhs endloop1
	jmp loop1

endloop1:
	mov.b #30, 0(r1)	;r = 30
loop3:
	mov.b #0, 2(r1)		;c = 0
loop4:
	mov.b &y, 4(r1)		;s = y
	add.b 2(r1), 4(r1)	;s += y
	sub.b #5, 4(r1)		;s -= 5
	cmp.b #0, 4(r1)		;s-0
	jge skip3
	add.b #128, 4(r1)	;s+= 128
	mov.b 4(r1), r12	;p1 = s
	mov.b 0(r1), r13	;p2 = r
	mov #0xffff, r14	;p3 = COLOR_WHITE
	call #drawPixel
	jmp endloop4
skip3:
	mov.b &y, r12		;p1 = y
	add.b 2(r1), r12	;p1 = y+c
	sub.b #5, r12		;p1 = y+c-5
	mov.b 0(r1), r13	;p2 = r
	mov #0xffff, r14	;p3 = COLOR_WHITE
	call #drawPixel
endloop4:
	add.b #1, 2(r1)		;c++
	cmp.b #5, 2(r1)		;c-5
	jlo loop4
	add.b #1, 0(r1)		;r++
	cmp.b #40, 0(r1)	;r-40
	jhs endloop3
	jmp loop3
endloop3:
	add.b #5, &y		;y+=5
	add #6, r1
	pop r0
