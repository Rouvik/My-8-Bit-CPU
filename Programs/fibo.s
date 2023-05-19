; A simple fibonacci program for my 8 bit computer (RCPU-II) to be assembled by rasm
; written by Rouvik Maji 30th April, 2023 11:27 PM IST
ldx 1
ldy 0

loop:
atr ; store sum to R register
rout ; display term
rtx ; copy from R to X (inverted order)
swp ; swap X and Y to settle the terms in order
jmp loop ; jump back to instruction 2 (atr)
