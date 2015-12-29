;
; Code equates
;

L0070       = $0070
L0071       = $0071
L0072       = $0072
L0073       = $0073
L0074       = $0074
L0075       = $0075
L0076       = $0076
L0077       = $0077
L0078       = $0078
L0079       = $0079
L007A       = $007A
L007B       = $007B
L007C       = $007C
L007D       = $007D
L007E       = $007E
L007F       = $007F
L0080       = $0080
L0081       = $0081
L0082       = $0082
L0083       = $0083
L0084       = $0084
L0085       = $0085
L0086       = $0086
L0087       = $0087
L0088       = $0088
L0089       = $0089
L008A       = $008A
L008B       = $008B
L008C       = $008C
L008D       = $008D
L008E       = $008E
L008F       = $008F
L0090       = $0090
L0091       = $0091
L0092       = $0092
L0093       = $0093
L0094       = $0094
L0095       = $0095
L0096       = $0096
L0097       = $0097
L0098       = $0098
L009A       = $009A
L009C       = $009C
L009E       = $009E

L0292       = $0CFB	; System IRQ time
L0293       = $0CFC
L0294       = $0CFD
L0295       = $0CFE
L0296       = $0CFF

L6720       = $8500	; Start of background tiles

L6900       = $8714	; Position countdown timer
L6908       = $8715

L6C20       = $8900	; Start of screen buffering
L6D60       = $8A00
L6EA0       = $8B00
L6FE0       = $8C00
L7120       = $8D00
L7260       = $8E00
L73A0       = $8F00
L74E0       = $9000

L7620       = $9100	; Line below background tiles

L763F       = $9104	; Pos door left
L76DF       = $9118	; Pos door right

score	= $9408
bombs	= $941D
men	= $951D
keys	= $961D

;LFFEE       = $FFF4
LFFF1       = $F0AD
;LFFF4       = $FFF4

;
; Start of code
;
;            *= $0E00
;

;--------------------------------------------
; Keyscan 
;--------------------------------------------
; Store 1 in L1F00,x if key pressed
;
; Input:
;  -
;
; Output:
;  L1F00 = 0/1 up
;  L1F01 = 0/1 left
;  L1F02 = 0/1 right
;  L1F03 = 0/1 fire
;  L1F04 = 0/1 down
;--------------------------------------------

L0E00:
	ldx #4		; Nr of keys
	stx L0078
L0E04:
	ldx L0078
	lda #0
	sta L1F00,x	; Reset key var

	lda L1F15	; Check joystick
	beq L0E17

	jsr joyget	; Scan joystick
	and L0E24,x
	beq L0E18
	jmp L0E19
L0E17:
	lda L0E23,X
	jsr keyscan
	bcs L0E18	; Check key
L0E19:
	ldx L0078
	inc L1F00,X
L0E18:
	dec L0078
	bpl L0E04	; Repeat for all keys
	rts	

;            keys  :   Z   X  RET  .
L0E23:      .byte $1B,$3A,$38,$0D,$1E	; Keyboard
L0E24:      .byte $08,$02,$01,$10,$04	; Joystick

;--------------------------------------------
; Countdown timer when solving bomb puzzle
;--------------------------------------------

L0E28:
	jsr gettime

            lda #$02               ; A9 02
            sta L1F71              ; 8D 71 1F

            lda L1F70              ; AD 70 1F
            cmp #$1E               ; C9 1E
            beq L0E80              ; F0 43

            cmp #$0A               ; C9 0A
            bcc L0E4D              ; 90 0C
L0E41:      dec L1F71              ; CE 71 1F
            sec                    ; 38
            sbc #$0A               ; E9 0A
            cmp #$0A               ; C9 0A
            bcc L0E4D              ; 90 02
            bcs L0E41              ; B0 F4

L0E4D:      sta L1F70              ; 8D 70 1F
            lda L1F71              ; AD 71 1F
	ldx #>L6900
	ldy #<L6900
	jsr L1D95

            lda #$09               ; A9 09
            sec                    ; 38
            sbc L1F70              ; ED 70 1F
	ldx #>L6908
	ldy #<L6908
	jsr L1D95

            rts                    ; 60

L0E80:      pla                    ; 68
            pla                    ; 68

            lda #$01               ; A9 01
            sta L1FAE              ; Killed flag

            rts                    ; 60

;--------------------------------------------
; Plot Joe Blade sprite
;--------------------------------------------
;
; - Load screenbyte
; - AND Joe maskbyte
; - ORA Joe spritebyte
; - Store screenbyte
; 
; Input:
;  86/87 = screenaddress top row
;  88/89 = screenaddress first row
;  8A/8B = screenaddress second row
;  8C/8D = screenaddress third row
;  8E/8F = screenaddress fourth row
;
;  L59A0 = Mask top row
;  L59C0 = Mask 2nd row
;  L59E0 = Mask 3rd row
;  L5A00 = Mask 4th row
;  L5A20 = Mask 5th row
;
;  L5A40 = Data top row
;  L5A60 = Data 2nd row
;  L5A80 = Data 3rd row
;  L5AA0 = Data 4th row
;  L5AC0 = Data 5th row
;
; Output:
;  -
;--------------------------------------------

L0E88:
        ldx #$1F               ; Byte counter
L0E8A:
	ldy scrval,x           ; Get screen offset

	lda (L0086),Y          ; Screen top row
	and L59A0,X            ; Joe mask
	ora L5A40,X            ; Joe data
	sta (L0086),Y          ; Screen

	lda (L0088),Y          ; Screen second row
 	and L59C0,X            ; Joe mask
	ora L5A60,X            ; Joe data
	sta (L0088),Y          ; Screen

	lda (L008A),Y          ; Screen third row
	and L59E0,X            ; Joe mask
	ora L5A80,X            ; Joe data
	sta (L008A),Y          ; Screen

	lda (L008C),Y          ; Screen fourth row
	and L5A00,X            ; Joe mask
	ora L5AA0,X            ; Joe data
	sta (L008C),Y          ; Screen

	lda (L008E),Y          ; Screen fifth row
	and L5A20,X            ; Joe mask
	ora L5AC0,X            ; Joe data
	sta (L008E),Y          ; Screen

	dex
	bpl L0E8A              ; Next byte
	rts

;--------------------------------------------
; Plot enemies
;--------------------------------------------
;
; Check and plot guards if enabled
;--------------------------------------------

L0EC0:

; Set pointers
;  7C/7D = mask Joe head
;  7E/7F = data Joe head

            ldy L1F6C              ; Delay guard1
            lda L1FF2,Y            ; Get lb shapetable
            sta L007C              ; 7C/7D = mask Joe head
            clc
            adc #$80
            sta L007E              ; 7E/7F = data Joe head
            lda L1FE4,Y            ; Get hb shapetable
            sta L007D
            adc #$00
            sta L007F

; Copy head mask/data Joe to Joe sprite

            ldy #$3F
L0ED8:      lda (L007C),Y          ; Copy Joe head mask to Joe sprite
            sta L59A0,Y
            lda (L007E),Y          ; Copy Joe head data to Joe sprite
            sta L5A20,Y
            dey
            bpl L0ED8

; Set pointers
;  7C/7D = mask Joe head + $600
;  7E/7F = data Joe head + $600

            lda L007D              ; 7C/7D = mask Joe head + $600
            clc
            adc #$06
            sta L007D
            lda L007F              ; 7E/7F = data Joe head + $600
            clc
            adc #$06
            sta L007F

; Copy body mask/data Joe to Joe sprite

            ldy #$40
L0EF5:      lda (L007C),Y          ; Copy Joe body mask to Joe sprite
            sta L59A0,Y 
            lda (L007E),Y          ; Copy Joe body data to Joe sprite
            sta L5A20,Y
            iny
            bpl L0EF5

; Check plotting guard1

            lda L1F75              ; Direction guard2, 0=left, 1=right
            bne L0F0A              ; If right, jump
            jsr L0F64              ; If left, 

L0F0A:      lda L1F6D              ; Direction guard1, 0=left, 1=right
            beq L0F12              ; If left, jump
            jsr L1478              ; If right, mirror sprite

L0F12:      lda L1F68              ; Check guard1 flag
            beq L0F57              ; If zero, skip guard1

            lda L1FE1              ; Death flicker flag guard 1
            beq L0F2A              ; Plot guard1

            dec L1FE1              ; Death flicker flag guard 1
            bne L0F26              ; D0 05

            ldx #$00
            stx L1F68              ; Reset guard1 flag

L0F26:      and #$01               ; 29 01
            bne L0F57              ; Skip guard1


; Plot guard1
;  90/91 = screenaddress top row
;  92/93 = screenaddress first row
;  94/95 = screenaddress second row
;  96/97 = screenaddress third row

L0F2A:
            ldx #$1F               ; Set byte counter
L0F2C:
	ldy scrval,x		; Set screen offset

            lda (L0090),Y          ; First row
            and L59A0,X
            ora L5A20,X
            sta (L0090),Y

            lda (L0092),Y          ; Second row
            and L59C0,X
            ora L5A40,X
            sta (L0092),Y

            lda (L0094),Y          ; Third row
            and L59E0,X
            ora L5A60,X
            sta (L0094),Y

            lda (L0096),Y          ; Fourth row
            and L5A00,X
            ora L5A80,X
            sta (L0096),Y

            dex
            bpl L0F2C              ; Next byte

; Check plotting guard2

L0F57:      lda L1F75              ; Direction guard2, 0=left, 1=right
            beq L0FA9              ; If left, skip guard2

            lda L1F6D              ; Direction guard1, 0=left, 1=right
            bne L0F64              ; If right, jump
            jsr L1478              ; Mirror sprite

L0F64:      lda L1F69              ; Guard2 flag
            beq L0FA9              ; If zero, skip guard2

            lda L1FE2              ; Death flicker flag guard 2
            beq L0F7C              ; F0 0E

            dec L1FE2              ; Death flicker flag guard 2
            bne L0F78              ; D0 05

            ldx #$00
            stx L1F69              ; Reset guard2 flag
L0F78:
            and #$01               ; 29 01
            bne L0FA9              ; Skip guard2

; Plot guard1
;  98/99 = screenaddress top row
;  9A/9B = screenaddress first row
;  9C/9D = screenaddress second row
;  9E/9F = screenaddress third row

L0F7C:
            ldx #$1F               ; Set byte counter
L0F7E:
	ldy scrval,x		; Set screen offset

            lda (L0098),Y          ; First row
            and L59A0,X
            ora L5A20,X
            sta (L0098),Y

            lda (L009A),Y          ; Second row
            and L59C0,X
            ora L5A40,X
            sta (L009A),Y

            lda (L009C),Y          ; Third row
            and L59E0,X
            ora L5A60,X
            sta (L009C),Y

            lda (L009E),Y          ; Forth row
            and L5A00,X
            ora L5A80,X
            sta (L009E),Y

            dex
            bpl L0F7E              ; Next byte

L0FA9:      rts

;--------------------------------------------
; Wipe sprite mask + data
;--------------------------------------------
;
;--------------------------------------------

