main:
	greset ; clean up the screen for drawing
	ldx 0
	ldy 0
	jmp loop

loop:
	ldy 1
	atx
	xtr
	rty

	ldr 118 ; charteuse xterm-255 color
	gdraw

	ldy 255 ; for comparison
	
	cmp
	jze end
	jmp loop

end:
	ldr 1
	rout
	hlt
