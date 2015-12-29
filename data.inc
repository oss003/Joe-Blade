;
; Start of code
;
;            *= $7100
;

L1F00:      .byte $00		; Key : - up/jump
L1F01:      .byte $00		; Key Z - left
L1F02:      .byte $00		; Key X - right
L1F03:      .byte $00		; Key RET
L1F04:      .byte $00		; Key / - down

L1F05:      .byte $00

L1F06:      .byte $00,$01,$02,$00,$01	; X-pos left letter selector
L1F0B:      .byte $02,$03,$04,$03,$04	; X-pos right letter selector

L1F10:      .byte $04		; Bombpuzzle letter1
L1F11:      .byte $01		; Bombpuzzle letter2
L1F12:      .byte $02		; Bombpuzzle letter3
L1F13:      .byte $03		; Bombpuzzle letter4

L1F14:      .byte $00

;-----------------------------------------------

L1F15:      .byte $00		; Joystickflag

;-----------------------------------------------

L1F16:      .byte $00,$00,$00

L1F19:      .byte $01
L1F1A:      .byte $00
L1F1B:      .byte $00
L1F1C:      .byte $06		; Stand=8 walk=6 jump=$A
            .byte $02,$02

L1F1F:      .byte $00		; Add_Score flag, 1 = add 50

L1F20:      .byte $00		; Score digits l->r
L1F21:      .byte $00
L1F22:      .byte $00
L1F23:      .byte $00
L1F24:      .byte $00

L1F25:      .byte $00

L1F26:      .byte $FF		; Strength
L1F27:      .byte $05

L1F28:      .byte "NOW EVAH UOY SNOITAL"
            .byte "UTARGNOC",$0B,$02,$1F

L1F47:      .byte $00

; Special object data (4 bytes)
; 2x Mask data + 2x Spritedata

L1F48:      .byte <L0900	; Special object data 1 Key
L1F49:      .byte >L0900
L1F4A:      .byte <L0980
L1F4B:      .byte >L0980
L1F4C:      .byte <L0A00,>L0A00	; Special object data 2 Food
            .byte <L0A80,>L0A80
            .byte <L0B00,>L0B00	; Special object data 3 Bomb
            .byte <L0B80,>L0B80
            .byte <L0C00,>L0C00	; Special object data 4 Hostage
            .byte <L0C80,>L0C80

L1F58:      .byte $00,$00
L1F5A:      .byte $00,$00
L1F5C:      .byte $00,$00
L1F5E:      .byte $00,$00
L1F60:      .byte $00

L1F61:      .byte $00		; nr bombs
L1F62:      .byte $00		; nr men
L1F63:      .byte $14		; nr of gunshots

L1F64:      .byte $00
L1F65:      .byte $00		; nr keys

L1F66:      .byte $00		; Special object nr
L1F67:      .byte $00

L1F68:      .byte $00		; Guard1 flag, >0 -> start X-pos
L1F69:      .byte $00		; Guard2 flag, >0 -> start X-pos

L1F6A:      .byte $7A		; Actual Room number

L1F6B:      .byte $01           ; Direction Joe, 0=left, 1=right

; Guard 1 data
L1F6C:      .byte $02		; Delay guard1 0-3
L1F6D:      .byte $00		; Direction guard1, 0=left, 1=right
L1F6E:      .byte $64		; X-pos guard1

L1F6F:      .byte $00		; Buffer system clock (5x)
L1F70:      .byte $00
L1F71:      .byte $00,$00,$00

; Guard2 data
L1F74:      .byte $02		; Delay guard2 0-3
L1F75:      .byte $00		; Direction guard2, 0=left, 1=right
L1F76:      .byte $64		; X-pos guard2

L1F77:      .byte $08		; X-pos Joe

; Joe jumping table
L1F78:      .byte $2C,$28,$24,$28
            .byte $26,$24,$22,$28,$26,$24,$22,$20
            .byte $20,$20,$22,$24,$36,$22,$24,$36
            .byte $22,$24,$36,$20,$34,$20

            .byte $20,$20
            .byte $20,$20,$21,$21,$21,$22,$22,$23
            .byte $24,$25,$26,$37,$21,$23,$25,$37
            .byte $21,$23,$25,$37,$33,$20

L1FAA:      .byte $00		; Jump up counter
L1FAB:      .byte $00
L1FAC:      .byte $00
L1FAD:      .byte $00

L1FAE:      .byte $00		; Killed flag 1 = killed

L1FAF:      .byte $00,$02,$03,$01,$02,$04,$03,$01
L1FB7:      .byte $04,$03,$02,$00,$00,$03,$01,$02
L1FBF:      .byte $01,$01,$04,$04,$01,$01,$02,$03
L1FC7:      .byte $03,$04,$00,$02,$04,$00,$00,$04
L1FCF:      .byte $02,$00,$01,$03,$03,$02,$04,$00
L1FD7:      .byte $00

L1FD8:      .byte $00,$01,$02,$03

L1FDC:      .byte $00		; Time
L1FDD:      .byte $00
L1FDE:      .byte $00
L1FDF:      .byte $02

L1FE0:      .byte $0A
L1FE1:      .byte $00		; Death flicker flag guard 1
L1FE2:      .byte $00		; Death flicker flag guard 2
L1FE3:      .byte $00		; Flag for just going room up/down


; Joe sprite pointers

L1FE4:
	.byte >L2100,>L2200,>L2300,>L2400,>L2500,>L2600
L1FEA:
        .byte >L2700,>L2800,>L2900,>L2A00,>L2B00,>L2C00
	.byte >L2D00,>L2E00

L1FF2:
	.byte <L2100,<L2200,<L2300,<L2400,<L2500,<L2600
L1FF8:
        .byte <L2700,<L2800,<L2900,<L2A00,<L2B00,<L2C00
	.byte <L2D00,<L2E00