; Reset sprite mask ($ff) + data ($00)
; L59A0-L5A3F = $ff (Mask sprite)
; L5A40-L5ADF = $00 (Data sprite)

L0FAA:      ldx #$9F               ; Byte counter
            lda #$FF               ; Reset mask value
            ldy #$00               ; Reset data value

L0FB0:      sta L59A0,X            ; Reset sprite mask
            tya
            sta L5A40,X            ; Reset sprite data
            lda #$FF
            dex
            bne L0FB0
            sta L59A0
            sty L5A40

; Set counters to $04

            lda #$04               ; A9 04
            sta L0076              ; 85 76
            sta L0078              ; 85 78

; Point 7C/7D to shape mask

            ldy L1F1C              ; Stand=8 walk=6 jump=$A
            lda L1FF2,Y            ; Get lb shapetable
            sta L007C
            lda L1FE4,Y            ; Get hb shapetable
            sta L007D

            lda L1F19              ; Decrement strength flag
            bne L0FF0              ; If not zero, jump

            lda L1FAA              ; Jump up counter
            bne L0FE5              ; Joe is jumping

            lda #$06
            sta L0080              ; Set offset pointer
            bne L0FE9              ; Forced jump

L0FE5:      lda #$0A
            sta L0080              ; Set offset pointer

L0FE9:      lda L007D              ; 7C/7D - offset*256
            sec
            sbc L0080
            sta L007D

; Set 72/73 = L59A0 (Mask Joe)

L0FF0:      lda #<L59A0            ; Sprite mask
            sta L0072
            lda #>L59A0
            sta L0073

L0FF8:      ldx L1FAA              ; Jump up counter
            beq L1003              ; Joe on floor?

            lda L1F78,X            ; Get Joe jumping table
            and #$07               ; 29 07
            tax                    ; AA

; Point 7E/7F to shape data

L1003:      lda L007C
            clc
            adc #$80
            sta L007E
            lda L007D
            adc #$00
            sta L007F

; Set 74/75 = L5A40 (Data Joe)

            lda L0072
            clc
            adc #$A0
            sta L0074
            lda L0073
            adc #$00
            sta L0075

; Copy right shape into sprite
;
;  7C/7D = shape mask
;  7E/7F = shape data
;  74/75 = L5A40 (Data Joe)
;  72/73 = L59A0 (Mask Joe)

            ldy #$00               ; A0 00
L101F:      lda (L007C),Y          ; B1 7C
            pha                    ; 48
            lda (L007E),Y          ; B1 7E
            sty L0079              ; 84 79
            stx L007A              ; 86 7A

            ldy L007A              ; A4 7A
            sta (L0074),Y          ; 91 74
            pla                    ; 68
            sta (L0072),Y          ; 91 72

            ldy L0079              ; A4 79
            inx                    ; E8
            cpx #$08               ; E0 08
            beq L1092              ; F0 5C

L1036:      iny                    ; C8
            cpy #$08               ; C0 08
            bne L101F              ; D0 E4

;

            lda L1F19              ; Decrement strength flag
            bne L104D              ; D0 0D

            lda L0076              ; A5 76
            cmp #$03               ; C9 03
            bne L104D              ; D0 07

            lda L007D              ; A5 7D
            clc                    ; 18
            adc L0080              ; 65 80
            sta L007D              ; 85 7D

L104D:      dec L0076              ; C6 76
            beq L1061              ; F0 10

            lda #$20               ; A9 20
            clc                    ; 18
            adc L007C              ; 65 7C
            sta L007C              ; 85 7C
            lda #$00               ; A9 00
            adc L007D              ; 65 7D
            sta L007D              ; 85 7D

            jmp L1003              ; 4C 03 10

L1061:      lda L1F19              ; Decrement strength flag
            bne L106D              ; D0 07

            lda L007D              ; A5 7D
            sec                    ; 38
            sbc L0080              ; E5 80
            sta L007D              ; 85 7D

L106D:      dec L0078              ; C6 78
            beq L10B1              ; F0 40

            lda #$04               ; A9 04
            sta L0076              ; 85 76

;

            lda L0072              ; A5 72
            sec                    ; 38
            sbc #$78               ; E9 78
            sta L0072              ; 85 72
            lda L0073              ; A5 73
            sbc #$00               ; E9 00
            sta L0073              ; 85 73

            sec                    ; 38
            lda L007C              ; A5 7C
            sbc #$58               ; E9 58
            sta L007C              ; 85 7C
            lda L007D              ; A5 7D
            sbc #$00               ; E9 00
            sta L007D              ; 85 7D

            jmp L0FF8              ; 4C F8 0F

;--------------------------------------------
; 72/73 -> +$20 (Mask)
; 74/75 -> +$20 (Data=Mask+$80)
;--------------------------------------------

L1092:      ldx #$00               ; A2 00
            lda L0072              ; A5 72
            clc                    ; 18
            adc #$20               ; 69 20
            sta L0072              ; 85 72
            lda L0073              ; A5 73
            adc #$00               ; 69 00
            sta L0073              ; 85 73

            lda L0072              ; A5 72
            clc                    ; 18
            adc #$A0               ; 69 A0
            sta L0074              ; 85 74
            lda L0073              ; A5 73
            adc #$00               ; 69 00
            sta L0075              ; 85 75
            jmp L1036              ; 4C 36 10

;--------------------------------------------
; Check direction Joe and plot sprite
;--------------------------------------------

L10B1:
            lda L1F6B              ; Direction Joe, 0=left, 1=right
            beq L10B9              ; If left, jump
            jsr L1478              ; Mirror sprite

L10B9:
            jsr L0E88              ; Plot Joe Blade
            rts

;--------------------------------------------
; Check guard hitting borders of screen
;--------------------------------------------
; Input:
;  X=0 -> guard1
;  X=8 -> guard2
;--------------------------------------------

L10BD:      ldy L1F6D,X            ; Direction guard1, 0=left, 1=right
            beq L10EE              ; If left, jump

; Check guard hitting right side of screen

            ldy L1F6C,X            ; Delay guard
            iny
            cpy #$04
            beq L10CF              ; If 4 cycles, jump

            tya                    ; Update delay counter
            sta L1F6C,X            ; Delay guard
            rts

L10CF:      inc L1F6E,X            ; Move guard 1 byte to right

            ldy L1F6E,X            ; Get X-pos guard
            lda #$00
            cpy #$1E               ; Check right screen border
            bne L10E8              ; If not reached, jump

            sta L1F6D,X            ; Set direction guard=left
            sta L1F6C,X            ; Reset delay guard

            dec L1F6E,X            ; Move guard 1 byte to left
            sta L1F6C,X            ; Reset delay guard

            rts

L10E8:      sta L1F6C,X            ; Set delay guard
            jmp L175A              ; Update pointers

; Check guard hitting left side of screen

L10EE:      ldy L1F6C,X            ; Delay guard
            iny                    ; C8
            cpy #$04               ; C0 04
            beq L10FB              ; F0 05
            tya                    ; 98
            sta L1F6C,X            ; Delay guard
            rts                    ; 60

L10FB:      dec L1F6E,X            ; X-pos guard1
            bne L110E              ; D0 0E
            lda #$01               ; A9 01
            sta L1F6D,X            ; Direction guard1, 0=left, 1=right
            lda #$00               ; A9 00
            sta L1F6C,X            ; Delay guard
            inc L1F6E,X            ; X-pos guard1
            rts                    ; 60

L110E:      lda #$00               ; A9 00
            sta L1F6C,X            ; Delay guard
            jmp L175A              ; Update pointers

; Keyscan up/jump

L1116:      jsr L0E00              ; Keyscan
            lda L1FE3              ; Check flag going room up
            beq L112F              ; If flag set, skip keyscan
            lda L1F00              ; Key : - up/jump
            beq L112A

            lda #$00
            sta L1F00              ; Reset Key : - up/jump
            beq L112F              ; Forced jump

L112A:      lda #$00
            sta L1FE3              ; Reset flag going room up

L112F:      lda L1FAA              ; Jump up counter
            beq L1137              ; Joe on floor?
            jmp L11F1              ; 4C F1 11

; Check exit left up/down

L1137:      ldx L1F77              ; X-pos Joe
            cpx #$05               ; Check exit left up/down
            bne L1194

; Check exit left up

            ldx L1F6A              ; Current room number
            lda L0D00,X            ; Room data
            and #$10               ; Check exit left up
            beq L1179
            lda L1F00              ; Check Key : - up/jump
            beq L1179

            lda L0D80,X            ; Room data
            ldx L1F65              ; Nr of keys
            and #$20               ; Check if key needed
            beq L115D
            dex                    ; Decr nr of keys
            bpl L115D              ; If more than 1 key, jump
            jmp L11F1

L115D:      stx L1F65              ; Nr of keys
            txa 
            ldx #>keys             ; Set keys position in panel
            ldy #<keys
            jsr L1D95              ; Print number A at address X,Y

            lda L1F6A              ; Current room number
            clc
            adc #$08               ; Point to room up
            sta L1F6A              ; Current room number

            lda #$01
            sta L1FE3              ; Set flag going room up
            jmp L15C2              ; Continue

; Check exit left down

L1179:      ldx L1F6A              ; Current room number
            lda L0D00,X            ; Room data
            and #$20               ; Check exit left down
            beq L1194
            lda L1F04              ; Check Key / - down
            beq L1194

            lda L1F6A              ; Current room number
            sec
            sbc #$08               ; Point to room down
            sta L1F6A              ; Current room number
            jmp L15C2              ; Continue

; Check exit right up/down

L1194:      ldx L1F77              ; X-pos Joe
            cpx #$19               ; Check exit right up/down
            bne L11F1

; Check exit right up

            ldx L1F6A              ; Current room number
            lda L0D00,X            ; Room data
            and #$04               ; Check exit right up
            beq L11D6
            lda L1F00              ; Check Key : - up/jump
            beq L11D6

            lda L0D80,X            ; Room data
            ldx L1F65              ; Nr of keys
            and #$20               ; Check if key needed
            beq L11BA
            dex                    ; Decr nr of keys
            bpl L11BA              ; If more than 1 key, jump
            jmp L11F1

L11BA:      stx L1F65              ; Nr of keys
            txa
            ldx #>keys             ; Set keys position in panel
            ldy #<keys
            jsr L1D95              ; Print number A at address X,Y

            lda L1F6A              ; Current room number
            clc
            adc #$08               ; Point to room up
            sta L1F6A              ; Current room number

            lda #$01
            sta L1FE3              ; Set flag going room up
            jmp L15C2              ; Continue

; Check exit right down

L11D6:      ldx L1F6A              ; Current room number
            lda L0D00,X            ; Room data
            and #$08               ; Check exit right down
            beq L11F1
            lda L1F04              ; Check Key / - down
            beq L11F1

            lda L1F6A              ; Current room number
            sec
            sbc #$08               ; Point to room down
            sta L1F6A              ; Current room number
            jmp L15C2              ; Continu

L11F1:      lda L1FAA              ; Jump up counter
            bne L11F9              ; Joe jumping?
            jmp L1325              ; 4C 25 13

;--------------

