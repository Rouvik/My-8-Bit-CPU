# My-8-Bit-CPU (Rouvik-CPU Mark-2)
Compilers, data sheets, resources and .circ files for my first 8-Bit CPU (Rouvik CPU - II)

## Requirements to run this project:
- <b>Logisim Evolution 3.7.2</b> (may work on other versions too)
- Load the .circ file and upload the required Microcode instructions to the microcode PLA below in logisim
- Compile and use the assembler in `/AssemblerSrc` to build your own hex file from a assembly source
- Pass the hex file to the Program ROM and use CTRL + K to run the simulation!

## How to compile rasm(Rouvik's Assembler) for your system:
Just grab any C++ compiler with std=c++11 in supported and compile the assembler.cpp
file in AssemblerSrc to get the assembler executable and that's it!

## RASM usage:
rasm [name of assembly file] [(optional) output file name]

## Details about the instruction set:
Read the [Instructions.md](https://github.com/Rouvik/My-8-Bit-CPU/blob/main/Instructions.md) to know more!

## Image examples:

### Basic Circuit Schematic:
![8-Bit-CPU-Schematic](https://github.com/Rouvik/My-8-Bit-CPU/blob/main/Images/Circuit.png?raw=true)

### Where to add the `MicroInstruction_PROM.txt` and `Assembled hex`:
![MILoad.png](https://github.com/Rouvik/My-8-Bit-CPU/blob/main/Images/MI_And_Prog_Load.png?raw=true)

### Brief image based hardware explanation:
![Expl.png](https://github.com/Rouvik/My-8-Bit-CPU/blob/main/Images/Expl.png?raw=true)


## Contact:
[majirouvik@gmail.com](mailto:majirouvik@gmail.com)

Created by Rouvik Maji 29th April, 2023 with ♥️
