;;; Copyright (c) 2025 Ufasoft  http://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com
;;;
;;; SPDX-License-Identifier: MIT

;;; Default Configuration definitions for ADVENT


; .INCLUDE /config.inc/

.MCALL	.CFG
.CFG

.LIST	ME		; Macro expansions
.ENABL	AMA		; address mode 37
.ENABL	LC


...EMT = 1		; Use EMT API for BK-0011M

;; Define C$xxxx on C.xxxx definitions
;; C.xxx are necessary because bash/make/nmake have inconsistent escaping rules of '$' char
.IIF DF C.AMAL,	C$AMAL=C.AMAL
.IIF DF C.RT11,	C$RT11=C.RT11
.IIF DF C.BK10,	C$BK10=C.BK10
.IIF DF C.BK11,	C$BK11=C.BK11


.IIF NDF C$AMAL,	C$AMAL = 1			; Amalgamation build

C$BK10	= 1
C$B11M	= 1
C$VM1	= 1

C$1801 = 0		;!!!Temporary