L11F9:      dec L1FAA              ; Joe jumping down

	jsr L2140              ; Perform sound jumping

            ldx L1FAA              ; Jump up counter
            bne L1220              ; Joe jumping?

            lda L1FAD              ; AD AD 1F
            sta L1F1C              ; Stand=8 walk=6 jump=$A
            ldy L1FAB              ; AC AB 1F
            beq L1215              ; F0 09
            dec L1F1C              ; Stand=8 walk=6 jump=$A
            dec L1F1C              ; Stand=8 walk=6 jump=$A
            jmp L1220              ; 4C 20 12

L1215:      ldy L1FAC              ; AC AC 1F
            beq L1220              ; F0 06

            dec L1F1C              ; Stand=8 walk=6 jump=$A
            dec L1F1C              ; Stand=8 walk=6 jump=$A

L1220:      lda L1F78,X            ; Joe jumping table
            tax                    ; AA
            and #$08               ; 29 08
            cmp #$08               ; C9 08
            bne L1237              ; D0 0D

            lda L0086              ; A5 86
            clc                    ; 18
            adc #$40               ; 69 40
            sta L0086              ; 85 86
            lda L0087              ; A5 87
            adc #$01               ; 69 01
            sta L0087              ; 85 87

L1237:      txa                    ; 8A
            and #$10               ; 29 10
            cmp #$10               ; C9 10
            bne L124B              ; D0 0D

            sec                    ; 38
            lda L0086              ; A5 86
            sbc #$40               ; E9 40
            sta L0086              ; 85 86
            lda L0087              ; A5 87
            sbc #$01               ; E9 01
            sta L0087              ; 85 87

L124B:      ldx L1FAA              ; Jump up counter
            lda L1F78,X            ; Get jumpbyte from table
            and #$20               ; 29 20
            bne L1258              ; D0 03
            jmp L1321              ; 4C 21 13

L1258:      lda L1FAB              ; AD AB 1F
            beq L12BD              ; F0 60

            inc L1F1C              ; Stand=8 walk=6 jump=$A
            inc L1F1C              ; Stand=8 walk=6 jump=$A

            lda L1F1C              ; Stand=8 walk=6 jump=$A
            cmp #$0E               ; Check if Joe was jumping
            bne L12BD              ; D0 53

; Joe is jumping

            inc L1F77              ; X-pos Joe

            lda L1F77              ; X-pos Joe
            cmp #$1E               ; Check leaving screen right
            bmi L12AA              ; 30 36

            ldx L1F6A              ; Current room number
            lda L0D00,X            ; Room data
            and #$01               ; Check exit right?
            beq L128A              ; F0 0C

            dec L1F77              ; X-pos Joe

            dec L1F1C              ; Stand=8 walk=6 jump=$A
            dec L1F1C              ; Stand=8 walk=6 jump=$A

            jmp L1443              ; Update pointers

; Exit screen to right side

L128A:      inc L1F6A              ; Current room number

            lda L1F6A              ; Current room number
            and #$07               ; 29 07
            bne L129D              ; D0 09
            lda L1F6A              ; Current room number
            sec                    ; 38
            sbc #$08               ; E9 08
            sta L1F6A              ; Current room number

L129D:      lda #$01               ; Set pos left screen
            sta L1F77              ; X-pos Joe
            lda #$0A
            sta L1F1C              ; Stand=8 walk=6 jump=$A
            jmp L15C2              ; Continue

L12AA:      lda #$0A               ; Joe jumps
            sta L1F1C              ; Stand=8 walk=6 jump=$A

            lda L1FAB              ; AD AB 1F
            clc                    ; 18
            adc L0086              ; 65 86
            sta L0086              ; 85 86
            lda #$00               ; A9 00
            adc L0087              ; 65 87
            sta L0087              ; 85 87

L12BD:      lda L1FAC              ; AD AC 1F
            beq L1321              ; F0 5F

            inc L1F1C              ; Stand=8 walk=6 jump=$A
            inc L1F1C              ; Stand=8 walk=6 jump=$A

            lda L1F1C              ; Stand=8 walk=6 jump=$A
            cmp #$0E               ; C9 0E
            bne L1321              ; D0 52

; Joe is jumping

            dec L1F77              ; X-pos Joe
            ldx L1F77              ; X-pos Joe
            dex                    ; CA
            bpl L1310              ; 10 38

            ldx L1F6A              ; Current room number
            lda L0D00,X            ; Room data
            and #$02               ; Check exit left
            beq L12EE              ; F0 0C

            inc L1F77              ; X-pos Joe

            dec L1F1C              ; Stand=8 walk=6 jump=$A
            dec L1F1C              ; Stand=8 walk=6 jump=$A

            jmp L1443              ; Update pointers

; Exit screen to left side

L12EE:      dec L1F6A              ; Current room number

            lda L1F6A              ; Current room number
            and #$07               ; Check
            cmp #$07               ; C9 07
            bne L1303              ; D0 09
            lda L1F6A              ; Current room number
            clc                    ; 18
            adc #$08               ; 69 08
            sta L1F6A              ; Current room number

L1303:      lda #$1D               ; Set right pos screen
            sta L1F77              ; X-pos Joe

            lda #$0A
            sta L1F1C              ; Stand=8 walk=6 jump=$A
            jmp L15C2              ; Continue

L1310:      lda #$0A               ; A9 0A
            sta L1F1C              ; Stand=8 walk=6 jump=$A
            lda L0086              ; A5 86
            sec                    ; 38
            sbc L1FAC              ; ED AC 1F
            sta L0086              ; 85 86
            bcs L1321              ; B0 02
            dec L0087              ; C6 87

L1321:      jmp L1443              ; Update pointers
            rts                    ; 60

;--------------------------------------------

L1325:      lda L1F00              ; Key up/jump
            beq L136D              ; F0 43

;            jsr L2140              ; Perform sound jumping

            lda #$00               ; A9 00
            sta L1FAC              ; 8D AC 1F
            sta L1FAB              ; 8D AB 1F

            lda L1F1C              ; Stand=8 walk=6 jump=$A
            sta L1FAD              ; 8D AD 1F

            clc                    ; 18
            adc #$04               ; 69 04
            sta L1F1C              ; Stand=8 walk=6 jump=$A

            lda #$19               ; Set jumping start value
            sta L1FAA              ; Jump up counter

            lda L1F02              ; Key X - right
            bne L1353              ; D0 08

            lda L1F01              ; Key Z - left
            bne L1360              ; D0 10

            jmp L1116              ; 4C 16 11

;--------------------------------------------

L1353:      lda #$01               ; Direction=right
            sta L1F6B              ; Direction Joe, 0=left, 1=right

;            lda #$08               ; A9 08
	lda #$01
            sta L1FAB              ; 8D AB 1F
            jmp L1116              ; 4C 16 11

L1360:      lda #$00               ; Direction=left
            sta L1F6B              ; Direction Joe, 0=left, 1=right

;            lda #$08               ; A9 08
	lda #$01
            sta L1FAC              ; 8D AC 1F
            jmp L1116              ; 4C 16 11

;--------------------------------------------
; Check keys
;--------------------------------------------

L136D:      lda L1F02              ; Key X - right
            beq L1375
            jmp L13E1              ; If pressed, jump

L1375:      lda L1F01              ; Key Z - left
            bne L137B              ; If pressed, jump
            rts

; Joe walking left

L137B:      ldx L1F6B              ; Direction Joe, 0=left, 1=right
            beq L1386              ; Check if already walking to left
            ldx #$00               ; If not set direction=left
            stx L1F6B              ; Direction Joe, 0=left, 1=right
            rts

L1386:      ldx L1F1C              ; Stand=8 walk=6 jump=$A
            inx                    ; 6->8, 8->A
            inx
            cpx #$0A               ; E0 0A
            beq L1393              ; F0 04
            stx L1F1C              ; Stand=8 walk=6 jump=$A
            rts                    ; 60

L1393:
;            jsr L215E              ; Perform SOUND command walking left
	lda #6
	ldx #8
	ldy #14
	jsr sound
;	lda $b002
;	eor #$04
;	sta $b002

            dec L1F77              ; Dec X-pos Joe

            ldx L1F77              ; X-pos Joe
            dex                    ; CA
            bpl L13CC              ; If not of screen left, jump

            ldx L1F6A              ; Current room number
            lda L0D00,X            ; Room data
            and #$02               ; Check for exit left
            beq L13AF              ; If exit, jump
            inc L1F77              ; Reset X-pos Joe
            jmp L1443              ; Update pointers

; Joe leaves screen to left

L13AF:      dec L1F6A              ; Current room number

            lda L1F6A              ; Current room number
            and #$07               ; 29 07
            cmp #$07               ; C9 07
            bne L13C4              ; D0 09

            lda L1F6A              ; Current room number
            clc                    ; 18
            adc #$08               ; 69 08
            sta L1F6A              ; Current room number

L13C4:      lda #$1D               ; Set pos right screen
            sta L1F77              ; X-pos Joe
            jmp L15C2              ; Continue

L13CC:      ldx #$06
            stx L1F1C              ; Stand=8 walk=6 jump=$A

            dec L0086              ; Move Joe 1 byte left

            jmp L1443              ; Update pointers

; Joe walking right

L13E1:      ldx L1F6B              ; Direction Joe, 0=left, 1=right
            bne L13EC              ; Check if already walking to right
            ldx #$01               ; If not set direction=right
            stx L1F6B              ; Direction Joe, 0=left, 1=right
            rts

L13EC:      ldx L1F1C              ; Stand=8 walk=6 jump=$A
            inx                    ; 6->8, 8->A
            inx
            cpx #$0A               ; E0 0A
            beq L13F9              ; F0 04
            stx L1F1C              ; Stand=8 walk=6 jump=$A
            rts                    ; 60

L13F9:
;            jsr L215E              ; Perform SOUND command walking right
	lda #6
	ldx #8
	ldy #14
	jsr sound
;	lda $b002
;	eor #$04
;	sta $b002

            inc L1F77              ; Dec X-pos Joe

            ldx L1F77              ; X-pos Joe
            cpx #$1E
            bmi L1431              ; If not of screen right, jump

            ldx L1F6A              ; Current room number
            lda L0D00,X            ; Room data
            and #$01               ; Check for exit right
            beq L1416              ; F0 06
            dec L1F77              ; X-pos Joe
            jmp L1443              ; Update pointers

; Joe leaves screen to right

L1416:      inc L1F6A              ; Current room number
            lda L1F6A              ; Current room number
            and #$07               ; 29 07
            bne L1429              ; D0 09

            lda L1F6A              ; Current room number
            sec                    ; 38
            sbc #$08               ; E9 08
            sta L1F6A              ; Current room number

L1429:      lda #$01               ; Set pos left screen
            sta L1F77              ; X-pos Joe
            jmp L15C2              ; Continue

L1431:      ldx #$06
            stx L1F1C              ; Stand=8 walk=6 jump=$A

            inc L0086              ; Move Joe 1 byte right

;--------------------------------------------
; Update pointers
;--------------------------------------------

