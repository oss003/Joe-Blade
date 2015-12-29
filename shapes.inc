;
; Code equates
;
;
; Start of code
;
;            *= $2100
;

L2100:
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $F8,$F0,$E0,$E0,$E0,$C0,$80,$C0
            .byte $01,$00,$00,$00,$00,$00,$00,$00
            .byte $FF,$FF,$7F,$3F,$3F,$3F,$3F,$3F
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $C0,$E0,$E0,$F0,$F0,$F8,$FC,$F8
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $3F,$1F,$3F,$7F,$FF,$FF,$7F,$3F

;------------------------------------------------
; Perform sound command
;------------------------------------------------

L2140:
;	lda #$11
;	sta L1F58
;
;	lda #$01
;	sta L1F5A
;
;	lda #$00
;	sta L1F5C
;
;	lda #$01
;	sta L1F5E
;L215E:
;	ldx #<L1F58
;	ldy #>L1F58
;	lda #$07
;	jsr LFFF1	; Sound command

	ldx L1FAA
	cpx #$08
	bcc L215F
	lda #2
	ldy #2
	jsr sound
L215F:
	rts

;------------------------------------------------
;            .byte $0F,$0F,$1F,$FF
	.repeat 34+15
	  .byte 0
	.endrep

L2180:
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$03,$07,$0E,$0D,$00,$3F,$00
            .byte $00,$FE,$57,$AB,$55,$0A,$E5,$18
            .byte $00,$00,$00,$80,$80,$80,$80,$80
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $1C,$03,$03,$07,$07,$03,$00,$01
            .byte $0E,$E3,$F8,$FD,$EE,$C0,$2E,$7F
            .byte $00,$C0,$00,$00,$00,$00,$00,$80

;----------------------------------------------
; Set front colour
;----------------------------------------------

L21C0:
	sta L0159

;	lda #$13	; Set logical colour 1
;	jsr LFFEE
;	lda #$01
;	jsr LFFEE
;	ldx #$04
;	lda #$00
;L21D1:
;	jsr LFFEE
;	dex
;	bpl L21D1
	rts
;----------------------------------------------

L21D8:
            .byte $BB,$FB,$BB,$FB
L21DC:
            .byte $FB,$FB,$FF,$FF

            .byte $00,$01,$01,$01,$00,$00,$00,$00
            .byte $05,$84,$DA,$FC,$F8,$78,$00,$00
            .byte $43,$7E,$01,$01,$01,$01,$00,$00
            .byte $60,$E0,$E0,$E0,$E0,$C0,$00,$00
	.byte 0,0,0,0,0,0,0,0
	.byte 0,0,0,0,0,0,0,0
	.byte 0,0,0,0

L2200:
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FE,$FF
            .byte $F0,$E0,$C0,$80,$80,$00,$00,$00
            .byte $07,$03,$01,$00,$00,$00,$00,$00
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $00,$00,$80,$C0,$C0,$E0,$F0,$F0
            .byte $00,$00,$00,$01,$01,$03,$01,$00
            .byte $7F,$7F,$7F,$FF,$FF,$FF,$FF,$FF

;----------------------------------------------
; Draw bar below background tiles
; Check for exits left and right down
;----------------------------------------------

L2240:
	lda #$FF		; Draw line below BG tiles
	ldx #$5F
L2244:
	sta L7620,x
	dex
	bpl L2244
	ldx #$80
L2250:
	sta L7620,x
	inx
	bne L2250

	ldx L1F6A		; Get room nr
	lda L0D00,x		; Check for exit left down
	and #$20
	beq L2273

	ldy #$7			; Open exit left down
	lda #$00
L2262:
	ldx scrval,y
	sta L763F,x
	sta L763F+1,x
	sta L763F+2,x
	sta L763F+3,x
	dey
	cpy #3
	bne L2262
L2273:
	jmp L22C0		; Check for exit right down
;----------------------------------------------

            .byte $00,$00
            .byte $00,$00,$00,$00,$00,$00,$00
;	.byte $FF

L2280:
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$0F,$1D,$3A,$35,$00,$FF,$00
            .byte $00,$F8,$5C,$AE,$56,$2A,$96,$62
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $70,$0F,$0F,$1F,$1F,$0F,$00,$05
            .byte $38,$8F,$E0,$F4,$B8,$00,$B8,$FE
            .byte $00,$00,$00,$00,$00,$00,$00,$00

