;
; Start of code
;
;            *= $6100
;

L0900:	; Object1, Key mask white
            .byte $00,$00,$00,$00,$01,$07,$07,$0F
            .byte $00,$00,$00,$00,$F0,$FC,$FE,$0E
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $0E,$0E,$0E,$0E,$07,$07,$03,$01
            .byte $07,$07,$07,$07,$0F,$FE,$FF,$F7
            .byte $00,$00,$00,$00,$00,$00,$00,$80
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $03,$01,$00,$00,$00,$00,$00,$00
            .byte $C0,$E0,$F0,$78,$3C,$1E,$0F,$1F
            .byte $00,$00,$00,$00,$00,$00,$00,$80
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $3F,$7B,$37,$0F,$0E,$00,$00,$00
            .byte $C0,$C0,$80,$00,$00,$00,$00,$00
L0980:	; Key mask black
            .byte $FF,$FF,$FF,$FE,$F9,$F7,$F7,$EF
            .byte $FF,$FF,$FF,$0F,$F3,$FD,$FE,$0E
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $EE,$EE,$EE,$EE,$F7,$F7,$FB,$FD
            .byte $F7,$F7,$F7,$F7,$0F,$FE,$FF,$F7
            .byte $7F,$7F,$7F,$7F,$7F,$FF,$7F,$BF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FE,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $0B,$FD,$FE,$FF,$FF,$FF,$FF,$FF
            .byte $DF,$EF,$F7,$7B,$BD,$DE,$EF,$DF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$7F,$BF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $BF,$7B,$B7,$CF,$EE,$F1,$FF,$FF
            .byte $DF,$DF,$BF,$7F,$FF,$FF,$FF,$FF

L0A00:	; Object 2, Food mask white
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$07,$00,$05,$05,$05,$05
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$01
            .byte $00,$08,$08,$10,$10,$13,$E7,$BF
            .byte $08,$08,$08,$10,$10,$90,$D0,$D7
            .byte $80,$80,$80,$40,$40,$40,$00,$C0
            .byte $01,$01,$0C,$07,$07,$0B,$03,$05
            .byte $7F,$7F,$7F,$3F,$CF,$F3,$FC,$FF
            .byte $D7,$D6,$D7,$D7,$D6,$97,$10,$10
            .byte $40,$80,$40,$C0,$00,$C0,$00,$40
            .byte $01,$02,$00,$02,$00,$00,$00,$00
            .byte $FF,$FF,$00,$FF,$00,$FF,$00,$00
            .byte $C0,$F0,$00,$FE,$00,$FE,$00,$00
            .byte $40,$40,$40,$40,$40,$00,$00,$00
L0A80:	; Food mask black
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$F8,$F7,$F8,$F5,$F5,$F5,$F5
            .byte $FF,$FF,$7F,$FF,$7F,$7F,$7F,$7F
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FE,$FD
            .byte $F7,$EB,$EB,$D7,$D4,$13,$E7,$BF
            .byte $E8,$E8,$E8,$D0,$50,$90,$D0,$D7
            .byte $BF,$BF,$BF,$5F,$5F,$5F,$1F,$DF
            .byte $FD,$E1,$EC,$E7,$E7,$EB,$E3,$F5
            .byte $7F,$7F,$7F,$3F,$CF,$F3,$FC,$FF
            .byte $D7,$D6,$D7,$D7,$D6,$97,$50,$10
            .byte $5F,$9F,$5F,$DF,$1F,$DF,$1F,$5F
            .byte $F1,$F2,$F8,$FA,$FC,$FC,$FE,$FF
            .byte $FF,$FF,$00,$FF,$00,$FF,$00,$FF
            .byte $C0,$F0,$00,$FE,$00,$FE,$00,$FF
            .byte $5F,$5F,$5F,$5F,$5F,$3F,$FF,$FF

