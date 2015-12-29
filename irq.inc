;--------------------------------------------
; INITIRQ
;
; Initialize IRQ vector + timer
; 100 Hz = 1.000.000 / 100 = 10.000 usec
;--------------------------------------------

irqtime	= 10000

initIRQ:
	sei

	lda #>irqvec		; Set IRQ vec
	sta $205
	lda #<irqvec
	sta $204

	lda #<(irqtime)		; Set IRQ timer
	sta $b804
	lda #>(irqtime)
	sta $b805

	lda $b80b		; Continuous IRQ on T1
	and #$7f
	ora #$40
	sta $b80b

	lda #$c0		; Enable T1-IRQ
	sta $b80e

	cli
	rts

irqvec:
	lda $b804		; Clear IRQ flag
	txa
	pha
	tya
	pha

	inc L0292		; Increment time
	bne end_irq
	inc L0292+1
	bne end_irq
	inc L0292+2
	bne end_irq
	inc L0292+3
	bne end_irq
	inc L0292+4
	bne end_irq
end_irq:
	pla
	tay
	pla
	tax
	pla
	rti

gettime:
	sei
	lda L0292
	sta L1F6F
	lda L0292+1
	sta L1F6F+1
	lda L0292+2
	sta L1F6F+2
	lda L0292+3
	sta L1F6F+3
	lda L0292+4
	sta L1F6F+4
	cli
	rts

settime:
	sei
	lda L1F6F
	sta L0292
	lda L1F6F+1
	sta L0292+1
	lda L1F6F+2
	sta L0292+2
	lda L1F6F+3
	sta L0292+3
	lda L1F6F+4
	sta L0292+4
	cli
	rts