;----------------------------------------------

;L22C0:
;	ldx L1F6A		; Get room nr
;	lda L0D00,x		; Check for exit right down
;	and #$08
;	beq L22DF
;
;	ldy #$7			; Open exit right down
;	lda #$00
;L22CE:
;	ldx scrval,y
;	sta L76DF,x
;	sta L76DF+1,x
;	sta L76DF+2,x
;	sta L76DF+3,x
;	dey
;	cpy #3
;	bne L22CE
;L22DF:
;	rts

	.byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	.byte 0,0,0,0,0,0,0,0,0,0

;----------------------------------------------

L22E0:
            .byte "EDALB EOJ",$0B,$0B
L22EB:
            .byte "yalp ot erif sserP",$0D,$07
L22FF:
            .byte $0,0,0,0,0,0
L2300:
            .byte $FF,$FF,$FF,$FE,$FE,$FC,$F8,$FC
            .byte $C0,$80,$00,$00,$00,$00,$00,$00
            .byte $0F,$07,$07,$03,$03,$03,$03,$03
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FC,$FE,$FE,$FF,$FF,$FF,$FF,$FF
            .byte $00,$00,$00,$00,$00,$80,$C0,$80
            .byte $01,$01,$03,$07,$07,$07,$07,$03
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF

;------------------------------------------------
; Rotate shapedat
;
; Rotate all shape data 1 position down
;
; 5AE0 5AE5 5AEA 5AEF 5AF4 5AF9 5AFE
; 5B03 5B08 5B0D 5B12 5B17 5B1C 5B21
; 5B26 5B2B 5B30 5B35 5B3A 5B3F 5B44 
;------------------------------------------------

L2340:
	ldx #$00               ; Move first shape to last
L2342:
	lda L5AE0,X            ; First shape
	sta L5B44,X            ; Last shape
	inx
	cpx #$05               ; Move block of 5 bytes
	bne L2342

	ldx #$00               ; Move all shapes 1 down
L234F:
	lda L5AE5,X            ; Shape from
	sta L5AE0,X            ; Shape to
	inx
	cpx #$6E               ; All 22 shapes done?
	bne L234F

	rts

;------------------------------------------------

            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$13,$F0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$FF
L2380:
            .byte $00,$00,$00
            .byte $00,$00,$00,$03,$00,$00,$3F,$75
            .byte $EA,$D5,$00,$FE,$01,$00,$E0,$70
            .byte $B8,$58,$A8,$58,$88,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$01,$00,$00
            .byte $00,$00,$00,$00,$00,$C0,$3E,$3F
            .byte $7F,$7E,$3C,$02,$17,$E0,$3C,$80
            .byte $D0,$E0,$00,$E0,$F8,$00,$00,$00
            .byte $00,$00,$00,$00,$00

;------------------------------------------------
; Check for end of game, then restart
;------------------------------------------------

L23C0:      lda #$7B
            cmp L1F6A		; Current room
            bne L23F0

            lda #$06
            cmp L1F61		; Nr of bombs
            bne L23F0
            cmp L1F62		; Nr of men
            bne L23F0

            ldx L1F28+$1D
            ldy L1F28+$1C
            jsr set_cursor		; Cursor at X,Y

            ldx #$1C		; Print 'Congratulations ... won'
L23DA:      lda L1F28,x
            jsr LFFEE
            dex
            bpl L23DA

            lda #$01
            sta L1F47

L23E8:      jsr L0E00		; Scan keys

            lda L1F03		; Wait for pressing RET key
            beq L23E8

L23F0:      lda #$00
            sta L1FE1
            sta L1FE2
            rts
L23F9:
            .byte $76,$4F
            .byte $00
;	.byte $00,$00,$54,$00
L2400:
            .byte $FF,$FE,$FC
            .byte $F8,$F8,$E0,$E0,$F0,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$7F,$3F,$1F
            .byte $0F,$0F,$0F,$0F,$0F,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$F0,$F8,$F8
            .byte $FC,$FC,$FE,$FF,$FF,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$0F,$0F,$0F
            .byte $1F,$1F,$1F,$0F,$0F,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FE,$10,$00
            .byte $00,$00,$F0,$FC,$FC,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$07,$07,$03
            .byte $03,$03,$07,$0F,$0F,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FC,$FC,$E0
            .byte $E0,$E0,$E0,$F0,$F8,$00,$00,$00
            .byte $0C,$08,$10,$10,$30,$0F,$0F,$0F
            .byte $0F,$1F,$1F,$3F,$7F,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF
