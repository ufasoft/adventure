;;; Copyright (c) 2025 Ufasoft  http://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com
;;;
;;; SPDX-License-Identifier: MIT
;;;

;; TEXT definitions

SEN.N	= 0
SEN.S	= 1
SEN.Q	= 2
SEN.E	= 3

$SEP	= 0	; Subsentence separator
$SEPEX	= 1	; Exclamation subsentence separator


$UCS	= 1	; UPPERCASE word
$THE	= 2	; the subject
$SUB	= 3	; Sub-phrase
$DQU	= 4	; "
$PAR	= 5	; (
$NUM	= 6
$CAP	= 7	; Capitalized word
$ASCIN	= 8.	; Inlined negative-terminated ASCII string
$HYPHEN	= 9.	; -
$SLA	= 10.	; /
$DOT	= 11.	; .
$EXC	= 12.	; !
$QUE	= 13.	; ?
$COL	= 14.	; :
$COM	= 15.	; ,

$THRIS	= 16.	; there is
$THRIA	= 17.	; there is a
$THRAR	= 18.	; there are
$UR.AT	= 19.	; you're at
$UR.IN	= 20.	; you're in
$YR	= 21.	; You are
$YRINA	= 22.	; You are in a


MXSCOR	= 350.	; Max possible SCORE

ABKSTR	 = 764		; Load Address for BK-0010
ASTKUP = ABKSTR

B.OBJ	= 36.

;; Location numbers
LBUILD	= 3.
LY2	= 33.



.GLOBL	the
.GLOBL	$OOFF										; 162.
.GLOBL	$WORDS, EWORDS, $SWORD, $VWORD, $OBJECT
.GLOBL	$SOFF, $SAYS, $EVERB, $MOTIO, $SUBJ, $MSG, $SUFF, $SUBS, $ROFF, LTEXT, STEXT
.GLOBL	$FDTOT, $FKNIV, $FMORE, $FSTIK
.GLOBL	$EVSEQ

;; .LINK coditions

VRBSIZ	= 35.


B.MOVE	= 167.
