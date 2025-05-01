;;; Copyright (c) 2021-2025 Ufasoft  http://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com
;;;
;;; SPDX-License-Identifier: MIT

;;; BK-0010.01 Keyboard codes

$K.LE	= 10	; Left key
$K.TAB	= 11	; interrupt 274
$K.NL	= 12	; NewLine key
$K.CLS	= 14
$K.RUS	= 16
$K.LAT	= 17
$K.BC	= 23	; BC key (return previous string)
$K.DEL	= 26	; !<--
$K.INS	= 27	; !-->
$K.BS	= 30	; Backspace
$K.RI	= 31	; Right key
$K.UP	= 32	; Up key
$K.DO	= 33	; Down key
$K.RPT	= 201	; Repeat
$K.BLK	= 204	; Block editor
$K.STP	= 220	; Step



;; Cyrillic letters in KOI8 encoding
C.CY.A	= 341
C.CY.B	= 342
C.CY.G	= 347
C.CY.I	= 351
C.CY.K	= 353
C.CY.M	= 355
C.CY.O	= 357
C.CY.P	= 360
C.CY.R	= 362
C.CY.S	= 363
C.CY.T	= 364
C.CY.U	= 365
C.CY.V	= 367
C.CY.W	= 373		; 'Sh'

C.EXTM	= 214		; Exttended Memory Mode
C.CURS	= 232		; Cursor ON/OFF

; BK pseudo-graphics
C.LE	= 261
C.RI	= 276
