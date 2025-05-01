;;; Copyright (c) 2021-2022 Ufasoft  http://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com
;;;
;;; SPDX-License-Identifier: MIT

;;; BK-0010.01 Specific Addresses and macros


.INCLUDE /k1801.inc/
.INCLUDE /bkkeys.inc/

.IIF NE <<'ÿ>-377> .ERROR	; File must be in KOI-8 encoding


$F.CLR	= 40		; Color mode
$F.IVBG	= 41		; Inverse background mode
$EXTM	= 42		; Extended memory mode byte; Values: 0, 377 allow to switch on/off, any other value disables to switch off
$KFLAG	= 43		; Key flags: 200 when TAB key pressed
$F.UND	= 44		; Underline mode
$F.INV	= 45		; Inverse mode
$F.CTL	= 46		; CTRL indication mode
$F.BLK	= 47		; Block Editing mode
$F.GFX	= 50		; Graphics mode
$F.HID	= 56		; Hide Cursor mode
$KEY	= 104		; Scan code of Last pressed Key
$TKEY	= 105		; flag of pressed key
$KSLOW	= 106		; Loop Counter on Repeat Key
$KRPT	= 110		; Flag to repeat latest Key
$TABDSZ	= 111		; #Spaces on TAB key
$TABS	= 112		; .. 120 Tabulation positions
$AP2LE	= 122		; Current AP2-key Text length
$RESE1	= 123		; Not used
$AP2CU	= 126		; ..150 AP2-key Text addresses
$SCROL	= 152		; Flag of scrolling
$GPNT	= 153		; Flag of Point
$GMSK	= 154		; Mask of Graphics Point
$GSMSK	= 155		; Starting Mask
$CURSO	= 156		; Cursor position: 0..2777
$CURA	= 160		; Address of Cursor in Video Memory
$CHRCB	= 162		; Horizontal bytes/char: 1|2
$CHARS	= 164		; Chars per Screen: 400|3000
$GCUR	= 166		; Graphics Cursor
$GCURA	= 170		; Graphics Cursor Address
$GVLEN	= 172		; Graphics Vector Length
$GROWS	= 174		; Graphics Rrow counter
$GRX	= 176		; Graphics X coordinate
$GRY	= 200		; Graphics Y coordinate
$RULAT	= 112		; 0: Lat Mode, 1: Rus Mode
$ANVP	= 202		; Video memory address
$BAZVP	= 204		; Address of screen Top
$VIDCB	= 206		; Video memory size in bytes: 10000|40000
$VWOR	= 210		; Working Video memory size in bytes: 5000|36000
$BGMSK	= 212		; Background Mask: 177777|125252|52525|0
$FGMSK	= 214		; Foreground Mask
$BSMSK	= 216		; Status Line Background Mask
$FSMSK	= 220		; Status Line Foreground Mask
$CNT	= 222		; Code counter
$ICNT	= 224		; Indicator counter
$RESE2	= 226		; ..246 Not used
$TEL	= 250		; ..254 Telegraph
$OUTCP	= 256		; Copy of output port (not Used)
$KBDA	= 260		; Additional Kbd Handler
$KENTE	= 262		; Enter key code:  0: \n, other:\r
$TADDR	= 264		; Last loaded file address
$TSIZE	= 266		; Last loaded file size
$IRQ3	= 270		; ..272	Not used
$K2ISR	= 274		; ..276	Interrupt vector by AP2 key
$MPHAS	= 300		; Flag of Tape phase
$MERR	= 301		; Tape Error code. Source of byte 321 of Tape params block
$MPRD	= 302		; Flag ofTape  pseudo-reading mode
$MINC	= 304		; Tape reading increment: 0..1
$MPRMA	= 306		; Tape params address
$MSP	= 310		; Tape saved Stack Pointer
$MCSUM	= 312		; Tape Checksum
$MCNST	= 314		; Tape reading constant
$RESE3	= 316		; Not used. Not cleared by EMT14
$MPRM	= 320		; ..371 Tape params

$AURET	= 766		; address for autoloading
$III	= 2060
$RNDSAV	= 2070
$SAVJMP	= 2134
$BUF	= 2422		; Used by $IUNPK
$BUFOUT	= 3022		; Used by R.TOKEN & BASIC., at least 20 bytes

