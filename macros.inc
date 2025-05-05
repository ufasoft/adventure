;;; Copyright (c) 2025 Ufasoft  http://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com
;;;
;;; SPDX-License-Identifier: MIT
;;;

;; Macros and VERBs/NOUNs definitions

.INCLUDE /pdp11.inc/
.INCLUDE /rt11.inc/
.INCLUDE /k1801.inc/

.INCLUDE /defcfg.inc/
.INCLUDE /text.inc/

.IF NE C$BK10
	C$M10	= 0		; Don't define API macros
	.INCLUDE /bk1001.inc/
.ENDC


CURPOS	= ^o474		; Pointer to Next char to read
$SPBUF	= ^o477		; SP
$BUF	= ^o500


HNTMAX	= 5.
LOCSIZ	= 140.		; Number of locations. Must be even.
OBJMAX	= 55.
MAXDIE	= 3		; Number of reincarnation messages available
FSTTRS	= 41.
NUMTRS	= 15.
MAXTRS	= OBJMAX
CLSSES	= 9.

DALTLC	= 18.		; Alternate initial loc for DWARF, in case one of them starts out on top of the adventurer
CHLOC	= 114.		; Chest location
CHLOC2	= 140.		; The dead end in the other maze has its loc



$CALL1	= 141.		; 301
$CALL2	= 142.		; 302
$CALL3	= 143.		; 303
$ESAY	= 157.
$PROB	= 158.		; With probability N
$UCND	= 159.		; Unconditional but prohibited for DWARVES
$CARRY	= 160.
$HERE	= 161.		; Must be carrying or in same room
$PRN0	= 162.		; PROP(n) != 0
$PRN1	= 163.		; PROP(n) != 1
$PRN2	= 164.		; PROP(n) != 2
$PRN4	= 166.		; PROP(n) != 4


.GLOBL	ABB ;, ABBLOC
.GLOBL	STICK, PANIC, DTOTAL, SCORE, BONUS, TALLY, TALLY2, NUMDIE, ABBNUM
.GLOBL	DLOC, DSEEN, REPL, DESCR
.GLOBL	ODLOC, PLAC, FIXD, PLACE, FIXED, PROPS
.GLOBL	PWORD, PUTS, PEOS, PSENT, PSENT1, READ$, RDWORD, READ$B, READ$C, P.CR
.GLOBL	PSINT, ABB, TOTING, FINDEN, UNPACK
.GLOBL	WD1, WD2, VERB, OBJ, INP2
.GLOBL	$COM, $DOT, LPROM
.GLOBL	ATTACK, CLOCK1, CLOCK2, CLOSED, CLOSNG, DALTLC, DETAIL, DFLAG, BSCORE, DKILL, FOOBAR, GAVEUP
.GLOBL	HOLDNG, HINTS, HINTED, HINTLC, HTURNS, HPRICE, HOLDNG
.GLOBL	KNFLOC, LIMIT, LMWARN, TURNS, WZDARK
.GLOBL	LOC, OLDLC2, OLDLOC
.GLOBL	INIT, PRVEMT, PCHR.2, PCHR.3, STAR10, IMGEND, B.BVAR, CVAL, RET.1, FNDLOC
.GLOBL	LIGHTS, WATERS, NOPIRA, FORCES, $TRAVEL
.GLOBL	UCASE, EOP, EOS, EOW
.GLOBL	$START, BKINIT, BKINIC, ASAVE, RTSAVE, BKSAVE, ARND, RTRND, BKRND, BKRND1, AEXIT
.GLOBL	O.WD2, O.OBJ, O.VERB, O.LOC
.GLOBL	I.TRAP, I.EMT, I.SPK1, I.SPK2, AREA, AGTLN, GTLNRT, GTLN10
.GLOBL	RMTROL

;, I.M, I.VE

;; Input:  R1: location
;; Returns: R5: pointer in $TRAVEL of the first option at location R1
;;  SF=1 if R1 < 1
.MACRO	.KEY
	TRAP	1
.ENDM	.KEY


;; Print SPACE and unsigned integer R1
.MACRO	.P.U16
	TRAP	2
.ENDM	.P.U16


;; Returns
;;   R1: property of `o`
.MACRO	.PROP	o
	TRAP	6
	.WORD	o
