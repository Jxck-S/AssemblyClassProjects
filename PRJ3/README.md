# Tiny Virtual Machine

Through the Tiny Virtual Machine simulation, one mimics the behavior of a computer by reading files that contain instructions and executing those instructions based on defined opcodes and memory addresses.

| OPcode | Mnemonic | Meaning |
| --- | --- | --- |
| 01 | LOAD X | Loads content of Address X into AC |
| 02 | ADD X | Adds value in AC at Address X into AC |
| 03 | STORE X | Stores contents of Address X into AC |
| 04 | SUBT X | Subtracts value in AC at Address X into AC |
| 05 | IN X | Requests input from user |
| 06 | OUT X | Prints value from AC |
| 07 | END | Ends program |
| 08 | JMP X | Jumps to Address X |
| 09 | SKIPZ | Skips the next instruction |

## Assignment: Tiny Harvard Architecture ISA

**Author:** Dylan Becraft & Jack Sweeney

**School:** University of Central Florida

**Professor:** Euripides Montagne

**Class:** CGS 3269, Computer Architecture

**Due date:** November 28, 2023

**Language:** C

**To Compile:** `gcc -o tinyvm tinyvm.c`

**To Execute:**
- Linux: `./tinyvm myelf.txt`
- Windows: `tinyvm.exe myelf.txt`

**When:** `myelf.txt` must be a txt file that contains opcodes in number pairs, can be another filename

**Notes:**

The program uses dynamic allocation for the size of the array it is not static, instruction array size is based on number of instructions. And the data array/memory size is based on 0- highest data location address used. So using lower address numbers if more beneficial, using unnecessarily higher numbers will cause it to use more memory.

The `output.txt` I provided is from inputting 5 and 5 for input, using my own `myelf.txt` I created.

The program accepts a second argument `-d` after the input text argument to enable debugging mode.