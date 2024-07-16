jmp main # initial jmp

# location 255 serves as call location

# draws a horizontal line
# Params:
#   - mem(0): start loc
#   - mem(1): end loc
#   - mem(2): y loc
#   - mem(3): color
hline:
    sad 0
    xlm

hline_loop:
    sad 2
    ylm
    sad 3
    rlm
    gdraw
    
    sad 1   # check end of loop
    ylm
    cmp
    jze hline_end
    ldy 1   # increment x
    atx
    jmp hline_loop

hline_end:
    sad 255
    xlm     # load jump location for return
    ldy 4
    atx     # increment to correct jump location
    jtx     # jump back to original program
    hlt     # halt here for errors

# draws a vertical line
# Params:
#   - mem(0): start loc
#   - mem(1): end loc
#   - mem(2): x loc
#   - mem(3): color
vline:
    sad 0
    ylm

vline_loop:
    sad 2
    xlm
    sad 3
    rlm
    gdraw
    
    sad 1   # check end of loop
    xlm
    cmp
    jze vline_end
    ldx 1   # increment x
    aty
    jmp vline_loop

vline_end:
    sad 255
    xlm     # load jump location for return
    ldy 4
    atx     # increment to correct jump location
    jtx     # jump back to original program
    hlt     # halt here for errors

main:
    greset
    ldx 50
    sad 0
    xtm
    ldx 205
    sad 1
    xtm
    ldx 128
    sad 2
    xtm
    ldx 10
    sad 3
    xtm         # set memory to required state for drawing the lines

    pcr
    sad 255
    rtm
    jmp vline   # call the vline function

    pcr
    sad 255
    rtm
    jmp hline   # call the hline function

    ldx 69      # set a number to display output
    xout
    hlt