.ENDM	.PROP

.MACRO	.BRANC	code, b, lab
	TRAP	code
	.BYTE	b
	.SBYT	<lab-.-1/2>
.ENDM	.BRANC

;; If Property of `o` or R1 ==0 then branch to `lab`
.MACRO	.PRP0	o, lab
	.BRANC	<^o50>, o, lab
.ENDM	.PRP0

.MACRO	.PRP0P	o, m
	TRAP	^o150
	.BYTE	o
	.BYTE	m
.ENDM	.PRP0P

;; If Property of `o` or R1 !=0 then branch to `lab`
.MACRO	N.PRP0	o, lab
	.BRANC	<^o250>, o, lab
.ENDM	N.PRP0

;; If Property of `o` or R1 ==1 then branch to `lab`
.MACRO	.PRP1	o, lab
	.BRANC	<^o57>, o, lab
.ENDM	.PRP1

;; If Property of `o` or R1 !=1 then branch to `lab`
.MACRO	N.PRP1	o, lab
	.BRANC	<^o257>, o, lab
.ENDM	N.PRP1

;; If Property of `o` or R1 !=0 then print `m`
.MACRO	N.PR0P	o, m
	TRAP	^o350		; .PROP OBJ
	.BYTE	o
	.BYTE	m
.ENDM	N.PR0P

;; If Property of `o` or OBJ ==-1 then branch to `lab`
.MACRO	P.MI	o, lab
	.BRANC	<^o54>, o, lab
.ENDM	P.MI

;; If Property of `o` or OBJ ==-1 then print `m`
.MACRO	P.MI.P	o, m
	TRAP	^o154
	.BYTE	o
	.BYTE	m
.ENDM	P.MI.P

;; If Property of `o` or OBJ >= 0 then branch to `lab`
.MACRO	P.PL	o, lab
	.BRANC	<^o254>, o, lab
.ENDM	P.PL


;; Returns:
;;  R0: Object (R4)+
;;       if (R4)==0, then OBJ
;;       if (R4)==-1, then R1
;;       if (R4)==-3, then R3 + B.OBJ
;;  R5: address of the Object in PLACE array
;;  ZF=1 if Toting the Object
.MACRO	.OB2PL
	TRAP	^o51
.ENDM	.OB2PL

;; Set value from v ?? R2 to property `o`
.MACRO	.SPROP	o, v
	TRAP	7
	.BYTE	o
	.IF	NB v
		.BYTE	v
	.IFF
		.BYTE	-1
	.ENDC
.ENDM	.SPROP


;; CMPB OBJ, #o; BEQ lab
.MACRO	O.EQ	o, lab
	.BRANC	<4>, o, lab
.ENDM	O.EQ

;; CMPB OBJ, #o; BEQ .RSPKR m
.MACRO	O.EQ.P	o, m
	TRAP	^o104
	.BYTE	o
	.BYTE	m
.ENDM	O.EQ.P


;; CMPB OBJ, #o; BNE lab
.MACRO	O.NE	o, lab
	.BRANC	<^o204>, o, lab
.ENDM	O.NE

.MACRO	O.NE.P	o, m
	TRAP	^o304
	.BYTE	o
	.BYTE	m
.ENDM	O.NE.P

;; CMPB WD1, #o; BEQ lab
.MACRO	WD1.EQ	o, lab
	.BRANC	<^o52>, o, lab
.ENDM	WD1.EQ

.MACRO	.PUTS	s
	TRAP	^o53
	.WORD	s
.ENDM	.PUTS

;; CMPB WD1, #o; BNE lab
.MACRO	WD1.NE	o, lab
	.BRANC	<^o252>, o, lab
.ENDM	WD1.NE

;; CMPB WD2, #o; BEQ lab
.MACRO	WD2.EQ	o, lab
	.BRANC	<^o14>, o, lab
.ENDM	WD2.EQ

;; CMPB WD2, #o; BNE lab
.MACRO	WD2.NE	o, lab
	.BRANC	<^o214>, o, lab
.ENDM	WD2.NE

;; CMPB VERB, #o; BEQ lab
.MACRO	V.EQ	o, lab
	.BRANC	5, o, lab
.ENDM	V.EQ

;; CMPB VERB, #o; BNE lab
.MACRO	V.NE	o, lab
	.BRANC	<^o205>, o, lab