L1443:
            lda #$40               ; A9 40
            clc                    ; 18
            adc L0086              ; 65 86
            sta L0088              ; 85 88
            lda #$01               ; A9 01
            adc L0087              ; 65 87
            sta L0089              ; 85 89

            lda #$40               ; A9 40
            clc                    ; 18
            adc L0088              ; 65 88
            sta L008A              ; 85 8A
            lda #$01               ; A9 01
            adc L0089              ; 65 89
            sta L008B              ; 85 8B

            lda #$40               ; A9 40
            clc                    ; 18
            adc L008A              ; 65 8A
            sta L008C              ; 85 8C
            lda #$01               ; A9 01
            adc L008B              ; 65 8B
            sta L008D              ; 85 8D

            lda #$40               ; A9 40
            clc                    ; 18
            adc L008C              ; 65 8C
            sta L008E              ; 85 8E
            lda #$01               ; A9 01
            adc L008D              ; 65 8D
            sta L008F              ; 85 8F

            rts                    ; 60

;--------------------------------------------
; Mirror sprite
;--------------------------------------------

; Mirror L59A0-5A9F

L1478:      ldx #$00               ; A2 00
L147A:      ldy L59A0,X            ; BC A0 59
            lda L58A0,Y            ; B9 A0 58
            sta L59A0,X            ; 9D A0 59
            dex                    ; CA
            bne L147A              ; D0 F4

; Mirror L5AA0-5AFF

            ldx #$3F               ; A2 3F
L1488:      ldy L5AA0,X            ; BC A0 5A
            lda L58A0,Y            ; B9 A0 58
            sta L5AA0,X            ; 9D A0 5A
            dex                    ; CA
            bne L1488              ; D0 F4

; Switch data

            ldy #$07               ; Set counter

            ldx #$09
            stx L0078              ; Set counter

            lda #<L59B8            ; 80/81 = L59B8
            sta L0080 
            lda #>L59B8
            sta L0081

            lda #<L59A0            ; 82/83 = L59A0
            sta L0082
            lda #>L59A0
            sta L0083

            lda #<L59B0            ; 84/85 = L59B0
            sta L0084
            lda #>L59B0
            sta L0085

            lda #<L59A8            ; 7A/7B = L59A8
            sta L007A 
            lda #>L59A8
            sta L007B

L14BA:      lda (L0080),Y          ; Switch data 80/81 <-> 82/83
            tax
            lda (L0082),Y
            sta (L0080),Y
            txa
            sta (L0082),Y

            lda (L0084),Y          ; Switch data 84/85 <-> 7A/7B
            tax
            lda (L007A),Y
            sta (L0084),Y
            txa
            sta (L007A),Y

            dey                    ; Next
            bpl L14BA

; Update pointers

            lda L0080              ; 80/81 + $20
            clc
            adc #$20
            sta L0080
            bcc L14DC
            inc L0081

L14DC:      lda L0082              ; 82/83 + $20
            clc
            adc #$20
            sta L0082
            bcc L14E7
            inc L0083

L14E7:      lda L0084              ; 84/85 + $20
            clc
            adc #$20
            sta L0084
            bcc L14F2
            inc L0085

L14F2:      lda L007A              ; 7A/7B + $20
            clc
            adc #$20
            sta L007A
            bcc L14FD
            inc L007B

L14FD:      ldy #$07               ; Reset counter
            dec L0078              ; Next
            bpl L14BA

            rts

L1504:      .byte $01,$02
L1506:      .byte $03

;--------------------------------------------
; Plot background tiles, ok
;--------------------------------------------

L1507:      ldy #$00               ; A0 00

            lda #>L6720            ; Set screen address
            sta L007B              ; 85 7B
            lda #<L6720            ; A9 20
            sta L007A              ; 85 7A

L1511:      sty L1504              ; Set column counter

            lda #$00               ; A9 00
            sta L1506              ; 8D 06 15
            ldy #>L0400               ; A0 04
            ldx #$03               ; A2 03
            lda #$00               ; top row screen
            jsr L1555              ; Plot tile

            lda #$00               ; A9 00
            sta L1506              ; 8D 06 15
            ldy #$50               ; A0 50
            ldx #$04               ; A2 04
            lda #$04               ; middle row screen
            jsr L1555              ; Plot tile

            lda #$08               ; A9 08
            sta L1506              ; 8D 06 15
            ldy #$50               ; A0 50
            ldx #$04               ; A2 04
            lda #$08               ; bottom row screen
            jsr L1555              ; Plot tile

            clc                    ; Point to next column
            lda L007A              ; A5 7A
            adc #$4                ; 69 20
            sta L007A              ; 85 7A
            bcc L1549              ; 90 02
            inc L007B              ; E6 7B

L1549:      ldy L1504              ; Get column counter
            iny                    ; Next column
            cpy #$08               ; Check for 8 columns
            bne L1511

;            jsr L0161              ; Wipe top BG line

            rts                    ; 60

;--------------------------------------------
; Plot tile
;
; A = offset hb screen
; X = 
; Y = 
;--------------------------------------------

L1555:      clc                    ; Calculate hb screen
            adc L007B              ; 65 7B
            sta L0079              ; 85 79
            lda L007A              ; Set lb screen
            sta L0078              ; 85 78

            lda L1F6A              ; Current room number
            sta L0076              ; 85 76

            lda #$00               ; A9 00
            clc                    ; 18
L1566:      rol L0076              ; 26 76
            rol A                  ; 2A
            dex                    ; CA
            bne L1566              ; D0 FA

            clc                    ; 18
            sta L0077              ; 85 77

            tya                    ; 98
            adc L0077              ; 65 77
            sta L0077              ; 85 77

            clc                    ; 18
            lda L1506              ; AD 06 15
            adc L0076              ; 65 76
            sta L0076              ; 85 76

            lda #$00               ; A9 00
            adc L0077              ; 65 77
            sta L0077              ; 85 77

            ldy L1504              ; AC 04 15
            lda (L0076),Y          ; B1 76
            sta L0076              ; 85 76

            lda #$00               ; A9 00
            clc                    ; 18
            ldx #$07               ; A2 07

L158E:      rol L0076              ; 26 76
            rol A                  ; 2A

            dex                    ; CA
            bne L158E              ; D0 FA

            clc                    ; 18
            adc #$30
            sta L0077              ; 85 77

            ldx #$04               ; Put BG sprite on screen
	stx vcount
L159B:      ldy #$1F               ; A0 1F
	sty counter
L159D:
	ldy counter
            lda (L0076),Y          ; B1 76
	ldx counter
	ldy scrval,x
            sta (L0078),Y          ; 91 78
            dec counter                    ; 88
            bpl L159D              ; 10 F9

	inc L0079

            lda #$20               ; A9 20
            clc                    ; 18
            adc L0076              ; 65 76
            sta L0076              ; 85 76

            lda #$00               ; A9 00
            adc L0077              ; 65 77
            sta L0077              ; 85 77

	dec vcount
            bne L159B              ; D0 DA

            rts                    ; 60

vcount:		.byte 0

;--------------------------------------------
; Start game
;--------------------------------------------

L15C2:      jsr L23C0              ; Test for end of game

            jsr L1A06              ; ???

            lda #$00               ; A9 00
            sta L1F68              ; Guard1 flag
            sta L1F69              ; Guard2 flag

            lda #$02               ; A9 02
            sta L1F6C              ; Delay guard1
            sta L1F74              ; Delay guard2

; Check for guards in the room

            ldx L1F6A              ; Current room number
            lda L2000,X            ; Check guard1
            tax                    ; AA
            and #$40               ; 29 40
            beq L15FA              ; F0 17

; Set default X-pos guard1

            txa                    ; Reset bit 6,7 of roomnr
            and #$3F               ; 29 3F
            sta L1F68              ; Guard1 flag

            ldx L1F6A              ; Current room number
            lda L2080,X            ; Check guard2
            tax                    ; AA
            and #$40               ; 29 40
            beq L15FA              ; F0 06

; Set default X-pos guard2

            txa                    ; Reset bit 6,7 of roomnr
            and #$3F               ; 29 3F
            sta L1F69              ; Guard2 flag

; Plot background

L15FA:      jsr L1507              ; Plot background tiles

            jsr L2240              ; Check for opening exits left/right

; Bit 6/7 of roomdata = front colour

            ldx L1F6A              ; Current room number
            lda L0D00,X            ; Room data
            pha                    ; Save room data

            lsr A                  ; 4A
            lsr A                  ; 4A
            lsr A                  ; 4A
            lsr A                  ; 4A
            lsr A                  ; 4A
            lsr A                  ; 4A
            tax                    ; AA
            lda L1FD8,X            ; Read room data
            jsr L21C0              ; 20 C0 21

; Set pointer 70/71 depending on bit 4/5 room data:
;
;  L60E0 with L1F67 = $05 if bit 4/5 = 0
;  L6180 with L1F67 = $19 if bit 4/5 <>0

            pla                    ; Get room data

;            ldx #<L60E0            ; Bit 4/5 room data clear
            ldx #<(L60C0+4)
            stx L0070              ; 70/71 = L60E0
            ldx #$05               ; L1F67 = $05
            stx L1F67              ; No exit left down
;            ldx #>L60E0
            ldx #>(L60C0+4)
            stx L0071

            and #$30               ; Check bit 4/5 room data
            beq L1633              ; Skip if 0

;            ldx #<L6180            ; Bit 4/5 room data set
            ldx #<(L60C0+$18)
            stx L0070              ; 70/71 = L6180
;            ldx #>L6180            ; L1F67 = $19
            ldx #>(L60C0+$18)
            stx L0071              ; Exit left down
            ldx #$19
            stx L1F67
L1633:
            lda #$00               ; A9 00
            sta L1F66              ; Special object nr
            sta L1F1F              ; 8D 1F 1F

; Check 16 rooms for key starting at obj 0

            ldx #$00               ; A2 00
            ldy #$0F               ; A0 0F
            jsr L169D              ; 20 9D 16
            bne L1676              ; D0 32

; Check 7 rooms for food starting at obj 15

            ldx #$0F               ; A2 0F
            ldy #$06               ; A0 06
            jsr L169D              ; 20 9D 16
            bne L167E              ; D0 31

; Check 7 rooms for bomb starting at obj 24

            ldx #$18               ; A2 18
            ldy #$06               ; A0 06
            jsr L169D              ; 20 9D 16
            bne L1683              ; D0 2D

; Check 7 rooms for hostages starting at obj 36

            ldx #$24               ; A2 24
            ldy #$06               ; A0 06
            jsr L169D              ; 20 9D 16
            bne L168B              ; D0 2C

; Check 3 rooms for chest starting at obj 32

            ldx #$20               ; A2 20
            ldy #$02               ; A0 02
            jsr L169D              ; 20 9D 16
            bne L1693              ; D0 2B

; Check 3 rooms for disguise starting at obj 43

            ldx #$2B               ; A2 2B
            ldy #$02               ; A0 02
            jsr L169D              ; 20 9D 16
            bne L1698              ; D0 27

            ldx #$00               ; A2 00
            jmp L16B2              ; 4C B2 16

;----------------------------------------------

L1676:      ldx #$01               ; Get key
            inc L1F1F              ; Add 1350 to score
            jmp L16B2              ; 4C B2 16

L167E:      ldx #$02               ; Get food
            jmp L16B2              ; 4C B2 16

L1683:      ldx #$03               ; Get bomb
            inc L1F1F              ; EE 1F 1F
            jmp L16B2              ; 4C B2 16

L168B:      ldx #$04               ; Get hostage
            inc L1F1F              ; Add 1350 to score
            jmp L16B2              ; 4C B2 16

L1693:      ldx #$05               ; Get chest
            jmp L16B2              ; 4C B2 16

L1698:      ldx #$06               ; Get disguise
            jmp L16B2              ; 4C B2 16

;----------------------------------------------
; Check current room for special objects
; 
; Input:
;
; Output:
;  A = 1 if special object in room
;  X = special object nr
;----------------------------------------------

L169D:      lda L1F6A              ; Current room number
            cmp L5B56,X            ; DD 56 5B
            beq L16AC              ; F0 07

            inx                    ; E8
            dey                    ; 88
            bpl L169D              ; 10 F4

            lda #$00               ; A9 00
            rts                    ; 60

L16AC:      lda #$01               ; A9 01
            stx L1F60              ; 8E 60 1F
            rts                    ; 60

;----------------------------------------------
; Copy screen to screenbuffer
;----------------------------------------------

L16B2:      stx L1F66              ; Special object nr
            ldx #$00               ; A2 00
L16B7:      lda L6C20,X            ; BD 20 6C
            sta L5BC0,X            ; 9D C0 5B
            lda L6D60,X            ; BD 60 6D
            sta L5D00,X            ; 9D 00 5D
            lda L6EA0,X            ; BD A0 6E
            sta L5E40,X            ; 9D 40 5E
            lda L6FE0,X            ; BD E0 6F
            sta L5F80,X            ; 9D 80 5F
            lda L7120,X            ; BD 20 71
            sta L60C0,X            ; 9D C0 60
            lda L7260,X            ; BD 60 72
            sta L6200,X            ; 9D 00 62
            lda L73A0,X            ; BD A0 73
            sta L6340,X            ; 9D 40 63
            lda L74E0,X            ; BD E0 74
            sta L6480,X            ; 9D 80 64
            dex                    ; CA
            bne L16B7              ; D0 CD

; Update guard 2

            lda L1F69              ; Guard2 flag
            sta L1F76              ; X-pos guard2

            ldx #$08
            jsr L175A              ; Update pointers guard2

; Update guard 2

            lda L1F68              ; Guard1 flag
            sta L1F6E              ; X-pos guard1

            ldx #$00
            jsr L175A              ; Update pointers guard1

; Update Joe

            lda L1F77              ; X-pos Joe
            jsr L173F              ; Calculate address in A,Y
            sta L0087              ; Store address in 86/87
            sty L0086

            ldx L1FAA              ; Jump up counter
            beq L173B              ; Joe on floor?

L170F:      lda L1F78,X            ; Joe jumping table
            tay                    ; A8
            and #$10               ; 29 10
            beq L1724              ; F0 0D

            sec                    ; 38
            lda L0086              ; A5 86
            sbc #$40               ; E9 40
            sta L0086              ; 85 86
            lda L0087              ; A5 87
            sbc #$01               ; E9 01
            sta L0087              ; 85 87

L1724:      tya                    ; 98
            and #$08               ; 29 08
            beq L1736              ; F0 0D
            clc                    ; 18

            lda L0086              ; A5 86
            adc #$40               ; 69 40
            sta L0086              ; 85 86
            lda L0087              ; A5 87
            adc #$01               ; 69 01
            sta L0087              ; 85 87

L1736:      inx                    ; E8
            cpx #$19               ; E0 19
            bne L170F              ; D0 D4

L173B:
            jsr L1443              ; Update pointers
            rts                    ; 60

;----------------------------------------------
; Calculate bufferaddress = X-pos*8 + L60B8
;----------------------------------------------
;
; Input:
;  A = X-pos
;
; Output:
;  A = hb address
;  Y = lb address
;----------------------------------------------

L173F:
            sta L0078              ; 85 78
            lda #$00               ; A9 00
;            clc                    ; 18
;            rol L0078              ; 26 78
;            rol A                  ; 2A
;            rol L0078              ; 26 78
;            rol A                  ; 2A
;            rol L0078              ; 26 78
;            rol A                  ; 2A
            sta L0079              ; 85 79

;            lda #<L60B8               ; A9 B8
	lda #<(L60C0-1)
            clc                    ; 18
            adc L0078              ; 65 78
            tay                    ; A8
;            lda #>L60B8               ; A9 60
	lda #>(L60C0-1)
            adc L0079              ; 65 79
            rts                    ; 60

;----------------------------------------------
; Update pointers guard
;----------------------------------------------
;
; Input:
;  X = 0 -> guard1
;  X = 8 -> guard2
;
; Output:
;  90/91 = Bufferaddress guard position top line
;  92/93 = Bufferaddress guard position 2nd line
;  94/95 = Bufferaddress guard position 3rd line
;  96/97 = Bufferaddress guard position 4th line
;----------------------------------------------

L175A:      lda L1F6E,X            ; X-pos guard1
            jsr L173F              ; Calculate address in A,Y
            sta L0091,X            ; 90/91 = top line
            tya
            sta L0090,X

            lda L0090,X            ; 92/93 = 2nd line
            clc
            adc #$40
            sta L0092,X
            lda L0091,X
            adc #$01
            sta L0093,X

            lda L0092,X            ; 94/95 = 3rd line
            clc
            adc #$40
            sta L0094,X
            lda L0093,X
            adc #$01
            sta L0095,X

            lda L0094,X            ; 96/97 = 4th line
            clc
            adc #$40
            sta L0096,X
            lda L0095,X
            adc #$01
            sta L0097,X

            rts

;----------------------------------------------
; Plot object1
;
; Input:
;  70/71 = screen buffer address
;----------------------------------------------

L178D:
; Point to object1

	lda #<L5CC0               ; Mask object1
	sta L17B2+1
	lda #>L5CC0
	sta L17B2+2

	lda #<L5CE0               ; Data object1
	sta L17AC+1
	lda #>L5CE0
	sta L17AC+2

; Plot object

L179D:
            lda L0070              ; A5 70
            sta L0082              ; 85 82
            lda L0071              ; A5 71
            sta L0083              ; 85 83

            ldy #$04               ; A2 04
	sty vcount
L17A7:
            ldx #$1F               ; A0 1F
L17A9:
	ldy scrval,x
L17AC:
	lda $ffff,x
            and (L0082),Y          ; 31 82
L17B2:
	ora $ffff,x
            sta (L0082),Y          ; 91 82
	dex
            bpl L17A9              ; 10 F5

            lda L17B2+1            ; Next bufferline
            clc
            adc #$40
            sta L17B2+1
            lda L17B2+2
            adc #$01
            sta L17B2+2

            lda L17B2+1            ; Next shapeline
            clc
            adc #$20
            sta L17AC+1
            lda L17B2+2
            adc #$00
            sta L17AC+2

            lda L0082              ; A5 82
            clc                    ; 18
            adc #$40               ; 69 40
            sta L0082              ; 85 82
            lda L0083              ; A5 83
            adc #$01               ; 69 01
            sta L0083              ; 85 83

	dec vcount                    ; CA
            bne L17A7              ; D0 C9

            rts                    ; 60

;----------------------------------------------
; Plot object2
;
; Input:
;  70/71 = screen buffer address
;----------------------------------------------

L17DF:
	lda #<L61C0                ; Mask object2
	sta L17B2+1
	lda #>L61C0
	sta L17B2+2

	lda #<L61E0                ; Data object2
	sta L17AC+1
	lda #>L61E0
	sta L17AC+2

	jmp L179D                  ; Plot object

;----------------------------------------------
; Plot special object in room
;----------------------------------------------

L17F2:      ldx L1F66              ; Special object nr

            dex                    ; CA
            txa                    ; 8A
            clc                    ; 18
            asl A                  ; 0A
            asl A                  ; 0A

            tax                    ; 
            lda L1F48,X            ; Special object data
	sta L1824+1
            lda L1F49,X            ; BD 49 1F
	sta L1824+2

            lda L1F4A,X            ; Special object mask
	sta L1820+1
            lda L1F4B,X            ; BD 4B 1F
	sta L1820+2

            lda L0070              ; Special object screenposition
            sta L0082              ; 85 82
            lda L0071              ; A5 71
            sta L0083              ; 85 83

            ldy #$04               ; A2 04
	sty vcount
L1819:
            ldx #$1F               ; A0 1F
L181B:
	ldy scrval,x
L1820:
            lda $ffff,x          ; B1 84
            and (L0082),Y          ; 31 82
L1824:
            ora $ffff,x          ; 11 80
            sta (L0082),Y          ; 91 82
            dex                    ; 88
            bpl L181B              ; 10 F5

            lda L1824+1              ; A5 80
            clc                    ; 18
            adc #$20               ; 69 20
            sta L1824+1              ; 85 80
            lda L1824+2              ; A5 81
            adc #$00               ; 69 00
            sta L1824+2              ; 85 81

            lda L1824+1              ; A5 80
            clc                    ; 18
            adc #$80               ; 69 80
            sta L1820+1              ; 85 84
            lda L1824+2              ; A5 81
            adc #$00               ; 69 00
            sta L1820+2              ; 85 85

            lda L0082              ; A5 82
            clc                    ; 18
            adc #$40               ; 69 40
            sta L0082              ; 85 82
            lda L0083              ; A5 83
            adc #$01               ; 69 01
            sta L0083              ; 85 83

            dec vcount                    ; CA
            bne L1819              ; D0 C9

            rts                    ; 60

;--------------------------------------------
; Program entry
;--------------------------------------------

L1851:
	jsr initIRQ

            jsr L2340              ; Rotate shapedat

            ldx #$64               ; Backup 20 shapes
L1856:      lda L5AE0-1,X          ; Shapedat source
            sta L5B56-1,X          ; Shapedat dest
            dex
            bne L1856

            jsr L25BB              ; Wipe screen $6720-$761F

            jsr L1E9D              ; Plot strength bar

            lda #$06
            sta L1F1C              ; Stand=8 walk=6 jump=$A

            lda #$7B
            sta L1F6A              ; Current room number

            lda #$00
            sta L1FAE              ; Killed flag
            sta L1FAA              ; Jump up counter
	sta cursor_x
	sta cursor_y

            lda #$14
            sta L1F63              ; ??

            lda #$00
            sta L1F47              ; ??
            sta L1F65              ; Nr of keys
            sta L1F61              ; Nr of bombs
            sta L1F62              ; Nr of men

            ldx #$04
