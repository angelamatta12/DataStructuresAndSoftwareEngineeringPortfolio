/*
 * Project 1
 * EECS 370 LC-2K Instruction-level simulator
 *
 * Make sure to NOT modify printState or any of the associated functions
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// DO NOT CHANGE THE FOLLOWING DEFINITIONS

// Machine Definitions
#define MEMORYSIZE 65536 /* maximum number of words in memory (maximum number of lines in a given file)*/
#define NUMREGS 8        /*total number of machine registers [0,7]*/
#define BITMASKOPCODE 0x1FFFFFF
#define BITMASKA 0x003FFFFF
#define BITMASKB 0x7FFFF
#define BITMASKDESTREG 0b111
#define BITMASKOFFSETFIELD 0xFFFF
// File Definitions
#define MAXLINELENGTH 1000 /* MAXLINELENGTH is the max number of characters we read */

typedef struct
    stateStruct
{
    int pc;
    int mem[MEMORYSIZE];
    int reg[NUMREGS];
    int numMemory;
} stateType;

void printState(stateType *);

static inline int convertNum(int32_t);

int main(int argc, char **argv)
{
    char line[MAXLINELENGTH];
    stateType state;
    FILE *filePtr;

    if (argc != 2)
    {
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL)
    {
        printf("error: can't open file %s , please ensure you are providing the correct path", argv[1]);
        perror("fopen");
        exit(1);
    }

    /* read the entire machine-code file into memory */
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; ++state.numMemory)
    {
        if (sscanf(line, "%d", state.mem + state.numMemory) != 1)
        {
            printf("error in reading address  %d\n. Please ensure you are providing a machine code file.", state.numMemory);
            perror("sscanf");
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }

    // Your code starts here!
    state.pc=0;
    for(int i =0; i< NUMREGS;i++){
        state.reg[i]=0;
    }
    printState(&state);
    int count = 0;

    while (state.pc < state.numMemory)
    {
        int lineCode = state.mem[state.pc];
        int temp1 = lineCode;
        int opcode = (temp1 & BITMASKOPCODE)>>22;

        // depending on the instruction in question, may need to use several continue statements and alter PC
        //  default is that PC is incremented by 1 if there is no Beq or anything else

        // isolate the opcode

        // translate opcode

        // compare isolated opcode to if statements

        // idea: for the interest of saving on code: some of these fall under the same category aka add and nor, lw,sw, and beq, and halt and noop, double check
        //  how each of the bits are divided up to see if can reduce the number of if statements
        // add and nor
        if (opcode == 0b000||opcode == 0b001)
        {
            int temp2 = lineCode;
            int regA =(temp2 & BITMASKA)>>19;
            int temp3 = lineCode;
            int regB =(temp3& BITMASKB)>>16;
            int temp4 =lineCode;
            int destReg=convertNum((temp4& BITMASKDESTREG));

            //  bits 24 - 22 : opcode bits 21 - 19 : reg A bits 18 - 16 : reg B bits 15 - 3 : unused(should all be 0) bits 2 - 0 : destReg

            // add
            if (opcode == 0b000)
            {
                // 0b000	Add contents of regA with contents of regB, store results in destReg.
                state.reg[destReg] = state.reg[regA]+state.reg[regB];
            }
            else
            {
                // nor
                // 0b001	Nor contents of regA with contents of regB, store results in destReg. This is a bitwise nor; each bit is treated independently.
                state.reg[destReg] = ~((state.reg[regA] | state.reg[regB]));
            }
        }

        // lw, sw, beq
        else if (opcode == 0b010||opcode == 0b011||opcode == 0b100)
        {
            int regA =(lineCode & BITMASKA) >> 19;
            int temp3 = lineCode;
            int regB =(temp3& BITMASKB)>>16;
            int temp4 =lineCode;
            int offsetField=convertNum((temp4 & BITMASKOFFSETFIELD));

            if (opcode == 0b010)
            {
                // 0b010	lw  “Load Word”; Load regB from memory. Memory address is formed by adding offsetField with the contents of regA. Behavior is defined only for memory addresses in the range [0, 65535].
                // need to check the whole offsetfield bound error rule
                int index = (state.reg[regA]+offsetField);
                state.reg[regB]= (state.mem[index]);

            }
            else if (opcode == 0b011)
            {

                // sw
                //  0b011	“Store Word”; Store regB into memory. Memory address is formed by adding offsetField with the contents of regA. Behavior is defined only for memory addresses in the range [0, 65535].
                state.mem[(state.reg[regA]+offsetField)] =  state.reg[regB];
            }
            else
            {
                // beq
                //  0b100	“Branch if equal” If the contents of regA and regB are the same, then branch to the address PC+1+offsetField, where PC is the address of this beq instruction.
                    if(state.reg[regA]==state.reg[regB]){
                        state.pc = state.pc+1+offsetField;
                        count++;
                        printState(&state); 
                        continue;
                    }
            }
        }

        // jalr
        else if (opcode == 0b101)
        {
            int temp2 = lineCode;
            int regA =(temp2& BITMASKA)>>19;
            int temp3 = lineCode;
            int regB =(temp3& BITMASKB)>>16;

            // 0b101	“Jump and Link Register”; First store the value PC+1 into regB, where PC is the address where this jalr instruction is defined. 
                state.reg[regB]=state.pc+1;
            //Then branch (set PC) to the address contained in regA. Note that this implies if regA and regBrefer to the same register, the net effect will be jumping to PC+1.
                state.pc =state.reg[regA];
            // this is a branching cmd that alters the PC value thus use continue keyword here to start the loop all over again instead of PC++ at bottom occuring
            count++;
            printState(&state); 
            continue;
        }
        // noop
        else if (opcode == 0b111)
        {
            // do nothing
        }
        // halt
        else if (opcode == 0b110)
        {
            state.pc++;
            count++;
            break;
        }
        else
        {
            // unknown opcode error check
            exit(1);
        }

        state.pc++;
        count++;
        printState(&state); 
    }

    printf("machine halted\n");
    printf("total of %d instructions executed\n", count);
    printf("final state of machine:\n");

    printState(&state);
    // Your code ends here!

    return (0);
}

/*
 * DO NOT MODIFY ANY OF THE CODE BELOW.
 */

void printState(stateType *statePtr)
{
    int i;
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", statePtr->pc);
    printf("\tmemory:\n");
    for (i = 0; i < statePtr->numMemory; i++)
        printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    printf("\tregisters:\n");
    for (i = 0; i < NUMREGS; i++)
        printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    printf("end state\n");
}

// convert a 16-bit number into a 32-bit Linux integer
static inline int convertNum(int num)
{
    return num - ((num & (1 << 15)) ? 1 << 16 : 0);
}

/*
 * Write any helper functions that you wish down here.
 */
