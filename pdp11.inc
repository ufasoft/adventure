;;; Copyright (c) 2021-2022 Ufasoft  http://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com
;;;
;;; SPDX-License-Identifier: MIT

C.NUL	= 0
C.BEL	= 7
C.BS	= ^o10
C.HT	= ^o11
C.NL	= ^o12
C.VT	= ^o13
C.FF	= ^o14
C.CR	= ^o15
C.ESC	= ^o33
C.SP	= ^o40
C.QU	= ^o47	; '
C.SEMI	= ^o73	; Semicolon ;
C.LT	= '<
C.DEL	= ^o177


FLAG.C	= 1
FLAG.V	= 2
FLAG.Z	= 4
FLAG.N	= ^o10
FLAG.T	= ^o20

OP.NOP	= ^o240
OP.BR	= ^o400
OP.BNE	= ^o1000
OP.EMT	= ^o104000
OP.TRAP	= ^o104400

$DFLPS = 340		; default PSW for trap interrupt vectors

.MACRO	ALGN4
	.=<.+3>/4*4
.ENDM

.MACRO	ALGN8
	.=<.+7>/8.*8.
.ENDM

.MACRO	ALGN32
	.=<.+31.>/32.*32.
.ENDM

;;; Idioms

;; reg -= 2
.MACRO	DEC2	reg
	.IIF NE C$VM1,	TST	-(reg)
	.IIF EQ C$VM1,	BITB	-(reg), -(reg)
.ENDM

;; reg += 2
.MACRO	INC2	reg
	.IIF NE C$VM1,	TST	(reg)+
	.IIF EQ C$VM1,	BITB	(reg)+, (reg)+
.ENDM

;; reg += 4
.MACRO	INC4	reg
	.IIF NE C$VM1,	CMP	(reg)+, (reg)+
	.IIF EQ C$VM1,	ADD	#4, reg
.ENDM

;; Push args into Stack
.MACRO	PUSH	c, d, e, f, g, h
	.IRP	x, <c, d, e, f, g, h>
		.IIF	B, x,	.MEXIT
		MOV	x, -(SP)
	.ENDR
.ENDM

;; Pop args from Stack
.MACRO	POP	c, d, e, f, g, h
	.IRP	x, <c, d, e, f, g, h>
		.IIF	B, x,	.MEXIT
		MOV	(SP)+, x
	.ENDR
.ENDM

;; Pascal (Length-prefixed) string.
.MACRO	.ASCIP	s
	.NCHR	$nlen, ^|s|
       	.ASCII	<$nlen>"s"
.ENDM


.MACRO	.SBYT	sb
	.IF	P1
		.BYTE 0
	.IFF						; sb is known on phase 2
		.IF GT sb - 127.
       			.ERROR	sb is out of bounds
		.IFF
       			.IF LT sb + 128.
       				.ERROR	sb is out of bounds
       			.IFF
       				.BYTE	sb
       			.ENDC
		.ENDC
       	.ENDC
.ENDM

;; Signed byte with bounds check
.MACRO	.SBYTE	c, d, e, f, g, h
	.IRP	x, <c, d, e, f, g, h>
		.IIF	B, x,	.MEXIT
		.SBYT	x
	.ENDR
.ENDM