L2480:
            .byte $00,$00,$01
            .byte $03,$03,$00,$0F,$00,$00,$FF,$D5
            .byte $AA,$55,$02,$F9,$06,$00,$80,$C0
            .byte $E0,$60,$A0,$60,$20,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$07,$00,$00
            .byte $01,$01,$00,$00,$00,$03,$F8,$FE
            .byte $FF,$FB,$F0,$0D,$5F,$80,$F0,$00
            .byte $40,$80,$00,$C0,$E0,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$47
            .byte $77,$07,$00,$00,$01,$DF,$DE,$00
            .byte $BE,$00,$5E,$4E,$4F,$F0,$F0,$F8
            .byte $38,$F8,$F0,$E0,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$01,$01,$00
            .byte $0D,$0F,$07,$03,$00,$50,$1F,$00
            .byte $E1,$C3,$C7,$87,$00,$E0,$E0,$00
            .byte $E0,$C0,$C0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00

L2500:      .byte $3F,$60,$4E,$D1,$91,$A0,$BF,$80
            .byte $80,$C0,$40,$60,$20,$A0,$A0,$20
L2510:      .byte $BF,$A0,$A0,$A0,$A0,$A0,$A0,$E0
            .byte $A0,$A0,$A0,$A0,$A0,$A0,$A0,$E0
            .byte $FF,$80,$BE,$A1,$A1,$A1,$BE,$80
            .byte $00,$80,$40,$40,$40,$40,$40,$80
            .byte $BE,$A1,$A1,$A1,$A2,$BC,$81,$FF
            .byte $40,$40,$40,$40,$40,$C0,$80,$00
            .byte $3F,$40,$9F,$B0,$A0,$A0,$A0,$A0
            .byte $C0,$20,$90,$D0,$70,$00,$00,$00
            .byte $A0,$A0,$A0,$A0,$B0,$9F,$40,$3F
            .byte $00,$00,$00,$70,$D0,$90,$20,$C0
            .byte $FF,$80,$BF,$A1,$A0,$A0,$A0,$A0
            .byte $80,$40,$20,$90,$D0,$50,$50,$50
            .byte $A0,$A0,$A0,$A0,$A0,$BF,$80,$FF
            .byte $50,$50,$50,$50,$90,$20,$40,$80
L2580:
            .byte $FF,$80,$BF,$A0,$A0,$A0,$BF,$81
            .byte $F0,$10,$F0,$00,$00,$00,$00,$00
            .byte $BF,$A0,$A0,$A0,$A0,$BF,$80,$FF
            .byte $00,$00,$00,$00,$00,$F0,$10,$F0

L25A0:      .byte "SELF DESTRUCT IN    SECONDS"

;---------------------------------------------
; Wipe $6720-$761F
; Atom $8500-$9100
;---------------------------------------------

L25BB:
	lda #$f0               ; CLEAR4
	sta $b000

	lda #<(L6720)            ; Set startaddress
	sta L0078
	lda #>(L6720)
	sta L0079

	ldx #$0D               ; Set nr of blocks to wipe

	ldy #$00               ; Pointer=0
	tya                    ; Data=0
L25C9:
	sta (L0078),Y          ; Wipe screenaddress
	dey
	bne L25C9              ; Block of 256 bytes wiped?

	inc L0079              ; Next block
	dex
	bne L25C9              ; Repeat for nr of blocks

	rts

;--------------------------------------------
; Display Bomb puzzle
;--------------------------------------------

L25D4:
            jsr L25BB              ; Wipe screen

            ldx #$03               ; Move cursor to X,Y
            ldy #$07
            jsr set_cursor

	jsr L25E4		; Print 'SELF DESTRUCT....

            jmp L2663              ; Print letterblocks

;--------------------------------------------

L25F6:      jsr L0E00              ; Keyscan
            jsr L0E28              ; Print countdown timer

            lda L1F01              ; AD 01 1F
            ora L1F02              ; 0D 02 1F
