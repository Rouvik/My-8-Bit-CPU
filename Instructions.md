# Instructions:
|Alias|Opcode|Description|
|-----|------|-----------|
|NOP|0000|Does nothing and wastes a CLK cycle|
|LDX|0001|Loads a value from operand to Register X|
|XOUT|0010|Loads value from Register X to Out Register for display|
|LDY|0011|Loads a value from operand to Register Y|
|YOUT|0100|Loads value from Register Y to Out Register for display|
|LDR|0101|Loads a value from operand to Register R|
|ROUT|0110|Loads value from Register R to Out Register for display|
|SWP|0111|Swaps the values of Register X and Y<br><br><b>Warning: This will cause the value of R Register be deleted</b>|
|AOUT|1000|Loads sum of Register X and Y to Out Register for display|
|SOUT|1001|Loads the difference of Register X and Y to Out Register for display|
|JMP|1010|Jumps to an  address provided in the operand within the same CLK cycle for execution|
|ATX|1011|Add and store in X register<br><br><b>Warning: This will delete the value in R as R is used for copy</b>|
|ATY|1100|Add and store in Y register<br><br><b>Warning: This will delete the value in R as R is used for copy</b>|
|STX|1101|Substract and store in X register<br><br><b>Warning: This will delete the value in R as R is used for copy</b>|
|STY|1110|Substract and store in Y register<br><br><b>Warning: This will delete the value in R as R is used for copy</b>|
|XTR|1111|Copy from X to R register|
|YTR|10000|Copy from Y to R register|
|RTX|10001|Copy from R to X register|
|RTY|10010|Copy from R to Y register|
|ATR|10011|Add and store to R register|
|STR|10100|Subtract and store to R register|
|SAD|10101|Store address for a data to be fetched or stored for RAM|
|XLM|10110|Load a data from the specified address in `Address Register` to X Register|
|XTM|10111|Store a data to the specified address in `Address Register` from X Register|
|RLM|11000|Load a data from the specified address in `Address Register` to R Register|
|RTM|11001|Store a data to the specified address in `Address Register` from R Register|
|YLM|11010|Load a data from the specified address in `Address Register` to Y Register|
|YTM|11011|Store a data to the specified address in `Address Register` from Y Register|
|SADR|11100|Set the `Address Register` to the value in R Register|
|SADX|11101|Set the `Address Register` to the value in X Register|
|SADY|11110|Set the `Address Register` to the value in Y Register|
|CMP|11111|Compares the values in `registers X and Y` and updates CPU flags accordingly|
|JNE|100000|Jumps to the immediate address specified if the Negative(N) flag is 1|
|JZE|100001|Jumps to the immediate address specified if the Zero(Z) flag is 1|
|JOV|100010|Jumps to the immediate address specified if the Overflow(V) flag is 1|
|JPE|100011|Jumps to the immediate address specified if the Positive(P) flag is 1|
|GDRAW|100100|Draws a pixel with thr datas from the X Register(X coord) Y Register(Y coord) and R Resister(Pixel color XTERM-255)|
|GRESET|100101|Resets the display to all Black (0 in XTERM-255)|
|HLT|10000000|Stops CPU execution|