.ENDM	V.NE

;; CMPB VERB, #o; BEQ .RSPKR m
.MACRO	V.EQ.P	o, m
	TRAP	^o105
	.BYTE	o
	.BYTE	m
.ENDM	V.EQ.P

;; Destroy o ?? R1
.MACRO	.DSTROY	o
	TRAP	^o10
       	.WORD	o
.ENDM	.DSTROY

;; If `o ?? OBJ` is here, the branch to `lab`
.MACRO	.HERE	o, lab
	.BRANC	<^o11>, o, lab
.ENDM	.HERE

;; If `o ?? OBJ` is not here, the branch to `lab`
.MACRO	N.HERE	o, lab
	.BRANC	<^o211>, o, lab
.ENDM	N.HERE

.MACRO	.HERP	o, m
	TRAP	^o111
	.BYTE	o
	.BYTE	m
.ENDM	.HERP

.MACRO	N.HERP	o, m
	TRAP	^o311
	.BYTE	o
	.BYTE	m
.ENDM	N.HERP

;; Carry `o` ?? OBJ
.MACRO	.CARRY	o
	TRAP	3
	.BYTE	o
	.BYTE	-1
.ENDM	.CARRY

;; Drop `o` or OBJ
.MACRO	.DROP	o, p
	.IF NB 	p
		TRAP	^o12
		.BYTE	o
		.BYTE	p + 2
	.IFF
		.IF NB o
			TRAP	^o12
			.BYTE	o
			.IF NB p
				.BYTE	p + 2
			.IFF
				.BYTE	0
			.ENDC

		.IFF
			TRAP	^o47
		.ENDC
	.ENDC
.ENDM	.DROP

;; Drop if toting
.MACRO	TOT.DRO	o, p
	TRAP	^o60
	.BYTE	o
	.IF NB p
		.BYTE	p + 2
	.IFF
		.BYTE	0
	.ENDC
.ENDM	TOT.DRO


;; Print sentence in R1 from table R2
.MACRO	.SPEAK
	TRAP	^o13
.ENDM	.SPEAK

;; IF byte var with offset `off` ==0 then branch to `lab`
.MACRO	IF.EQ	off, lab
	.BRANC	<^o15>, off, lab
.ENDM	IF.EQ

;; IF byte var with offset `off` ==0 then .RSPKR m
.MACRO	IF.EQP	off, m
	TRAP	^o115
	.BYTE	off
	.BYTE	m
.ENDM	IF.EQP

;; If byte var with offset `off` !=0 then branch to `lab`
.MACRO	IF.NE	off, lab
	.BRANC	<^o215>, off, lab
.ENDM	IF.NE

;; IF byte var with offset `off` !=0 then .RSPKR m
.MACRO	IF.NEP	off, m
	TRAP	^o315
	.BYTE	off
	.BYTE	m
.ENDM	IF.NEP

.GLOBL	O.CLOD, O.CLIN, O.HIN2, O.TALL, O.WZDA
.GLOBL	O.BATT, O.EGGS, O.MSG, O.CHEST, O.TROL
.GLOBL	O.UCAS

.MACRO	.CLOD	lab
	IF.EQ	O.CLOD, lab
.ENDM	.CLOD

.MACRO	.CLOSNG lab
	IF.EQ	O.CLIN, lab
.ENDM	.CLOSNG

.MACRO	.GAVEUP lab
	IF.NE	O.GAVE, lab
.ENDM	.GAVEUP

.MACRO	.TALLY lab
	IF.NE	O.TALL, lab
.ENDM	.TALLY

.MACRO	.WZDARK lab
	IF.NE	O.WZDA, lab
.ENDM	.WZDARK


;; Returns ZF=1 if Location R2 is not allowed for Pirate
.MACRO	.NOPIR
	TRAP	^o17
.ENDM	.NOPIR


;; Returns ZF=1 if LOC is found in table R3
.MACRO	.FILOC
	TRAP	^o25
.ENDM	.FILOC



;; Returns: R2: Object at LOC
;; ZF=1 if R2==0
.MACRO	.ATLOC
	TRAP	^o21
.ENDM	.ATLOC

;; Returns: R2: Object at R1
.MACRO	.ATLC
	TRAP	^o22