L2600:
            ora L1F03              ; 0D 03 1F
            bne L25F6              ; D0 EF

L2607:      jsr L0E00              ; Keyscan

            jsr L0E28              ; Print countdown timer

            lda L1F01              ; AD 01 1F
            ora L1F02              ; 0D 02 1F
            ora L1F03              ; 0D 03 1F
            beq L2607              ; F0 EF

            lda L1F03              ; AD 03 1F
            beq L264B              ; F0 2E

            ldx L1F05              ; AE 05 1F
            ldy L1F06,X            ; BC 06 1F
            sty L0079              ; 84 79

            ldy L1F0B,X            ; BC 0B 1F
            ldx L0079              ; A6 79
            lda L1F10,X            ; BD 10 1F
            sta L0078              ; 85 78

            lda L1F10,Y            ; B9 10 1F
            sta L1F10,X            ; 9D 10 1F

            lda L0078              ; A5 78
            sta L1F10,Y            ; 99 10 1F

            ldx #$00               ; A2 00
L263C:      lda L1F10,X            ; BD 10 1F
            sta L0078              ; 85 78
            cpx L0078              ; E4 78
            bne L264B              ; D0 06
            inx                    ; E8
            cpx #$05               ; E0 05
            bne L263C              ; D0 F2

            rts                    ; 60

L264B:      lda L1F05              ; AD 05 1F
            clc                    ; 18
            adc L1F02              ; 6D 02 1F
            sec                    ; 38
            sbc L1F01              ; ED 01 1F
            bpl L265A              ; 10 02
            lda #$04               ; A9 04

L265A:      cmp #$05               ; C9 05
            bne L2660              ; D0 02

            lda #$00               ; A9 00
L2660:      sta L1F05              ; 8D 05 1F

; Entry

L2663:      jsr L26AF              ; Print letterblocks

            lda #<L74E0            ; Set letter selector screenaddress
            sta L0078
            lda #>L74E0
            sta L0079

            lda #$00               ; Clear complete line
            ldy #$FF
L2672:      sta (L0078),Y
            dey
            bne L2672

            ldx L1F05              ; Left letter selector
            lda L1F06,X            ; Get X-pos letter selector
            jsr L268C              ; Draw left letter selector

            ldx L1F05              ; Right letter selector
            lda L1F0B,X            ; Get X-pos letter selector
            jsr L268C              ; Draw right letter selector

            jmp L25F6              ; Return

; Draw letter selector

L268C:      tax
            lda #<(L74E0-4)               ; A9 74
            sta L0078              ; 85 78
            lda #>(L74E0-4)               ; A9 74
            sta L0079              ; 85 79

L2695:      lda L0078              ; A5 78
            clc                    ; 18
            adc #$06               ; 69 30
            sta L0078              ; 85 78
            lda L0079              ; A5 79
            adc #$00               ; 69 00
            sta L0079              ; 85 79
            dex                    ; CA
            bpl L2695              ; 10 F0
L26A0:
            ldx #$0f               ; A0 0F
            lda #$FF               ; A9 FF
L26A9:
	ldy scrval,x
	sta (L0078),Y          ; 91 78
            dex                    ; 88
            bpl L26A9              ; 10 FB

            rts                    ; 60

;------------------------------------------------
; Print letterblocks
;------------------------------------------------

L26AF:
	ldx #$00		; Set letter counter
	stx L0077

	lda #<(L7120+2)		; Set screenaddress
	sta L0078
	lda #>(L7120+2)
	sta L0079
L26BB:
	lda L0078		; 78/79 = lettertop
	sta L007A		; 7A/7B = letterbottom
	lda L0079
	sta L007B
	inc L007B

	ldx L0077		; Get letter counter
	lda L1F10,X		; Letterdata offset = 32 x counter + 15
	asl A
	asl A
	asl A
	asl A
	asl A
	clc
	adc #$0F

	tax			; Set letterdata pointer

	ldy #$e1		; Set screen linepointer

