;----------------------------------------------
;JOE BLADE
; Atom version by Kees van Oss  2013
;----------------------------------------------
	.DEFINE asm_code $0200
	.DEFINE header   1		; Header Wouter Ras emulator
	.DEFINE filenaam "JOE"

.org asm_code-22*header

.IF header
;********************************************************************
; ATM Header for Atom emulator Wouter Ras

name_start:
	.byte filenaam			; Filename
name_end:
	.repeat 16-name_end+name_start	; Fill with 0 till 16 chars
	  .byte $0
	.endrep

	.word asm_code			; 2 bytes startaddress
	.word exec			; 2 bytes linkaddress
	.word eind_asm-start_asm	; 2 bytes filelength

;********************************************************************
.ENDIF


exec  = L1851
start_asm:
	.include "topmaps.inc"
	.include "obj1.inc"
	.repeat $300
	  .byte 0
	.endrep
	.include "rodat.inc"
	.include "code.inc"
	.include "data.inc"
	.include "guardt2.inc"
	.include "shapes.inc"
	.repeat $3000-*
	  .byte 0
	.endrep
	.include "sbgnd.inc"
	.include "maps.inc"
	.repeat $5840-*
	  .byte 0
	.endrep
	.include "numbers.inc"
	.repeat $58a0-*
	  .byte 0
	.endrep
	.include "mirror.inc"
	.repeat $59a0-*
	  .byte 0
	.endrep
	.include "objdat.inc"
	.repeat $5bc0-*
	  .byte 0
	.endrep
	.include "obj2.inc"
	.include "font.inc"
	.include "int.inc"
	.include "keyscan.inc"
	.include "irq.inc"
	.include "sound.inc"
	.include "joystick.inc"

scrval:
	.byte $00,$20,$40,$60,$80,$a0,$c0,$e0
	.byte $01,$21,$41,$61,$81,$a1,$c1,$e1
	.byte $02,$22,$42,$62,$82,$a2,$c2,$e2
	.byte $03,$23,$43,$63,$83,$a3,$c3,$e3


eind_asm: