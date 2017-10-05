ECE 250 ASSEMBLER/SIMULATOR
---------------------------

We have provided a simple assembler and simulator for the Duke250/16.
Currently, these tools have only been tested on Linux x86 systems, e.g.
teer*.oit.duke.edu.

I. COMPILING

To compile the simulator and assembler, type 'make'.  If successful, you will
have executables 'asm' and 'sim' in your current directory afterwards.

II. ASSEMBLING

The assembler takes one argument, which is the filename of an assembly-
language program.  It writes three files: a memory initialization file (MIF)
for the simulator (extension .sim), a MIF for the instruction memory in Logisim (.imem.lgsim) and a MIF for the data memory in Logisim (.dmem.lgsim).

To assemble the test program that is included, type './asm simple.s'.

You can also add the -v flag to the assembler to output debug information,
including the symbol table.

Please note that the program needs to have a ".text" header marking the beginning of the instructions. A ".data" header is also necessary to mark the beginning of the static data section. In case of doubt, look at the organization of the included sample program. 

III. SIMULATING

The simulator is a very fast functional simulator.  It does not model the
microarchitectural details of the Duke250/16.  It takes one argument, which
is the filename of an assembled program.

To simulate the test program, type './sim simple.sim' after assembling
simple.s.

You can also add the -v flag to print the dynamic instruction trace, along
with the values of all registers every instruction.  Adding the -n flag
will print the number of dynamic instructions executed at the end of the
simulation.