L26D8:
	lda L2500,X
	sta (L0078),Y		; Plot letter upper right
	lda L2510,X
	sta (L007A),Y		; Plot letter lower right

 	dey

	lda L2500-8,X
	sta (L0078),Y		; Plot letter upper left
	lda L2510-8,X
	sta (L007A),Y		; Plot letter lower left

	dex
	iny

	tya			; Point 1 line up
	sec
	sbc #$20
	tay
	bcs L26D8

	ldx L0077
	inx			; Next letter
	cpx #$05
	beq L26FC		; Repeat if not 5 letters plot
	stx L0077		; Set counter

	lda L0078		; Point to next letter on screen
	clc
	adc #$6
	sta L0078
	jmp L26BB		; Plot next letter
	
L26FC:
	rts

            .byte $10,$F6,$A9,0
;	.byte 0,0,0,0,0,0,0,0,0
L2700:
            .byte $FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$F8,$90,$00,$80
            .byte $C0,$E0,$C0,$FF,$00,$00,$00,$00
            .byte $00,$00,$00,$FF,$7F,$7F,$7F,$3F
            .byte $3F,$1F,$1F,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$80,$80,$80,$C0,$E0
            .byte $E0,$E0,$F0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$1F,$1F,$1F,$1F,$3F
            .byte $3F,$7F,$7F,$FF,$FF,$FC,$FC,$FC
            .byte $FC,$FF,$FF,$F8,$F8,$60,$00,$00
            .byte $00,$C0,$F0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$3F,$1F,$0F,$0F,$0F
            .byte $0F,$1F,$1F,$FF,$FE,$FC,$FC,$FC
            .byte $FC,$FF,$FF,$F0,$60,$00,$00,$00
            .byte $01,$03,$83,$00,$00,$00,$00,$40
            .byte $FC,$FC,$FC,$1F,$0F,$0F,$0F,$0F
            .byte $0F,$0F,$1F,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$02,$65,$38
            .byte $0F,$00,$09,$00,$00,$FF,$5F,$AB
            .byte $FF,$00,$F5,$00,$00,$00,$00,$80
            .byte $80,$00,$40,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$3C,$3F,$03,$01,$0D
            .byte $0F,$07,$00,$FA,$F7,$FE,$FD,$FA
            .byte $DD,$80,$6E,$80,$40,$80,$40,$80
            .byte $00,$00,$00,$00,$00,$00,$01,$01
            .byte $00,$00,$00,$01,$03,$03,$1C,$DE
            .byte $1C,$01,$01,$DF,$DF,$DB,$03,$F8
            .byte $03,$7B,$3B,$80,$C0,$C0,$E0,$E0
            .byte $E0,$C0,$80,$00,$00,$01,$01,$01
            .byte $00,$00,$00,$05,$05,$9C,$DF,$FC
            .byte $F8,$78,$00,$3C,$43,$7F,$3E,$00
            .byte $01,$01,$00,$40,$E0,$E0,$E0,$E0
            .byte $E0,$C0,$00
L2800:
            .byte $FF,$FC,$FC,$FC,$FE
            .byte $FF,$FF,$FE,$E0,$40,$00,$00,$00
            .byte $80,$00,$00,$03,$01,$00,$00,$00
            .byte $00,$00,$00,$FF,$FF,$FF,$FF,$FF
            .byte $7F,$7F,$7F,$FE,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$00,$00,$00,$80,$80
            .byte $C0,$E0,$E0,$00,$00,$00,$00,$00
            .byte $01,$01,$00,$7F,$7F,$7F,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$F1,$F0,$F0,$F0
            .byte $FF,$FF,$FF,$E0,$80,$00,$00,$00
            .byte $00,$C0,$C0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$7F,$7F,$3F,$3F,$3F
            .byte $3F,$7F,$FF,$FF,$FF,$FE,$FE,$FE
            .byte $FE,$FF,$FF,$C0,$C0,$00,$00,$00
            .byte $01,$01,$83,$01,$01,$00,$00,$81
            .byte $01,$03,$07,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$00,$00,$01,$00,$00
            .byte $00,$00,$00,$00,$0B,$95,$E2,$3F
            .byte $00,$27,$F3,$00,$FC,$7C,$AE,$FE
            .byte $00,$D5,$EA,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$FF,$0F,$07,$37,$3F
            .byte $1E,$01,$07,$DD,$FA,$F5,$EA,$74
            .byte $00,$B8,$7E,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$04,$07,$00
            .byte $00,$00,$00,$0F,$0F,$70,$7B,$70
            .byte $05,$04,$14,$7F,$6F,$0F,$E3,$0F
            .byte $EF,$EE,$F0,$00,$00,$80,$80,$80
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$15,$11,$1E,$DE,$FC
            .byte $7C,$38,$00,$0C,$7C,$7E,$1E,$3C
            .byte $7C,$70,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00