L188C:      sta L1FDC,X            ; Reset time
            sta L1F20,X            ; Reset score
            dex
            bpl L188C

            jsr L1E64              ; Print score

            lda #$02               ; Time = 20:00
            sta L1FDF

            lda #$0A
            sta L1FE0              ; ??

            lda #$00               ; Print '0' for keys in panel
            ldx #>keys             ; Set screenaddress
            ldy #<keys
            jsr L1D95              ; Print number A at address X,Y

            lda #$00               ; Print '0' for bombs in panel
            ldx #>bombs            ; Set screenaddress
            ldy #<bombs
            jsr L1D95              ; Print number A at address X,Y

            lda #$00               ; Print '0' for men in panel
            ldx #>men              ; Set screenaddress
            ldy #<men
            jsr L1D95              ; Print number A at address X,Y

            lda #$06               ; Screen on
            jsr LFFEE

            ldx L22E0+$A           ; Move cursor to X,Y
            ldy L22E0+$9
            jsr set_cursor

            ldx #$0A-2             ; Print 'JOE BLADE' at 14,17
L18C9:      lda L22E0,X
            jsr LFFEE
            dex
            bpl L18C9

            ldx L22EB+$13          ; Move cursor to X,Y
            ldy L22EB+$12
            jsr set_cursor

            ldx #$13-2             ; Print 'Press fire or play'
L18D9:      lda L22EB,X
            jsr LFFEE
            dex
            bpl L18D9

; Wait for keypress:
;  RETURN = keyboard
;   fire  = joystick

	jsr joyinit
	lda #0			; Set keyboardflag
	sta L1F15

L18E2:
	jsr joyget		; Check if fire on joystick pressed
	and #$10
	bne L18EB

            jsr L0E00              ; Keyscan
            lda L1F03
            beq L18E2              ; Wait until RET pressed

L18EA:      jsr L0E00              ; Keyscan
            lda L1F03
            bne L18EA              ; Wait until RET released

;	lda #0			; Set keyboardflag
;	sta L1F15
	jmp L18EC

L18EB:
	lda #1			; Set joystickflag
	sta L1F15
L18EC:
            jsr L15C2              ; Start game

L18F5:      lda L1F47              ; AD 47 1F
            beq L18FD              ; F0 03
            jmp L1851              ; 4C 51 18

;---------------------------------------------

L18FD:      lda #$00               ; Reset system clock
            ldx #$04               ; A2 04
L1901:      sta L1F6F,X            ; 9D 6F 1F
            dex                    ; CA
            bpl L1901              ; 10 FA

	jsr settime
;            ldx #>L1F6F               ; A2 6F
;            ldy #<L1F6F               ; A0 1F
;            lda #$02               ; Write system clock
;            jsr LFFF1              ; 20 F1 FF

            lda L1FAE              ; Killed flag
            beq L1923              ; F0 0E

            ldx #$0A               ; A2 0A
            stx L0078              ; 86 78

L1919:      jsr L1D68              ; Perform 10 shot SOUND
            dec L0078              ; C6 78
            bne L1919              ; D0 F9

            jmp L1851              ; 4C 51 18

;---------------------------------------------

L1923:      lda L1F19              ; Check strength flag
            bne L1937              ; D0 0F

            dec L1F1A              ; CE 1A 1F
            bne L1937              ; D0 0A

            dec L1F1B              ; CE 1B 1F
            bne L1937              ; D0 05

            lda #$01               ; A9 01
            sta L1F19              ; Decrement strength flag

L1937:
            jsr L1A7D              ; 20 7D 1A

            jsr L1116              ; 20 16 11

            jsr L0FAA              ; 20 AA 0F

            jsr L1BCA              ; 20 CA 1B

            lda L1F68              ; Guard1 flag
            and #$01               ; 29 01
            beq L195E              ; F0 14

            lda L1F6E              ; X-pos guard1 
            cmp L1F77              ; X-pos Joe
            bcc L1959              ; 90 07

            lda #$00               ; Direction = left
            sta L1F6D              ; Direction guard1, 0=left, 1=right
            beq L195E              ; Forced jump

L1959:      lda #$01               ; Direction = right
            sta L1F6D              ; Direction guard1, 0=left, 1=right

L195E:      lda L1F69              ; Guard2 flag
            and #$01               ; 29 01
            beq L1979              ; F0 14

            lda L1F76              ; X-pos guard2
            cmp L1F77              ; X-pos Joe
            bcc L1974              ; 90 07

            lda #$00               ; Set direction=left
            sta L1F75              ; Direction guard2, 0=left, 1=right
            beq L1979              ; Forced jump

L1974:      lda #$01               ; Set direction=right
            sta L1F75              ; Direction guard2, 0=left, 1=right

L1979:      lda L1FE1              ; Death flicker flag guard 1
            ora L1FE2              ; Death flicker flag guard 2
            bne L198B              ; D0 0A

            ldx #$00               ; A2 00
            jsr L10BD              ; 20 BD 10

            ldx #$08               ; A2 08
            jsr L10BD              ; 20 BD 10

L198B:
            jsr L0EC0              ; 20 C0 0E

            jsr L1DAF

L1991:
;            ldx #>L1F6F               ; A2 6F
;            ldy #<L1F6F               ; A0 1F
;            lda #$01               ; Read system clock
;            jsr LFFF1              ; 20 F1 FF
	jsr gettime

            lda L1F6F              ; AD 6F 1F
            cmp #$0A               ; C9 0A
            bmi L1991              ; 30 F0

            lda L1F61              ; Nr of bombs
            beq L19DB              ; F0 35

            dec L1FE0              ; CE E0 1F
            bne L19DB              ; D0 30

            lda #$0A               ; A9 0A
            sta L1FE0              ; 8D E0 1F

            dec L1FDC              ; CE DC 1F
            bpl L19DB              ; 10 26

            lda #$09               ; A9 09
            sta L1FDC              ; 8D DC 1F

            dec L1FDD              ; CE DD 1F
            bpl L19DB              ; 10 1C

            lda #$05               ; A9 05
            sta L1FDD              ; 8D DD 1F

            dec L1FDE              ; CE DE 1F
            bpl L19DB              ; 10 12

            lda #$09               ; A9 09
            sta L1FDE              ; 8D DE 1F

            dec L1FDF              ; CE DF 1F
            bpl L19DB              ; 10 08

            lda #$01               ; A9 01
            sta L1FAE              ; Killed flag

            jmp L18F5              ; 4C F5 18

;--------------------------------------------
; Print time 00:00
;--------------------------------------------

min_l = $940F
min_r = $9410
sec_l = $9412
sec_r = $9413

L19DB:      ldy #<sec_r               ; A0 78
            ldx #>sec_r               ; A2 7A
            lda L1FDC              ; AD DC 1F
            jsr L1D95              ; Print number A at address X,Y
            ldy #<sec_l               ; A0 70
            ldx #>sec_l               ; A2 7A
            lda L1FDD              ; AD DD 1F
            jsr L1D95              ; Print number A at address X,Y
            ldy #<min_r               ; A0 60
            ldx #>min_r               ; A2 7A
            lda L1FDE              ; AD DE 1F
            jsr L1D95              ; Print number A at address X,Y
            ldy #<min_l               ; A0 58
            ldx #>min_l               ; A2 7A
            lda L1FDF              ; AD DF 1F
            jsr L1D95              ; Print number A at address X,Y
            jmp L18F5              ; 4C F5 18

;--------------------------------------------
; 76/77 -> L5BC0 Backup screen
; 78/79 -> Start address level map
;          L5000 +(high nibble roomnumber)*$100
; 7A/7B -> 
;--------------------------------------------

; Set Backupscreen address 76/77

L1A06:
            lda #>L5BC0               ; A9 5B
            sta L0076              ; 85 76
            lda #<L5BC0               ; A9 C0
            sta L0077              ; 85 77

            ldx #$00               ; A2 00

; Set Start address room background data 78/79

            lda L1F6A              ; Current room number
            sta L0078              ; 85 78

            lda #$00               ; A9 00
            clc                    ; 18
            rol L0078              ; 26 78
            rol A                  ; 2A
            rol L0078              ; 26 78
            rol A                  ; 2A
            rol L0078              ; 26 78
            rol A                  ; 2A
            rol L0078              ; 26 78
            rol A                  ; 2A
            sta L0079              ; 85 79
	clc
	lda L0078
	adc #<L5000
	sta L0078
	lda L0079
	adc #>L5000               ; 69 50
	sta L0079


; Set BG tile address 7A/7B

            ldy #0               ; A0 00
L1A2A:      lda (L0078),Y          ; B1 78
            sta L007A              ; 85 7A

            lda #$00               ; A9 00
            clc                    ; 18
            rol L007A              ; 26 7A
            rol A                  ; 2A
            rol L007A              ; 26 7A
            rol A                  ; 2A
            rol L007A              ; 26 7A
            rol A                  ; 2A
            rol L007A              ; 26 7A
            rol A                  ; 2A
            rol L007A              ; 26 7A
            rol A                  ; 2A
            rol L007A              ; 26 7A
            rol A                  ; 2A
            rol L007A              ; 26 7A
            rol A                  ; 2A
            sta L007B              ; 85 7B

	clc
	lda L007A
	adc #<L3000
	sta L007A
	lda L007B
	adc #>L3000               ; 69 30
	sta L007B

; Store BG tile address pointer at L5820-L5836
; Store Backup screen address pointer L5800-L581F

            lda L007A              ; A5 7A
            sta L5820,X            ; 9D 20 58
            lda L007B              ; A5 7B
            sta L5821,X            ; 9D 21 58

            lda L0077              ; A5 77
            sta L5800,X            ; 9D 00 58
            lda L0076              ; A5 76
            sta L5801,X            ; 9D 01 58

            inx                    ; E8
            inx                    ; E8

            lda L0077              ; Backup screen addres +$20
            clc                    ; 18
	adc #4
            sta L0077              ; 85 77
            lda L0076              ; A5 76
            adc #$00               ; 69 00
            sta L0076              ; 85 76

            cpy #$07               ; C0 07
            bne L1A77              ; D0 06

	clc
	lda L0077
	adc #$e0
	sta L0077
            lda L0076              ; When y=7, Backup screen address +#300
            adc #$04               ; 69 03
            sta L0076              ; 85 76

L1A77:      iny                    ; C8
            cpy #$10               ; C0 10
            bne L1A2A              ; D0 AE

            rts                    ; 60

;--------------------------------------------

L1A7D:      lda L1F77              ; X-pos Joe
            lsr A                  ; 4A
            and #$FE               ; 29 FE
            sta L0078              ; 85 78
            clc                    ; 18
            adc #$10               ; 69 10
            tax                    ; AA
            jsr L1AB3              ; 20 B3 1A

            ldx L0078              ; A6 78
            jsr L1AB3              ; 20 B3 1A

            lda L1F68              ; Guard1 flag
            beq L1AA3              ; F0 0D

            lda L1F6E              ; X-pos guard1
            lsr A                  ; 4A
            and #$FE               ; 29 FE
            clc                    ; 18
            adc #$10               ; 69 10
            tax                    ; AA
            jsr L1AB3              ; 20 B3 1A

L1AA3:      lda L1F69              ; Guard2 flag
            bne L1AA9              ; D0 01
            rts                    ; 60

L1AA9:      lda L1F76              ; X-pos guard2
            lsr A                  ; 4A
            and #$FE               ; 29 FE
            clc                    ; 18
            adc #$10               ; 69 10
            tax                    ; AA