.ENDM	.ATLC

;; Returns R2: next object at LOC after object R2
;; Flags the same in .ATLOC
.MACRO	.NEXT
	TRAP	^o20
.ENDM	.NEXT

;; Returns: R1: random number [0..n)
.MACRO	.RND	n
	TRAP	^o23
	.WORD	n
.ENDM	.RND

;; True
.MACRO	.PCT	n, lab
	TRAP	^o24
	.BYTE	n
	.SBYT	<lab-.-1/2>
.ENDM	.PCT

;; n% of the time (n integer from 0 to 100) .RSPKR m
.MACRO	.PCTP	n, m
	TRAP	^o124
	.BYTE	n
	.BYTE	m
.ENDM	.PCTP


;; Get object o if it here
.MACRO	.TRYGE	o
	TRAP	^o26
	.WORD	o
.ENDM	.TRYGE

.MACRO	.MOVE	a, p
	.IF	NB a
		TRAP	^o27
		.BYTE	a
		.BYTE	p
	.IFF
		TRAP	^o37
	.ENDC
.ENDM	.MOVE

;; If toting `o ?? OBJ` then branch to `lab`
.MACRO	.TOT	o, lab
	TRAP	^o30
	.BYTE	o
	.SBYT	<lab-.-1/2>
.ENDM	.TOT

;; If toting `o ?? OBJ` then .RSPKR m
.MACRO	.TOTP	o, m
	TRAP	^o130
	.BYTE	o
	.BYTE	m
.ENDM	.TOTP

;; If not toting `o ?? OBJ` then branch to `lab`
.MACRO	N.TOT	o, lab
	TRAP	^o230
	.BYTE	o
	.SBYT	<lab-.-1/2>
.ENDM	N.TOT

;; If not toting `o ?? OBJ` then .RSPKR m
.MACRO	N.TOTP	o, m
	TRAP	^o330
	.BYTE	o
	.BYTE	m
.ENDM	N.TOTP

;; R5: poins to cons addr + 1
;; Returns:
;;  R1: Condition, R2: new Location, R5: points to next motion
;;  ZF=1 if end of entry
.MACRO	.RCOND
	TRAP	^o31
.ENDM	.RCOND

;; Returns: R1: Object number of liquid in BOTTLE
.MACRO	.LIQ
	TRAP	^o32
.ENDM	.LIQ

;; Returns: R1: Object number of liquid (if any) at LOC (WATER, OIL or 0)
.MACRO	.LIQLOC
	TRAP	^o33
.ENDM	.LIQLOC

;; Ask question #n, if the answer is "NO" branch to `lab`
;; Returns: R2: saved R1
.MACRO	.YESNO	n, lab
	.BRANC	<^o236>, n, lab
.ENDM	.YESNO

.MACRO	.YESNP	n, m
	TRAP	^o336
	.BYTE	n
	.BYTE	m
.ENDM	.YESNP



;; Print property `p or R2` of `o or OBJ`
.MACRO	.PSPEAK o, p
	TRAP	^o34
	.BYTE	o
	.IF NB,	p
		.BYTE	p+1
	.IFF
		.BYTE	0
	.ENDC
.ENDM	.PSPEAK

;; CMP LOC, #p; BEQ lab
.MACRO	L.EQ	p, lab
	.BRANC	<^o35>, p, lab
.ENDM	L.EQ

;; CMP LOC, #p; BNE lab
.MACRO	L.NE	p, lab
	.BRANC	<^o235>, p, lab
.ENDM	L.NE

.MACRO	L.NE.P	b, m
	TRAP	^o335
	.BYTE	b
	.BYTE	m
.ENDM	L.NE.P


.MACRO	R1.EQ	b, lab
	.BRANC	<^o16>, b, lab
.ENDM	R1.EQ

.MACRO	R1.NE	b, lab
	.BRANC	<^o216>, b, lab
.ENDM	R1.NE

.MACRO	R1.EQP	b, m
	TRAP	^o116
	.BYTE	b
	.BYTE	m
.ENDM	R1.EQP

.MACRO	R1.NEP	b, m
	TRAP	^o316
	.BYTE	b
	.BYTE	m
.ENDM	R1.NEP


;; CMPB R1, #b; BHI lab
.MACRO	R1.HI	b, lab
	.BRANC	<^o56>, b+1, lab