L2900:
            .byte $FF,$F9,$F0,$F0,$FC
            .byte $FE,$FC,$F8,$C0,$00,$00,$00,$00
            .byte $00,$00,$00,$0F,$07,$07,$03,$03
            .byte $03,$01,$01,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$F8,$F8,$FC,$FE,$FE
            .byte $FF,$FF,$FF,$00,$00,$00,$00,$00
            .byte $00,$00,$80,$01,$01,$01,$03,$07
            .byte $0F,$07,$03,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$CE,$C0,$C0,$C0
            .byte $FC,$FF,$FF,$80,$00,$00,$00,$00
            .byte $00,$80,$C0,$01,$01,$00,$00,$00
            .byte $01,$03,$03,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$C0,$C0,$C0,$E0,$C0
            .byte $80,$80,$80,$0F,$1F,$1F,$3F,$3F
            .byte $3F,$3F,$3F,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$00,$00,$06,$03,$00
            .byte $00,$00,$03,$00,$2F,$55,$8A,$FF
            .byte $00,$9F,$CF,$00,$F0,$F0,$B8,$F8
            .byte $00,$54,$A8,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$03,$00,$00,$00,$00
            .byte $00,$00,$00,$FF,$3F,$1F,$DF,$FD
            .byte $78,$06,$1D,$74,$E8,$D4,$A8,$D0
            .byte $00,$E0,$F8,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$11,$1D,$01
            .byte $00,$00,$00,$3D,$3D,$C0,$EF,$C0
            .byte $17,$13,$13,$FC,$BC,$3E,$8E,$3E
            .byte $BC,$B8,$C0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$14,$07,$1F,$0F,$07
            .byte $3F,$3F,$00,$20,$C0,$C0,$80,$80
            .byte $80,$80,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00
L2A00:
            .byte $FE,$C4,$C0,$C0,$E0
            .byte $F8,$F0,$E0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$3F,$1F,$0F,$0F,$0F
            .byte $07,$07,$07,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$E0,$F0,$F0,$F8,$F8
            .byte $FC,$FE,$FE,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$07,$07,$07,$0F,$0F
            .byte $1F,$1F,$0F,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FE,$18,$00,$00,$00
            .byte $F0,$FC,$FC,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$07,$07,$03,$03,$03
            .byte $03,$07,$0F,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FC,$FC,$E0,$E0,$E0
            .byte $E0,$F0,$F8,$00,$00,$00,$00,$08
            .byte $10,$10,$30,$1F,$1F,$0F,$0F,$1F
            .byte $1F,$3F,$7F,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$00,$00,$19,$0E,$03
            .byte $00,$02,$0F,$00,$BF,$57,$2A,$FF
            .byte $00,$7D,$3E,$00,$C0,$C0,$E0,$E0
            .byte $00,$50,$A0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$0F,$00,$00,$03,$03
            .byte $01,$00,$00,$FD,$FF,$7F,$7E,$F7
            .byte $E0,$1B,$77,$D0,$A0,$50,$A0,$40
            .byte $00,$80,$E0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$47,$77,$07
            .byte $00,$00,$01,$F7,$F6,$00,$BE,$00
            .byte $5E,$4E,$4F,$F0,$F0,$F8,$38,$F8
            .byte $F0,$E0,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$01,$01,$01,$0D,$0F
            .byte $07,$03,$00,$50,$17,$E7,$E1,$C3
            .byte $C7,$87,$00,$C0,$C0,$E0,$E0,$C0
            .byte $C0,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00