L1AB3:      stx L0077              ; 86 77

; Copy BG tiles to mirror1

            lda L5820,X            ; Set background tile address
            sta L1AF3+1              ; 8D F4 1A
            lda L5821,X            ; BD 21 58
            sta L1AF3+2              ; 8D F5 1A

            lda L5800,X            ; Set screen address
            sta L1AF6+1              ; 8D F7 1A
            lda L5801,X            ; BD 01 58
            sta L1AF6+2              ; 8D F8 1A

            ldy #$04               ; Tile = 4 rows
	sty vcount
            jmp L1AF1              ; Plot background tile

L1AD2:
	lda L1AF3+1		; Point to next row tile data
	clc
	adc #$20
	sta L1AF3+1
	bcc L1AE0
	inc L1AF3+2
L1AE0:
	lda L1AF6+1		; Point to next mirrorblock
	clc
	adc #$40
	sta L1AF6+1
	lda L1AF6+2
	adc #$01
	sta L1AF6+2
L1AF1:
	ldx #$1F
L1AF3:
	lda L04BC,X		; Load background tile data
	ldy scrval,x
L1AF6:
	sta L04BC,Y		; Display on screen
	dex
	bpl L1AF3

	dec vcount		; Repeat for next row
	bne L1AD2

            ldx L0077              ; A6 77
            cpx #$1E               ; E0 1E
            beq L1B55              ; F0 50
            cpx #$0E               ; E0 0E
            beq L1B55              ; F0 4C

; Copy BG tiles to mirror2

            inx                    ; E8
            inx                    ; E8
            lda L5820,X            ; BD 20 58
            sta L1B49+1              ; 8D 4A 1B
            lda L5821,X            ; BD 21 58
            sta L1B49+2              ; 8D 4B 1B
            lda L5800,X            ; BD 00 58
            sta L1B4C+1              ; 8D 4D 1B
            lda L5801,X            ; BD 01 58
            sta L1B4C+2              ; 8D 4E 1B

            ldy #$04               ; A0 04
	sty vcount
            jmp L1B47              ; 4C 47 1B

L1B28:
	lda L1B49+1              ; AD 4A 1B
	clc                    ; 18
	adc #$20               ; 69 20
	sta L1B49+1              ; 8D 4A 1B
	bcc L1B36              ; 90 03
	inc L1B49+2              ; EE 4B 1B
L1B36:
	lda L1B4C+1              ; AD 4D 1B
	clc                    ; 18
	adc #$40               ; 69 40
	sta L1B4C+1              ; 8D 4D 1B
	lda L1B4C+2              ; AD 4E 1B
	adc #$01               ; 69 01
	sta L1B4C+2              ; 8D 4E 1B
L1B47:
	ldx #$0F               ; A2 0F
L1B49:
	lda L04BC,X            ; BD BC 04
	ldy scrval,x
L1B4C:
	sta L04BC,Y            ; 9D BC 04
	dex                    ; CA
	bpl L1B49              ; 10 F7

	dec vcount                    ; 88
	bne L1B28              ; D0 D3
L1B55:
            ldx L0077              ; A6 77
            cpx #$00               ; E0 00
            beq L1BAD              ; F0 52
            cpx #$10               ; E0 10
            beq L1BAD              ; F0 4E

; Copy BG tiles to mirror3

            dex                    ; CA
            dex                    ; CA
            lda L5820,X            ; BD 20 58
            sta L1B9F+1              ; 8D A0 1B
            lda L5821,X            ; BD 21 58
            sta L1B9F+2              ; 8D A1 1B
            lda L5800,X            ; BD 00 58
            sta L1BA2+1              ; 8D A3 1B
            lda L5801,X            ; BD 01 58
            sta L1BA2+2              ; 8D A4 1B

            ldy #$04               ; A0 04
	sty vcount
            jmp L1B9D              ; 4C 9D 1B

L1B7E:
	lda L1B9F+1              ; AD A0 1B
	clc                    ; 18
	adc #$20               ; 69 20
	sta L1B9F+1              ; 8D A0 1B
	bcc L1B8C              ; 90 03
	inc L1B9F+2              ; EE A1 1B
L1B8C:
	lda L1BA2+1              ; AD A3 1B
	clc                    ; 18
	adc #$40               ; 69 40
	sta L1BA2+1              ; 8D A3 1B
	lda L1BA2+2              ; AD A4 1B
	adc #$01               ; 69 01
	sta L1BA2+2              ; 8D A4 1B
L1B9D:
	ldx #$1F               ; A2 1F
L1B9F:
	lda L04BC,X            ; BD BC 04
	ldy scrval,x
L1BA2:
	sta L04BC,Y            ; 9D BC 04
	dex                    ; CA
	cpx #$17               ; E0 17
	bne L1B9F              ; D0 F5

	dec vcount                    ; 88
	bne L1B7E              ; D0 D1

; Plot special object in room

L1BAD:      lda L1F66              ; Special object nr
            beq L1BC9              ; If no onject, skip
            cmp #$05
            bne L1BBC              ; If no chest skip
            jsr L178D              ; Plot object1
            jmp L1BC9              ; Continue

L1BBC:      cmp #$06
            bne L1BC6              ; If no disguise, skip
            jsr L17DF              ; Plot object2
            jmp L1BC9              ; Continue

L1BC6:      jmp L17F2              ; Plot special object

L1BC9:      rts

;----------------------------------------------

L1BCA:      lda L1F66              ; Special object nr
            bne L1BD2              ; D0 03
            jmp L1CBC              ; 4C BC 1C

L1BD2:      lda L1F67              ; AD 67 1F
            cmp L1F77              ; X-pos Joe
            beq L1BDD              ; F0 03
            jmp L1CBC              ; 4C BC 1C

L1BDD:      jsr L1DE5              ; 20 E5 1D
            jsr L1D83              ; 20 83 1D

            lda L1F66              ; Special object nr
            cmp #$01               ; Check if key
            bne L1BFC              ; If not, jump
            lda #$00               ; Reset 
            sta L1F66              ; Special object nr
            inc L1F65              ; Inc nr of keys

            lda L1F65              ; Nr of keys
            ldx #>keys             ; Set position in panel
            ldy #<keys
            jmp L1D8C              ; 4C 8C 1D

L1BFC:      lda L1F66              ; Special object nr
            cmp #$02               ; Check food
            bne L1C11              ; If not, jump
            lda #$00               ; Reset 
            sta L1F66              ; Special object nr

            ldx L1F60              ; AE 60 1F
            sta L5B56,X            ; 9D 56 5B
            jmp L1E9D              ; Plot strength bar

L1C11:      lda L1F66              ; Special object nr
            cmp #$03               ; Check bomb
            bne L1C82              ; If not, jump

            ldx L1FD7              ; AE D7 1F
            dex                    ; CA
            bpl L1C20              ; 10 02

            ldx #$07               ; A2 07
L1C20:      stx L1FD7              ; 8E D7 1F
            lda L1FAF,X            ; BD AF 1F
            sta L1F10              ; 8D 10 1F
            lda L1FB7,X            ; BD B7 1F
            sta L1F11              ; 8D 11 1F
            lda L1FBF,X            ; BD BF 1F
            sta L1F12              ; 8D 12 1F
            lda L1FC7,X            ; BD C7 1F
            sta L1F13              ; 8D 13 1F
            lda L1FCF,X            ; BD CF 1F
            sta L1F14              ; 8D 14 1F

            jsr L25D4              ; Print 'SELF DESTRUCT ....

            ldy #$00               ; A0 00

; Set 7A/7B=$8500

            lda #>L6720               ; A9 67
            sta L007B              ; 85 7B
            lda #<L6720               ; A9 20
            sta L007A              ; 85 7A

L1C4E:      sty L1504              ; 8C 04 15

            lda #$00               ; A9 00
            sta L1506              ; 8D 06 15

            ldy #>L0400            ; Top row background
            ldx #$03               ; A2 03
            lda #$00               ; A9 00
            jsr L1555              ; Plot tile

            clc                    ; 18
            lda L007A              ; A5 7A
            adc #$04               ; 69 20
            sta L007A              ; 85 7A
            bcc L1C6A              ; 90 02
            inc L007B              ; E6 7B

L1C6A:      ldy L1504              ; AC 04 15
            iny                    ; C8
            cpy #$08               ; C0 08
            bne L1C4E              ; D0 DC

            jsr L2240              ; 20 40 22
            inc L1F61              ; Nr of bombs

            lda L1F61              ; Nr of bombs
            ldx #>bombs            ; Set position in panel
            ldy #<bombs
            jmp L1D8C              ; Print

L1C82:      lda L1F66              ; Special object nr
            cmp #$04               ; C9 04
            bne L1C96              ; D0 0D
            inc L1F62              ; Nr of men

            lda L1F62              ; Nr of men
            ldx #>men              ; Set position in panel
            ldy #<men
            jmp L1D8C              ; Print

L1C96:      lda L1F66              ; Special object nr
            cmp #$05               ; C9 05
            bne L1CA5              ; D0 08
            lda #$14               ; A9 14
            sta L1F63              ; 8D 63 1F
            jmp L1D7E              ; 4C 7E 1D

L1CA5:      lda L1F66              ; Special object nr
            cmp #$06               ; C9 06
            bne L1CBC              ; D0 10
            lda #$00               ; A9 00
            sta L1F19              ; Decrement strength flag
            sta L1F1A              ; 8D 1A 1F
            lda #$03               ; A9 03
            sta L1F1B              ; 8D 1B 1F
            jmp L1D7E              ; 4C 7E 1D

L1CBC:      lda L1FAA              ; Jump up counter
            bne L1D2F              ; Joe jumping?

            lda L1F03              ; Key RET
            beq L1D2F              ; F0 69
            ldx L1F63              ; AE 63 1F
            cpx #$00               ; E0 00
            bne L1CD0              ; D0 03
            jmp L1D2F              ; 4C 2F 1D

L1CD0:      dex                    ; CA
            stx L1F63              ; 8E 63 1F
            jsr L1D68              ; Perform 10 shot SOUND
            lda L1F68              ; Guard1 flag
            ora L1F69              ; Guard2 flag
            beq L1D2F              ; F0 50
            lda L1F6B              ; Direction Joe, 0=left, 1=right
            beq L1D0B              ; F0 27

            lda L1F68              ; Guard1 flag
            beq L1CF6              ; F0 0D

            lda L1F77              ; X-pos Joe
            cmp L1F6E              ; X-pos guard1
            bcs L1CF6              ; B0 05

            lda #$0C               ; A9 32
            sta L1FE1              ; Death flicker flag guard 1

L1CF6:      lda L1F69              ; Guard2 flag
            beq L1D08              ; F0 0D

            lda L1F77              ; X-pos Joe
            cmp L1F76              ; X-pos guard2
            bcs L1D08              ; B0 05

            lda #$0C               ; A9 32
            sta L1FE2              ; Death flicker flag guard 2

L1D08:      jmp L1D2F              ; 4C 2F 1D