.ENDM	R1.HI

;; CMPB R1, #b; BLO lab
.MACRO	R1.LO	b, lab
	.BRANC	<^o256>, b, lab
.ENDM	R1.LO

.MACRO	R1.LOP	b, m
	TRAP	^o356
	.BYTE	b-1
	.BYTE	m
.ENDM	R1.LOP

;; CMPB LOC, #b; BHI lab
.MACRO	L.HI	b, lab
	.BRANC	<^o45>, b+1, lab
.ENDM	L.HI

;; CMPB LOC, #b; BLO lab
.MACRO	L.LO	b, lab
	.BRANC	<^o245>, b, lab
.ENDM	L.LO

;; CMPB R2, #b; BHI lab
.MACRO	R2.HI	b, lab
	.BRANC	<^o46>, b+1, lab
.ENDM	R2.HI

;; CMPB R2, #b; BLO lab
.MACRO	R2.LO	b, lab
	.BRANC	<^o246>, b, lab
.ENDM	R2.LO


;; If not met a DWARF yet (DFLAG < 2) branch to `lab`
.MACRO	N.MET	lab
	TRAP	^o55
	.BYTE	1
	.SBYT	<lab-.-1/2>
.ENDM	N.MET


.MACRO	.JUGGLE	o
	TRAP	^o40
	.WORD	o - B.OBJ
.ENDM	.JUGGLE

;; Branch lab if at place of `o`
.MACRO	.AT	o, lab
	.BRANC	<^o42>, o, lab
.ENDM	.AT

;; Branch lab if not at place of `o`
.MACRO	N.AT	o, lab
	.BRANC	<^o242>, o, lab
.ENDM	N.AT


.MACRO	N.AT.P	o, m
	TRAP	^o342
	.BYTE	o
	.BYTE	m
.ENDM	N.AT.P

;; CF=1 If location R2 moves without asking for input
.MACRO	.FORCED
	TRAP	^o43
.ENDM	.FORCED

;; CF=1 If LOC moves without asking for input
.MACRO	.FORCLOC
	TRAP	^o44
.ENDM	.FORCLOC


;; True (NF=1) if location "LOC" is dark
.MACRO	.DARK
	TRAP	^o41
.ENDM	.DARK


;; Print char c or R1
.MACRO	.P.CHR	c
	.IF NB c
		.WORD	^o7400 + c
	.IFF
		.WORD	^o7400
	.ENDC
.ENDM	.P.CHR

.MACRO	.RSPEAK	a
	.IF NB	a
		.WORD	^o7000 + a         ; using Invalid Instruction vector
	.IFF
		TRAP	0
	.ENDC
.ENDM	.RSPEAK


;; .RSPEAK a; JMP REPL
.MACRO	.RSPKR	a
	.WORD	^o107000 + a 	        ; using Invalid Instruction vector
.ENDM	.RSPKR


;; Print part of sentence
;.MACRO	.RSPK	a
;	.WORD	^o7400 + A         ; using Invalid Instruction vector
;.ENDM	.RSPK




.RADIX	10.

SAY	= 3
UNLOCK	= 4
LOCK	= 6
POUR	= 13
FIND	= 19
INVENT	= 20
RESUME	= 31
FEE	= 32
FIE	= 33
FOE	= 34
FOO	= 35
FUM	= 36

ROAD	= B.MOVE + 2
ENTER	= B.MOVE + 3
UPSTR	= B.MOVE + 4
DNSTR	= B.MOVE + 5
FOREST	= B.MOVE + 6
FORWARD	= B.MOVE + 7
BACK	= B.MOVE + 8
VALLEY	= B.MOVE + 9
STAIR	= B.MOVE + 10
EXIT	= B.MOVE + 11
OUT	= B.MOVE + 11
BUILD	= B.MOVE + 12
GULLY	= B.MOVE + 13
STREAM	= B.MOVE + 14
ROCK	= B.MOVE + 15
BED	= B.MOVE + 16
CRAWL	= B.MOVE + 17
COBBL	= B.MOVE + 18
IN	= B.MOVE + 19
SURFACE	= B.MOVE + 20
NULL	= B.MOVE + 21
DARK	= B.MOVE + 22
PSG	= B.MOVE + 23
LOW	= B.MOVE + 24
CANYON	= B.MOVE + 25

