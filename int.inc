;--------------------------------------------
; INT.INC
;
; Interrupt routine, center screen horizontal 
; for width=256 pixels
;
; !!! Not needed for Atom !!!
;--------------------------------------------

;
; Code equates
;
L00FC       = $00FC
L0204       = $0204
L0205       = $0205

LFE00       = $FE00
LFE08       = $FE08
LFE09       = $FE09

;
; Start of code
;
;            *= $0100
;

L0100:      .byte $00	; Old IRQ vec
L0101:      .byte $00

L0102:
            sei                    ; Set new vec
            lda L0204              ; AD 04 02
            sta L0100              ; 8D 00 01
            lda L0205              ; AD 05 02
            sta L0101              ; 8D 01 01
            lda #<L011B               ; A9 1B
            sta L0204              ; 8D 04 02
            lda #>L011B               ; A9 01
            sta L0205              ; 8D 05 02
            cli                    ; 58
            rts                    ; 60

;--------------------------------------------
; IRQ routine
;
; Start hor after 4 chars (32 pixels)
; Stop hor after 32 chars (256 pixels)
; Left on right 4 chars (32 pixels)
;--------------------------------------------

L011B:
            lda L00FC              ; A5 FC
            pha                    ; 48
            txa                    ; 8A
            pha                    ; 48
            tya                    ; 98
            pha                    ; 48
            lda LFE00              ; AD 00 FE
            and #$04               ; Scan 4 chars
            cmp #$04               ; C9 04
            bne L013D              ; D0 12
            lda #$FF               ; A9 FF
            sta LFE08              ; 8D 08 FE
            sta LFE09              ; 8D 09 FE
L0133:      pla                    ; 68
            tay                    ; A8
            pla                    ; 68
            tax                    ; AA
            pla                    ; 68
            sta L00FC              ; 85 FC
            jmp (L0100)            ; 6C 00 01

L013D:      lda LFE00              ; AD 00 FE
            and #$20               ; Scan 32 chars
            cmp #$20               ; C9 20
            bne L0133              ; D0 ED

            nop                    ; EA
            ldx L0159              ; AE 59 01
            lda L21D8,X            ; BD D8 21
            sta LFE08              ; 8D 08 FE
            lda L21DC,X            ; BD DC 21
            sta LFE09              ; 8D 09 FE
            jmp L0133              ; 4C 33 01

L0159:      .byte $00,$EA,$EA,$EA,$EA,$EA,$EA,$EA

;--------------------------------------------
; Wipe top BG line
;--------------------------------------------

L0161:
            ldx #$00               ; A2 00
            lda #$00               ; A9 00
L0165:      sta $8500,X            ; 9D 20 67
            dex                    ; CA
            bne L0165              ; D0 FA
            rts                    ; 60

            .byte $FF,$FF