L0B00:	; Object 3, Bomb mask white
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$C0
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $01,$02,$02,$04,$04,$1E,$20,$2F
            .byte $20,$40,$40,$80,$80,$F0,$08,$A8
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$01,$01,$02,$02,$02,$02
            .byte $40,$80,$00,$00,$00,$00,$00,$00
            .byte $04,$5A,$2D,$0D,$16,$0E,$16,$0E
            .byte $00,$00,$00,$00,$80,$80,$80,$80
            .byte $02,$02,$02,$01,$01,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$80,$40,$30
            .byte $16,$0E,$16,$05,$2D,$1A,$64,$18
            .byte $80,$80,$80,$00,$00,$00,$00,$00
L0B80:	; Bomb mask black
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FE,$FE,$FC,$FC,$FC,$E0,$EF
            .byte $BF,$7F,$7F,$FF,$FF,$FF,$0F,$AF
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$FE,$FE,$FE,$FE
            .byte $C0,$80,$00,$00,$00,$00,$00,$00
            .byte $07,$5B,$2D,$0D,$16,$0E,$16,$0E
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FE,$FE,$FE,$FF,$FF,$FF,$FF,$FF
            .byte $00,$00,$00,$00,$00,$80,$C0,$F0
            .byte $16,$0E,$16,$05,$2D,$1A,$64,$18
            .byte $FF,$FF,$FF,$FF,$3F,$07,$07,$1F

L0C00:	; Oject 4, Hostage mask white
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$00,$3C,$7F,$7F
            .byte $00,$00,$00,$00,$00,$F0,$F8,$F8
            .byte $00,$00,$00,$00,$00,$00,$00,$00
            .byte $00,$00,$00,$00,$03,$0F,$1F,$1C
            .byte $7F,$00,$7F,$3F,$80,$C3,$DC,$B8
            .byte $F8,$00,$F8,$F0,$03,$87,$73,$39
            .byte $00,$00,$00,$00,$80,$F0,$F8,$78
            .byte $1E,$1F,$0F,$07,$03,$01,$01,$01
            .byte $39,$9F,$C7,$F0,$F8,$FE,$E0,$9E
            .byte $38,$F7,$CF,$1F,$3F,$FF,$0F,$F3
            .byte $F8,$F8,$F0,$E0,$C0,$80,$80,$80
            .byte $39,$7C,$7D,$7D,$3E,$1E,$0E,$00
            .byte $7F,$7F,$FF,$FF,$FF,$EF,$80,$00
            .byte $FD,$FC,$FF,$FF,$FF,$F7,$01,$00
            .byte $9C,$BE,$BE,$BE,$7C,$78,$70,$00
L0C80:	; Hostage mask black
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FF,$C3,$BC,$7F,$7F
            .byte $FF,$FF,$FF,$FF,$0F,$F7,$FB,$FB
            .byte $FF,$FF,$FF,$FF,$FF,$FF,$FF,$FF
            .byte $FF,$FF,$FF,$FC,$F3,$EF,$DF,$DC
            .byte $7F,$00,$7F,$3F,$80,$C3,$DC,$B8
            .byte $FB,$03,$FB,$F4,$03,$87,$73,$39
            .byte $FF,$FF,$FF,$7F,$8F,$F7,$FB,$7B
            .byte $DE,$DF,$EF,$F7,$FB,$FD,$FD,$C5
            .byte $39,$9F,$C7,$F0,$F8,$FE,$E0,$9E
            .byte $38,$F7,$CF,$1F,$3F,$FF,$0F,$F3
            .byte $FB,$FB,$F7,$EF,$DF,$BF,$BF,$A3
            .byte $B9,$7C,$7D,$7D,$BE,$DE,$EE,$F0
            .byte $7F,$7F,$FF,$FF,$FF,$EF,$90,$7F
            .byte $FD,$FC,$FF,$FF,$FF,$F7,$09,$FE
            .byte $9D,$BE,$BE,$BE,$7D,$7B,$77,$0F