L2B00:
            .byte $FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FC,$88,$80,$C0,$E0
            .byte $F0,$E0,$C0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$7F,$3F,$3F,$1F,$1F
            .byte $0F,$0F,$0F,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$C0,$E0,$E0,$F0,$F0
            .byte $F8,$FC,$FE,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$0F,$0F,$0F,$1F,$3F
            .byte $7F,$3F,$1F,$FF,$FE,$FE,$FE,$FE
            .byte $FF,$FF,$FF,$FC,$60,$00,$00,$00
            .byte $F0,$F0,$E0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$0F,$0F,$07,$07,$07
            .byte $0F,$1F,$03,$FE,$FC,$FC,$FC,$FC
            .byte $FE,$FF,$FF,$60,$00,$00,$00,$00
            .byte $03,$07,$FF,$00,$00,$00,$20,$E0
            .byte $F8,$FF,$FF,$01,$00,$00,$00,$00
            .byte $00,$C1,$E1,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$01,$32,$1C,$07
            .byte $00,$04,$1E,$00,$7F,$AF,$55,$FF
            .byte $00,$FA,$7D,$00,$80,$80,$C0,$C0
            .byte $00,$A0,$40,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$1F,$01,$00,$06,$07
            .byte $03,$00,$00,$FB,$FF,$FE,$FD,$EE
            .byte $C0,$37,$EF,$A0,$40,$A0,$40,$80
            .byte $00,$00,$C0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$01,$01,$8E,$EF,$0E
            .byte $00,$06,$0E,$EF,$ED,$01,$7C,$01
            .byte $BD,$9D,$9E,$E0,$E0,$F0,$70,$F0
            .byte $E0,$C0,$00,$00,$01,$01,$01,$00
            .byte $00,$00,$00,$0E,$9E,$DF,$FE,$F8
            .byte $78,$00,$00,$A0,$3F,$9F,$0F,$07
            .byte $00,$00,$00,$EC,$DE,$BE,$F6,$CE
            .byte $1E,$1C,$00
L2C00:
            .byte $FF,$FE,$FE,$FF,$FF
            .byte $FF,$FF,$FF,$F0,$20,$00,$00,$80
            .byte $C0,$80,$00,$01,$00,$00,$00,$00
            .byte $00,$00,$00,$FF,$FF,$FF,$7F,$7F
            .byte $3F,$3F,$3F,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$00,$80,$80,$C0,$C0
            .byte $E0,$F0,$F8,$00,$00,$00,$00,$00
            .byte $01,$00,$00,$3F,$3F,$3F,$7F,$FF
            .byte $FF,$FF,$7F,$FF,$F9,$F8,$F8,$F8
            .byte $FF,$FF,$FF,$F0,$80,$00,$00,$00
            .byte $C0,$C0,$80,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$3F,$3F,$1F,$1F,$1F
            .byte $3F,$7F,$0F,$F9,$F0,$F0,$F0,$F0
            .byte $F8,$FC,$FF,$80,$00,$00,$00,$03
            .byte $0F,$1F,$FF,$00,$00,$00,$80,$80
            .byte $E0,$FF,$FF,$07,$03,$03,$03,$03
            .byte $03,$07,$87,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$05,$CA,$71,$1F
            .byte $00,$13,$79,$00,$FE,$BE,$57,$FF
            .byte $00,$EA,$F5,$00,$00,$00,$00,$00
            .byte $00,$80,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$7F,$07,$03,$1B,$1F
            .byte $0F,$00,$03,$EE,$FD,$FA,$F5,$BA
            .byte $00,$DC,$BF,$80,$00,$80,$00,$00
            .byte $00,$00,$00,$00,$00,$02,$03,$00
            .byte $00,$00,$00,$07,$07,$38,$BD,$38
            .byte $02,$1A,$3A,$BF,$B7,$07,$F1,$07
            .byte $F7,$77,$78,$80,$80,$C0,$C0,$C0
            .byte $80,$00,$00,$00,$06,$07,$07,$03
            .byte $01,$00,$00,$3A,$78,$7E,$F8,$E0
            .byte $E0,$00,$00,$83,$FF,$7E,$3F,$1F
            .byte $00,$00,$00,$B0,$78,$F8,$D8,$38
            .byte $78,$70,$00
