; a simple counter program
; by Rouvik Maji

ldx 0
ldy 1

loop:
	atr
	rout ; display
	rtx
	jmp loop
