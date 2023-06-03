ldx 0 ; i variable

loop:
	xout
	ldy 1 ; increment by 1
	atx
	ldy 11 ; i <= 10
	cmp
	jne loop
	hlt
