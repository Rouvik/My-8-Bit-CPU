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
|SWP|0111|Swaps the values of Register X and Y, <b>Warning: This will cause the value of R Register be deleted</b>|
|AOUT|1000|Loads sum of Register X and Y to Out Register for display|
|SOUT|1001|Loads the difference of Register X and Y to Out Register for display|
|JMP|1010|Jumps to an  address provided in the operand within the same CLK cycle for execution|