GIANT	= B.MOVE + 27
VIEW	= B.MOVE + 28
UP	= B.MOVE + 29
DOWN	= B.MOVE + 30
PIT	= B.MOVE + 31
OUTDOOR	= B.MOVE + 32
CRACK	= B.MOVE + 33
VSTEPS	= B.MOVE + 34		; see also STEP noun
DOME	= B.MOVE + 35
LEFT	= B.MOVE + 36
RIGHT	= B.MOVE + 37
HALL	= B.MOVE + 38
JUMP	= B.MOVE + 39
BARREN	= B.MOVE + 40
OVER	= B.MOVE + 41
ACROSS	= B.MOVE + 42
EAST	= B.MOVE + 43
WEST	= B.MOVE + 44
NORTH	= B.MOVE + 45
SOUTH	= B.MOVE + 46
NE	= B.MOVE + 47
SE	= B.MOVE + 48
SW	= B.MOVE + 49
NW	= B.MOVE + 50
DEBRIS	= B.MOVE + 51
HOLE	= B.MOVE + 52
WALL	= B.MOVE + 53
BROKEN	= B.MOVE + 54
Y2	= B.MOVE + 55
CLIMB	= B.MOVE + 56
LOOK	= B.MOVE + 57
FLOOR	= B.MOVE + 58
ROOM	= B.MOVE + 59
SLIT	= B.MOVE + 60
SLAB	= B.MOVE + 61
XYZZY	= B.MOVE + 62
DEPRES	= B.MOVE + 63
ENTRNC	= B.MOVE + 64
PLUGH	= B.MOVE + 65
SECRE	= B.MOVE + 66
CAVE	= B.MOVE + 67
FORK	= B.MOVE + 68	; Original 77
CROSS	= B.MOVE + 69
BEDQU	= B.MOVE + 70
PLOVE	= B.MOVE + 71
ORIENT	= B.MOVE + 72
CAVERN	= B.MOVE + 73
SHELL	= B.MOVE + 74
RESERV	= B.MOVE + 75
MAIN	= B.MOVE + 76

KEY	= B.OBJ + 1
LAMP	= B.OBJ + 2
GRATE	= B.OBJ + 3
CAGE	= B.OBJ + 4
ROD	= B.OBJ + 5
ROD2	= B.OBJ + 6
STEPS	= B.OBJ + 7
BIRD	= B.OBJ + 8
DOOR	= B.OBJ + 9
PILLOW	= B.OBJ + 10
SNAKE	= B.OBJ + 11
FISSURE	= B.OBJ + 12
TABLET	= B.OBJ + 13
CLAM	= B.OBJ + 14
OYSTER	= B.OBJ + 15
MAGZIN	= B.OBJ + 16
DWARF	= B.OBJ + 17
KNIFE	= B.OBJ + 18
FOOD	= B.OBJ + 19
BOTTLE	= B.OBJ + 20
WATER	= B.OBJ + 21	; Must be Odd
OIL	= B.OBJ + 22	; Must follow WATER
MIRROR	= B.OBJ + 23
PLANT	= B.OBJ + 24
PLANT2	= B.OBJ + 25
AXE	= B.OBJ + 28
DRAGON	= B.OBJ + 31
CHASM	= B.OBJ + 32
TROLL	= B.OBJ + 33
TROLL2	= B.OBJ + 34
BEAR	= B.OBJ + 35
MESSAGE	= B.OBJ + 36
VEND	= B.OBJ + 38
BATTER	= B.OBJ + 39
CARPET	= B.OBJ + 40

NUGGET	= B.OBJ + 41
DIAMOND	= B.OBJ + 42
SILVER	= B.OBJ + 43
JEWEL	= B.OBJ + 44
COINS	= B.OBJ + 45
CHEST	= B.OBJ + 46
EGGS	= B.OBJ + 47
TRIDNT	= B.OBJ + 48
VASE	= B.OBJ + 49
EMRALD	= B.OBJ + 50
PYRAM	= B.OBJ + 51
PEARL	= B.OBJ + 52
RUG	= B.OBJ + 53
SPICES	= B.OBJ + 54
CHAIN	= B.OBJ + 55

.RADIX	8.