$PWRTI	= 101626	; RESTORE REGISTERS, THEN RTI
$DEMT	= 100112	; EMT handler
$MIDMBK	= 100140
$MONIT	= 100274
$ASKRD	= 100536	; Ask filename and read tape
$ASKEX	= 100552	; Ask filename and & execute tape command
$PRERR	= 100644	; Print "ERROR"
$EMT6A	= 101122	; Read key without first checks
$KBISR	= 101136
$APISR	= 101362
$OUTBS	= 103544	; Backspace handler
$MCTSS	= 110310	; Read Display State word
$PSREG	= 110346	; Save registers
$PWREG	= 110362	; Restore registers

$FONT	= 112036	; Char-Code ranges: 0x10..7F, 0xA0..0xFF

$MDMAG	= 116076

$WSTOP	= 120226	; BREAK/STOP message
$WNL	= 120233
$IVEIL	= 121052
$MONIT	= 124302
$LINE	= 125426
$RECT	= 125454
$TRAP7	= 134340	; Address of TRAP 7 instruction (Out of memory error)
$ISGUN	= 140536
$IUNPK	= 140574
$UTOA	= 140600
$RTI20	= 146444	; POP R2, R0; RTI
$COCT	= 151254
$CBIN	= 151314

$RPAR 	= 151036	; BASIC TRAP 130 handler; Parse ')'
$LPAR 	= 151046	; BASIC TRAP 127 handler; Parse '('
$SW.C0	= 151650	; BASIC TRAP 101 handler; Skip spaces; Switch by char in (R3)
$SW.C1	= 151650	; BASIC TRAP 101A handler; Switch by char in (R3)
$CL.CH	= 151704	; BASIC TRAP 102 handler; Classify char in (R3)
$ATOI	= 153072	; BASIC TRAP 110 handler; Parse int in (R3)
$COMMA	= 154610	; BASIC TRAP 126 handler; Parse ')'

$BIN	= 161672
$HEX	= 161734
$ISTR	= 161610
$OCT	= 161624
$DAL	= 162162	; Result: R1 = R1 / R2;  R3 = R1 % R2
$PACK	= 163702
$ID 	= 166646	; Int to Double
$DI	= 166760	; DI - Double to Int
$SI	= 166770	; SI - Float to Int

$ERROR	= 146706	; "ERROR WORD"
$P.INT	= 153402	; PRINT INT IN R5

$CAT	= 101102	; .WORD '@
$CLT	= 147276	; .WORD '<
$CGT	= 112557	; .WORD '>
$CLPAR	= 147311	; .WORD '(
$CPLUS	= 153472	; .WORD '+
$CCOMMA	= 154614	; .WORD ',

$DGO	= 164710

$UNPCK	= 164750
$FIX	= 176212
$DCMP	= 177034

$STAND	= 166552

$PIDV2	= 175054

$ABS	= 166566
$ATAN	= 174434
$COS	= 173566

$DADD	= 167144
$DSUB	= 167124
$APLMI	= 152606	; address of .WORD $DADD, $DSUB

$DDIV	= 170776
$DMUL	= 170210
$DSGN	= 166614
$EXP	= 171762
$INT	= 176340
$LOG	= 173052
$PUSH8	= 172450	; 4 * PUSH -(R1),
$PUSH1	= 173264	; PUSH 1.0
$RAN	= 175176
$SIN	= 173614
$SQRT	= 171350
$TAN	= 174306

$AMATH	= 152636	; address of .WORD $SQRT, $SIN, $COS, $TAN, $ATAN, $EXP, $LOG, $INT, $FIX, $ABS, $IABS, $ISGN, $DSGN

$KBCTL	= 177660
$KBDAT	= 177662
R$ROL	= 177664

$KBDI	= 100		; bit in register 177660 to disable Keyboard interrupt
$KBKEY	= 100		; bit in register 177716. =0 if there is pressed key

.IIF NDF C$M10 	C$M10 = 1		; Define API macros

.IF NE C$M10

.MACRO	.EXIT
	JMP	^o100300
	;!!!? JMP	$MONIT
.ENDM

.MACRO	.PRINT	addr
	MOV	addr, R1
	CLR	R2
	EMT	^o20
.ENDM

.MACRO  .TTYIN	ch
	EMT	^o6
	.IIF NB ch, MOV	R0, ch
.ENDM

.MACRO  .TTYOUT	ch
	.IF NB ch
		MOV	ch, R0
	.ENDC
	EMT	^o16
.ENDM

.ENDC ; C$M10