L1D0B:      lda L1F68              ; Guard1 flag
            beq L1D1D              ; F0 0D

            lda L1F77              ; X-pos Joe
            cmp L1F6E              ; X-pos guard1
            bcc L1D1D              ; 90 05

            lda #$0C               ; A9 32
            sta L1FE1              ; Death flicker flag guard 1

L1D1D:      lda L1F69              ; Guard2 flag
            beq L1D2F              ; F0 0D

            lda L1F77              ; X-pos Joe
            cmp L1F76              ; X-pos guard2
            bcc L1D2F              ; 90 05

            lda #$0C               ; A9 32
            sta L1FE2              ; Death flicker flag guard 2

; Check hit Joe with guard1

L1D2F:      lda L1F68              ; Check if Guard1 exists
            beq L1D4F

            lda L1FAA              ; Jump up counter
            cmp #$12               ; C9 12
            bcc L1D3F              ; 90 04

            cmp #$20               ; C9 20
            bcc L1D64              ; 90 25

L1D3F:      ldx #$05               ; Check 4 position for hit
            ldy L1F77              ; X-pos Joe
            dey                    ; Check block left of Joe
            dey
L1D46:      cpy L1F6E              ; X-pos guard1
            beq L1D65              ; Jump if hit
            iny                    ; Next pos
            dex                    ; All pos checked?
            bne L1D46

; Check hit Joe-guard2

L1D4F:      lda L1F69              ; Check if Guard2 exists
            beq L1D64

            ldx #$05               ; Check 4 position for hit
            ldy L1F77              ; X-pos Joe
            dey                    ; Check block left of Joe
            dey
L1D5B:      cpy L1F76              ; X-pos guard2
            beq L1D65              ; Jump if hit
            iny                    ; Next pos
            dex                    ; All pos checked?
            bne L1D5B

L1D64:      rts

L1D65:      jmp L1EB5              ; Decrement strength

;--------------------------------------------
; Perform 10 shot SOUND commands
;--------------------------------------------

L1D68:
            ldx #$0A               ; A2 0A
            stx L0077              ; 86 77

L1D6C:
;       jsr L215E              ; Perform SOUND command

	lda #4
	ldx #8
	ldy #14
	jsr sound
;	lda $b002
;	eor #$4
;	sta $b002

            ldy #$28               ; Waiting loop
            ldx #$00               ; A2 00
L1D73:      dex                    ; CA
            bne L1D73              ; D0 FD
            dey                    ; 88
            bne L1D73              ; D0 FA

            dec L0077              ; C6 77
            bne L1D6C              ; D0 EF
            rts                    ; 60

;--------------------------------------------

L1D7E:      lda #$00               ; A9 00
            sta L1F66              ; Special object nr

L1D83:      lda #$00               ; A9 00
            ldx L1F60              ; AE 60 1F
            sta L5B56,X            ; 9D 56 5B
            rts                    ; 60

L1D8C:      pha                    ; 48
            txa                    ; 8A
            pha                    ; 48
            jsr L1D7E              ; 20 7E 1D
            pla                    ; 68
            tax                    ; AA
            pla                    ; 68

;----------------------------------------------
; Print number A at address X (hb),Y (lb)
;----------------------------------------------

L1D95:
	sty L1DA7+1            ; Set screenaddress
	stx L1DA7+2

	asl A                  ; Calculate number data pointer
	asl A
	asl A
	clc
	adc #$07
	tay

	ldx #$07               ; Set char line counter
	stx counter
L1DA4:
	ldx counter            ; Get screen row offset
	lda scrval,x
	tax
	lda L5840,Y            ; Get number data
L1DA7:
	sta L04BC,X            ; Store number data on screen
	dey
	dec counter            ; Next char line
	bpl L1DA4              ; Repeat for 8 lines

	rts
counter:
	.byte 0

;----------------------------------------------
; Copy screen buffer to screen
;----------------------------------------------

L1DAF:      ldx #$00               ; A2 00
L1DB1:      lda L5BC0,X            ; BD C0 5B
            sta L6C20,X            ; 9D 20 6C
            lda L5D00,X            ; BD 00 5D
            sta L6D60,X            ; 9D 60 6D
            lda L5E40,X            ; BD 40 5E
            sta L6EA0,X            ; 9D A0 6E
            lda L5F80,X            ; BD 80 5F
            sta L6FE0,X            ; 9D E0 6F
            lda L60C0,X            ; BD C0 60
            sta L7120,X            ; 9D 20 71
            lda L6200,X            ; BD 00 62
            sta L7260,X            ; 9D 60 72
            lda L6340,X            ; BD 40 63
            sta L73A0,X            ; 9D A0 73
            lda L6480,X            ; BD 80 64
            sta L74E0,X            ; 9D E0 74
            dex                    ; CA
            bne L1DB1              ; D0 CD
            rts                    ; 60

;----------------------------------------------

L1DE5:      lda #$11               ; A9 11
            sta L1F58              ; 8D 58 1F
            lda #$02               ; A9 02
            sta L1F5A              ; 8D 5A 1F
            lda #$20               ; A9 20
            sta L1F5E              ; 8D 5E 1F
            lda #$00               ; A9 00
            sta L1F5C              ; 8D 5C 1F

; Perform SOUND special object
;            ldx #$58               ; A2 58
;            ldy #$1F               ; A0 1F
;            lda #$07               ; Perform SOUND special object
;            jsr LFFF1              ; 20 F1 FF

	lda #10		; Sound pickup
	ldx #8
	ldy #14
	jsr sound

	lda #0		; Siren down
	sta counter
L1DF0:
	lda #1
	ldx counter
	ldy #1
	jsr sound
	ldy #4
L1DF1:
	ldx #0
L1DF2:
	dex
	bne L1DF2
	dey
	bne L1DF1
	inc counter
	lda counter
	cmp #30
	bne L1DF0

L1DF3:			; Siren up
	lda #1
	ldx counter
	ldy #1
	jsr sound

	ldy #4
L1DF4:
	ldx #0
L1DF5:
	dex
	bne L1DF5
	dey
	bne L1DF4

	dec counter
	bne L1DF3

	lda #10		; Sound pickup
	ldx #8
	ldy #14
	jsr sound


;            ldx #$00               ; A2 00
;            ldy #$00               ; A0 00
;            sta L0077              ; 85 77
;L1E08:      dex                    ; CA
;            bne L1E08              ; D0 FD
;            dey                    ; 88
;            bne L1E08              ; D0 FA
;
;            dec L0077              ; C6 77
;            bne L1E08              ; D0 F6

            jsr L1E16              ; Print score
            rts                    ; 60

;--------------------------------------------
; Add 50 to score and print score
; L1F1F = 0 -> Print score
; L1F1F = 1 -> Add 50 to score and print score
;--------------------------------------------

L1E16:      lda L1F1F              ; Check add_score flag
            beq L1E64              ; F0 49

            lda L1F24              ; Add 50 to score
            clc                    ; 18
            adc #$05               ; 69 05
            cmp #$0A               ; C9 0A
            bcc L1E2B              ; 90 06
            sec                    ; 38
            sbc #$0A               ; E9 0A
            inc L1F23              ; EE 23 1F
L1E2B:      sta L1F24              ; 8D 24 1F
            lda L1F23              ; AD 23 1F
            clc                    ; 18
            adc #$03               ; 69 03
            cmp #$0A               ; C9 0A
            bcc L1E3E              ; 90 06
            sec                    ; 38
            sbc #$0A               ; E9 0A
            inc L1F22              ; EE 22 1F
L1E3E:      sta L1F23              ; 8D 23 1F
            lda L1F22              ; AD 22 1F
            clc                    ; 18
            adc #$01               ; 69 01
            cmp #$0A               ; C9 0A
            bcc L1E51              ; 90 06
            inc L1F21              ; EE 21 1F
            sec                    ; 38
            sbc #$0A               ; E9 0A
L1E51:      sta L1F22              ; 8D 22 1F
            lda L1F21              ; AD 21 1F
            cmp #$0A               ; C9 0A
            bcc L1E61              ; 90 06
            inc L1F20              ; EE 20 1F
            sec                    ; 38
            sbc #$0A               ; E9 0A
L1E61:      sta L1F21              ; 8D 21 1F

; Print score

L1E64:
	lda #>score            ; Set score screenaddress
	sta L1E83+2
	lda #<score
	sta L1E83+1

	ldx #$00               ; Reset char pointer
	stx L0078
L1E72:
	ldx L0078              ; Get pointer
	lda L1F20,X            ; Get score digit
	ldx #$07               ; Calculate number data address
	asl A
	asl A
	asl A
	clc
	adc #$07
	tay

	ldx #7                 ; Char line pointer
	stx counter
L1E80:
	ldx counter
	lda scrval,x           ; Get screen line offset
	tax
	lda L5840,Y            ; Get number data
L1E83:
	sta L04BC,x            ; Screenaddress score digit
	dey
	dec counter
	bpl L1E80              ; All char lines plot?

	inc L1E83+1            ; Next score digit
	ldx L0078
	inx
	stx L0078
	cpx #$06               ; All digits printed?
	bne L1E72

	rts
;--------------------------------------------
; Strength bar
; L1F19=0 -> plot strength bar
; L1F19=1 -> decrement + plot strength bar
;--------------------------------------------

L7CC8 = $962D
L7CD0 = $962E

; Clear strength bar line for line, 6 lines

L1E9D:
	lda #$FF               ; Reset strength
	sta L1F26

	ldx #$00               ; Clear strength bar
L1EA4:
	lda #$00               ; Clear bar line
	sta L7CC8,X
	inx
	txa
	and #$07               ; Check end of line
	bne L1EA4
L1EB2:
	clc                    ; Point to next line
	txa
	adc #$20
	and #$f0
	tax
	cmp #$c0               ; Check if 6 lines are plotted
	bne L1EA4
L1EB5:
	lda L1F19              ; Decrement strength flag
	beq L1EC5

	dec L1F26              ; Strength bar
	bne L1EC5              ; Check if strength=0

	lda #$01               ; Yes, death
	sta L1FAE              ; Set killed flag

	rts

; Plot strength pointer

L1EC5:
	lda L1F26              ; Strength bar / 32 for 8 steps
	lsr A
	lsr A
	sta L0078              ; Scale strength to bar

	and #$07               ; Determine pixel position pointer
	tax
	lda #$80
	cpx #$00
	beq L1EDF              ; If 0, skip shifting
L1EDB:
	lsr A                  ; Shift pixel to right position
	dex
	bne L1EDB
L1EDF:
	sta L0079              ; Pointer bit calculated

	lda L0078              ; Get strength
	lsr a
	lsr a
	lsr a
	tax                    ; Calculate byte position
L1EE7:
	lda L0079              ; Get pixelmask
	sta L7CC8,X            ; Set pixel of strength pointer
	lda #$00
	sta L7CD0,X            ; Wipe next byte (pointer only moves to left)
L1EEC:
	txa                    ; Point to next line
	clc
	adc #$20
	tax
	and #$f0
	cmp #$c0               ; Check if 6 lines plot
	bne L1EE7

	rts

;L1EFD:
;	.byte $54,$70,$61
