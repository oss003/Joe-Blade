;------------------------------------------------
; Scankey A
; - A = scancode same as $FE71
; - Exit -> C=0 = key pressed
;           C=1 = key not pressed
;------------------------------------------------

keyscan:
sk12:
	ldx #0
sk1:
	cmp #10
	bcc sk5
	inx
	sec
	sbc #10
	jmp sk1
sk5:
	eor #$ff
	clc
	adc #10
	sta keyrow

	lda #1
	sta keycol

	lda $b000
	and #$f0
	ora #$f0
	ora keyrow
	sta $b000
sk3:
	cpx #0     ; Set keycol mask
	beq sk2
	dex	
	asl keycol
	jmp sk3
sk2:
	lda $b001  ; Read keycol
	and keycol
	bne sk4
sk13:
;	lda #0
	clc
	rts
sk4:
;	lda #$ff
	sec
	rts

keyrow:  .byte 0
keycol:  .byte 0
