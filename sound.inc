;---------------------------------------------------
; SOUND A,X,Y, produce tone
;
; A = Duration (1-255) * 0,005 usec
; X = Pitch (9-19)
; Y = Octave (0-7)
;---------------------------------------------------

dur_val   = $64
pit_val   = $65
oct_val   = $66

sound:
	sta dur_val
	stx pit_val
	sty oct_val

	lda #>5000     ; 2
	sta $b809      ; 4
	lda #<5000     ; 2
	sta $b808      ; 4
loop3:                       ;  
	  jsr toggle         ;22 , t3=t2+25

	  ldy oct_val        ; 3 , t2=Y*(t1+5)+3
loop2:	   ldx pit_val       ; 3 , t1=X*34+3
loop1:	      lda $b809      ; 4
	      cmp #$ff       ; 2
	      beq chk_timer  ; 2
	      jsr wait       ; 6+15
loop5:	      dex            ; 2
	    bne loop1        ; 3
	    dey              ; 2
	  bne loop2          ; 3
	jmp loop3            ; 3

end_sound:
	rts             

;--------------------------------------
; Toggle speaker
;--------------------------------------
toggle:
	lda $b002      ; 4
	eor #4         ; 2
	sta $b002      ; 4
	rts            ; 6

;--------------------------------------
; Check if time is over (21 usec)
;--------------------------------------
chk_timer:
	dec dur_val    ; 3
	beq end_sound  ; 3
settimer:
	lda #>5000     ; 2
	sta $b809      ; 4
	lda #<5000     ; 2
	sta $b808      ; 4
	jmp loop5      ; 3

;--------------------------------------
; Wait routine 21-6=15 usec
;--------------------------------------
wait:
	eor $0         ; 3
	nop            ; 2
	nop            ; 2
	nop            ; 2
	rts            ; 6