L2D00:
            .byte $FF,$F8,$F8,$FC,$FE
            .byte $FF,$FE,$FC,$C0,$80,$00,$00,$00
            .byte $00,$00,$00,$07,$03,$03,$01,$01
            .byte $00,$00,$00,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FC,$FE,$FE,$FF,$FF
            .byte $FF,$FF,$FF,$00,$00,$00,$00,$00
            .byte $80,$C0,$E0,$00,$00,$00,$01,$03
            .byte $07,$03,$01,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$E6,$E0,$E0,$E0
            .byte $FF,$FF,$FE,$C0,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$01,$00,$FF,$FF,$7F,$7F,$7F
            .byte $FF,$FF,$3F,$E6,$C0,$C0,$C0,$C0
            .byte $E0,$F0,$FF,$00,$00,$00,$02,$0E
            .byte $3F,$7F,$FF,$00,$00,$00,$00,$00
            .byte $80,$FC,$FE,$1F,$0F,$0F,$0F,$0F
            .byte $0F,$1F,$1F,$00,$00,$03,$01,$00
            .byte $00,$00,$01,$00,$17,$2A,$C5,$7F
            .byte $00,$4F,$E7,$00,$F8,$B8,$5C,$FC
            .byte $00,$AA,$D4,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$01,$00,$00,$00,$00
            .byte $00,$00,$00,$FF,$1F,$0F,$6F,$7E
            .byte $3C,$03,$0E,$BA,$F4,$EA,$D4,$E8
            .byte $00,$70,$FC,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$08,$0E,$00
            .byte $00,$00,$00,$1E,$1E,$E0,$F7,$E0
            .byte $0B,$69,$E9,$FE,$DE,$1F,$C7,$1F
            .byte $DE,$DC,$E0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$19,$1D,$1F,$0F
            .byte $07,$00,$00,$EA,$E3,$F9,$E0,$80
            .byte $80,$00,$00,$0E,$FD,$FB,$FF,$7C
            .byte $01,$01,$00,$C0,$E0,$E0,$60,$E0
            .byte $E0,$C0,$00
L2E00:
            .byte $FF,$E2,$E0,$F0,$F8
            .byte $FC,$F8,$F0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$1F,$0F,$0F,$07,$07
            .byte $03,$03,$03,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$F0,$F8,$F8,$FC,$FC
            .byte $FE,$FF,$FF,$00,$00,$00,$00,$00
            .byte $00,$00,$80,$03,$03,$03,$07,$0F
            .byte $1F,$0F,$07,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$98,$80,$80,$80
            .byte $FC,$FC,$F8,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$03,$03,$01,$01,$01
            .byte $03,$07,$00,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$98,$00,$00,$00,$00
            .byte $80,$C1,$FF,$00,$00,$00,$08,$38
            .byte $FE,$FF,$FF,$00,$00,$00,$00,$00
            .byte $00,$F0,$F8,$7F,$3F,$3F,$3F,$3F
            .byte $3F,$7F,$7F,$00,$00,$0C,$07,$01
            .byte $00,$01,$07,$00,$5F,$AB,$15,$FF
            .byte $00,$3E,$9F,$00,$E0,$E0,$70,$F0
            .byte $00,$A8,$50,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$07,$00,$00,$01,$01
            .byte $00,$00,$00,$FE,$7F,$3F,$BF,$FB
            .byte $F0,$0D,$3B,$E8,$D0,$A8,$50,$A0
            .byte $00,$C0,$F0,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$23,$3B,$03
            .byte $00,$01,$03,$7B,$7B,$80,$DF,$80
            .byte $2F,$A7,$A7,$F8,$78,$7C,$1C,$7C
            .byte $78,$70,$80,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$03,$67,$77,$7F,$3E
            .byte $1E,$00,$00,$A8,$8F,$E7,$83,$01
            .byte $00,$00,$00,$3B,$F7,$EF,$FD,$F3
            .byte $07,$07,$00,$00,$80,$80,$80,$80
            .byte $80,$00,$00
L22C0:
	ldx L1F6A		; Get room nr
	lda L0D00,x		; Check for exit right down
	and #$08
	beq L22DF

	ldy #$7			; Open exit right down
	lda #$00
L22CE:
	ldx scrval,y
	sta L76DF,x
	sta L76DF+1,x
	sta L76DF+2,x
	sta L76DF+3,x
	dey
	cpy #3
	bne L22CE
L22DF:
	rts

; Print SELF DESTR ......

L25E4:
            ldx #$00               ; Print 'SELF DESTRUCT ....
L25E8:      lda L25A0,X
            jsr LFFEE              ; Print char
            inx
            cpx #$1B
            bne L25E8
	rts