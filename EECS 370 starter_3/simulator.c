/*
 * EECS 370, University of Michigan, Fall 2023
 * Project 3: LC-2K Pipeline Simulator
 * Instructions are found in the project spec: https://eecs370.github.io/project_3_spec/
 * Make sure NOT to modify printState or any of the associated functions
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Machine Definitions
#define NUMMEMORY 65536 // maximum number of data words in memory
#define NUMREGS 8       // number of machine registers

#define ADD 0
#define NOR 1
#define LW 2
#define SW 3
#define BEQ 4
#define JALR 5 // will not implemented for Project 3 :)
#define HALT 6
#define NOOP 7

const char *opcode_to_str_map[] = {
    "add",
    "nor",
    "lw",
    "sw",
    "beq",
    "jalr",
    "halt",
    "noop"};

#define NOOPINSTR (NOOP << 22)

typedef struct IFIDStruct
{
    int pcPlus1;
    int instr;
} IFIDType;

typedef struct IDEXStruct
{
    // carried from prev stage
    int pcPlus1;
    int valA;
    int valB;
    int offset;
    int instr;
} IDEXType;

typedef struct EXMEMStruct
{
    int branchTarget;
    int eq;
    int aluResult;
    int valB;
    int instr;
} EXMEMType;

typedef struct MEMWBStruct
{
    int writeData;
    int instr;
} MEMWBType;

typedef struct WBENDStruct
{
    int writeData;
    int instr;
} WBENDType;

typedef struct stateStruct
{
    int pc;
    int instrMem[NUMMEMORY];
    int dataMem[NUMMEMORY];
    int reg[NUMREGS];
    unsigned int numMemory;
    IFIDType IFID;
    IDEXType IDEX;
    EXMEMType EXMEM;
    MEMWBType MEMWB;
    WBENDType WBEND;
    unsigned int cycles; // number of cycles run so far
} stateType;

static inline int opcode(int instruction)
{
    return instruction >> 22;
}

static inline int field0(int instruction)
{
    return (instruction >> 19) & 0x7;
}

static inline int field1(int instruction)
{
    return (instruction >> 16) & 0x7;
}

static inline int field2(int instruction)
{
    return instruction & 0xFFFF;
}

// this is for converting the offset to its actual value
//  convert a 16-bit number into a 32-bit Linux integer
static inline int convertNum(int num)
{
    return num - ((num & (1 << 15)) ? 1 << 16 : 0);
}

void printState(stateType *);
void printInstruction(int);
void readMachineCode(stateType *, char *);

int main(int argc, char *argv[])
{

    /* Declare state and newState.
       Note these have static lifetime so that instrMem and
       dataMem are not allocated on the stack. */

    static stateType state, newState;

    if (argc != 2)
    {
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    readMachineCode(&state, argv[1]);

    // Initialize state here

    state.pc = 0;
    state.IFID.instr = NOOPINSTR;
    state.IDEX.instr = NOOPINSTR;
    state.MEMWB.instr = NOOPINSTR;
    state.EXMEM.instr = NOOPINSTR;
    state.WBEND.instr = NOOPINSTR;

    newState = state;

    // state -> prev cycle
    // newState-> current cycle

    // mem is split into data and inst
    // inst for fetching no editing
    // data should be changed for lw and sw

    // init:
    //  instr  vars of all pipeline structs to noop

    // ok this makes sense now

    // when I read in the 1st inst -> goes into new state and state

    // save the results in the IF data type

    while (opcode(state.MEMWB.instr) != HALT)
    {

        printState(&state);

        newState.cycles += 1;

        // A figure out which stage we are in for the current inst

        // B execute the stage in question

        // C update the stage of that inst going on

        // D continue this for each inst until that inst is completed (WB stage)

        // implement without forwarding first

        // then implement with forwarding

        // possible cases for forwarding:

        /* ---------------------- IF stage --------------------- */

        // fetch the instruction

        newState.IFID.instr = state.instrMem[state.pc];
        newState.IFID.pcPlus1 = state.pc + 1;

        /* ---------------------- ID stage --------------------- */

        // decode the instruction
        newState.IDEX.pcPlus1 = state.IFID.pcPlus1;

        newState.IDEX.instr = state.IFID.instr;

        // offset/destReg for add/nor
        // calcing offset here

        newState.IDEX.offset = convertNum(field2(state.IFID.instr));

        // reg A
        newState.IDEX.valA = state.reg[field0(state.IFID.instr)];

        // reg B
        newState.IDEX.valB = state.reg[field1(state.IFID.instr)];

        // check stall first IFID and what currently checking

        // then data forwarding

        if (opcode(state.IDEX.instr) == LW)
        {
            if (opcode(state.IFID.instr) != HALT && opcode(state.IFID.instr) != NOOP &&
                (field0(state.IFID.instr) == field1(state.IDEX.instr)))
            {
                newState.IFID.instr = state.IFID.instr;
                newState.IFID.pcPlus1 = state.IFID.pcPlus1;
                (newState.pc)--;
                newState.IDEX.instr = NOOPINSTR;
            }

            else if (opcode(state.IFID.instr) != HALT && opcode(state.IFID.instr) != NOOP &&
                     (opcode(state.IFID.instr) != LW && field1(state.IFID.instr) == field1(state.IDEX.instr)))
            {

                newState.IFID.instr = state.IFID.instr;
                newState.IFID.pcPlus1 = state.IFID.pcPlus1;
                (newState.pc)--;
                newState.IDEX.instr = NOOPINSTR;
            }
        }

        int valA4INST = state.IDEX.valA;
        int valB4INST = state.IDEX.valB;

        int valEXMEM_A = state.IDEX.valA;
        int valEXMEM_B = state.IDEX.valB;

        int valMEMWB_A = state.IDEX.valA;
        int valMEMWB_B = state.IDEX.valB;

        int valWBEND_A = state.IDEX.valA;
        int valWBEND_B = state.IDEX.valB;

        int EXMEMopcode = opcode(state.EXMEM.instr);
        int MEMWBopcode = opcode(state.MEMWB.instr);
        int WBENDopcode = opcode(state.WBEND.instr);

        // check if destReg == regA for all instr
        // populating forwarding from exmem

        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP &&
            field0(state.IDEX.instr) == field2(state.EXMEM.instr) &&
            ((EXMEMopcode == ADD) || EXMEMopcode == NOR))
        {
            valEXMEM_A = state.EXMEM.aluResult;
        }

        // check if destReg == regB for all instr except LW
        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP &&
            opcode(state.IDEX.instr) != LW &&
            field1(state.IDEX.instr) == field2(state.EXMEM.instr) && ((EXMEMopcode == ADD) || EXMEMopcode == NOR))
        {
            valEXMEM_B = state.EXMEM.aluResult;
        }

        // forwarding from memwb
        // check if destReg(regB) == regA
        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP &&
            field0(state.IDEX.instr) == field1(state.MEMWB.instr) && MEMWBopcode == LW)
        {

            valMEMWB_A = state.MEMWB.writeData;
        }

        // check if destReg(regB) == regB for all instr except LW
        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP &&
            opcode(state.IDEX.instr) != LW &&
            field1(state.IDEX.instr) == field1(state.MEMWB.instr) && MEMWBopcode == LW)
        {
            valMEMWB_B = state.MEMWB.writeData;
        }

        // check if destReg == regA for all instr
        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP &&
            field0(state.IDEX.instr) == field2(state.MEMWB.instr) && (MEMWBopcode == ADD || MEMWBopcode == NOR))
        {
            valMEMWB_A = state.MEMWB.writeData;
        }

        // check if destReg == regB for all instr except LW
        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP && opcode(state.IDEX.instr) != LW &&
            field1(state.IDEX.instr) == field2(state.MEMWB.instr) && (MEMWBopcode == ADD || MEMWBopcode == NOR))
        {
            valMEMWB_B = state.MEMWB.writeData;
        }

        // forwarding for wbend

        // check if destReg(regB) == regA
        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP &&
            field0(state.IDEX.instr) == field1(state.WBEND.instr) && (WBENDopcode == LW))
        {
            valWBEND_A = state.WBEND.writeData;
        }

        // check if destReg(regB) == regB for all instr except LW
        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP && opcode(state.IDEX.instr) != LW && field1(state.IDEX.instr) == field1(state.WBEND.instr) && (WBENDopcode == LW))
        {
            valWBEND_B = state.WBEND.writeData;
        }

        // check if destReg == regA for all instr
        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP &&
            field0(state.IDEX.instr) == field2(state.WBEND.instr) &&
            (WBENDopcode == ADD || WBENDopcode == NOR))
        {
            valWBEND_A = state.WBEND.writeData;
        }

        // check if destReg == regB for all instr except LW
        if (opcode(state.IDEX.instr) != HALT && opcode(state.IDEX.instr) != NOOP && opcode(state.IDEX.instr) != LW && field1(state.IDEX.instr) == field2(state.WBEND.instr) &&
            (WBENDopcode == ADD || WBENDopcode == NOR))
        {
            valWBEND_B = state.WBEND.writeData;
        }

        // highest priority to lowest priority
        // checking if WBEND alters src for IDEX

        /* ---------------------- EX stage --------------------- */

        /// check the opcode for this part
        // ALU result

        //  value of reg B
        // check if should change to forwarded data

        if (valEXMEM_A != state.IDEX.valA)
        {
            valA4INST = valEXMEM_A;
        }
        else if (valMEMWB_A != state.IDEX.valA)
        {
            valA4INST = valMEMWB_A;
        }

        else if (valWBEND_A != state.IDEX.valA)
        {
            valA4INST = valWBEND_A;
        }

        if (valEXMEM_B != state.IDEX.valB)
        {
            valB4INST = valEXMEM_B;
        }
        else if (valMEMWB_B != state.IDEX.valB)
        {
            valB4INST = valMEMWB_B;
        }
        else if (valWBEND_A != state.IDEX.valA || valWBEND_B != state.IDEX.valB)
        {
            valB4INST = valWBEND_B;
        }

        //   if (valEXMEM_A != state.IDEX.valA || valEXMEM_B != state.IDEX.valB)
        //         {
        //             valB4INST = valEXMEM_B;
        //             valA4INST = valEXMEM_A;
        //         }
        //         else if (valMEMWB_A != state.IDEX.valA || valMEMWB_B != state.IDEX.valB)
        //         {
        //             valB4INST = valMEMWB_B;
        //             valA4INST = valMEMWB_A;
        //         }
        //         else if (valWBEND_A != state.IDEX.valA || valWBEND_B != state.IDEX.valB)
        //         {
        //             valB4INST = valWBEND_B;
        //             valA4INST = valWBEND_A;
        //         }

        newState.EXMEM.valB = valB4INST;

        // instruction
        newState.EXMEM.instr = state.IDEX.instr;

        // PC + 1 + Offset
        newState.EXMEM.branchTarget = state.IDEX.pcPlus1 + state.IDEX.offset;

        // ALU checking if the values passed into it are equal, need to do it based on inst.
        // what is passed into the ALU for the second val is based on inst could be B or offset

        // execute the instruction based on what the inst opcode is

        // check what opcode it is

        // execute the stuff that you are supposed to

        /// DONT FORGET TO SET THE PC FOR NEW STATE BASED ON WHAT HAPPENS HERE,
        // IF NOT BEQ -> SET TO PC + 1 FROM PIPELINE

        switch (opcode(state.IDEX.instr))
        {
        case ADD:
            // add and store in another reg
            newState.EXMEM.aluResult = valA4INST + valB4INST;
            // newState.reg[newState.IDEX.offset] = newState.EXMEM.aluResult;
            newState.EXMEM.eq = valA4INST == valB4INST;
            newState.pc++;
            break;
        case NOR:
            // nor and store in another reg
            newState.EXMEM.aluResult = ~(valA4INST | valB4INST);
            // newState.reg[ newState.IDEX.offset] = newState.EXMEM.aluResult;
            newState.EXMEM.eq = valA4INST == valB4INST;
            newState.pc++;
            break;
        case LW:
            // find address in memory we are grabbing from and store in reg B
            newState.EXMEM.aluResult = valA4INST + state.IDEX.offset;
            // newState.reg[ newState.IDEX.valA + newState.IDEX.offset] = state.dataMem[newState.EXMEM.aluResult];
            newState.EXMEM.eq = valA4INST == state.IDEX.offset;
            newState.pc++;
            break;
        case SW:
            // find address in memory we are storing into from reg B
            // do I set eq here too ?? CHECK NEW CHANGE HERE
            newState.EXMEM.eq = valA4INST == state.IDEX.offset;
            newState.EXMEM.aluResult = valA4INST + state.IDEX.offset;
            // newState.dataMem[newState.EXMEM.aluResult] = newState.EXMEM.valB;
            newState.pc++;
            break;
        case BEQ:
            // check if set the PC here !!!
            //  check if the contents are equal and set pc if they are
            newState.EXMEM.eq = valB4INST == valA4INST;
            // CHECK here
            newState.pc++;
            break;
            // set nothing
        case HALT:
        case NOOP:
            newState.pc++;
            break;
        default:
            //  printf(".fill %d", opcode(state.EXMEM.instr));
            // return;
            break;
        }

        /* --------------------- MEM stage --------------------- */

        // fetch/storing into  memory
        newState.MEMWB.instr = state.EXMEM.instr;
        // for register writing, thing we want to put into the register file aka the ALU result

        // SW storing into memory,LW grabbing from memory to put into the writeData, BEQ take branch

        if (opcode(state.EXMEM.instr) == SW)
        {
            newState.dataMem[state.EXMEM.aluResult] = state.EXMEM.valB;
        }
        else if (opcode(state.EXMEM.instr) == BEQ)
        {

            //  have him also check if this is what I should use for the eq
            if (state.EXMEM.eq)
            {
                newState.pc = state.EXMEM.branchTarget;

                // set IDEX and IFID to noop
                // what is in the IF stage
                // what is in the ID stage
                // what is in the EX stage

                // all need to be nooped

                newState.IFID.instr = NOOPINSTR;
                newState.IDEX.instr = NOOPINSTR;
                newState.EXMEM.instr = NOOPINSTR;
            }
        }

        if (opcode(state.EXMEM.instr) == LW)
        {
            newState.MEMWB.writeData = newState.dataMem[state.EXMEM.aluResult];
        }
        else
        {
            newState.MEMWB.writeData = state.EXMEM.aluResult;
        }

        /* ---------------------- WB stage --------------------- */

        if (opcode(state.MEMWB.instr) == ADD || opcode(state.MEMWB.instr) == NOR)
        {
            newState.reg[field2(state.MEMWB.instr)] = state.MEMWB.writeData;
        }
        else if (opcode(state.MEMWB.instr) == LW)
        {
            newState.reg[field1(state.MEMWB.instr)] = state.MEMWB.writeData;
        }

        // putting
        // for writing to the register file for ADD, NOR, LW
        newState.WBEND.instr = state.MEMWB.instr;
        newState.WBEND.writeData = state.MEMWB.writeData;

        /* ------------------------ END ------------------------ */
        state = newState; /* this is the last statement before end of the loop. It marks the end
        of the cycle and updates the current state with the values calculated in this cycle */
    }
    printf("Machine halted\n");
    printf("Total of %d cycles executed\n", state.cycles);
    printf("Final state of machine:\n");
    printState(&state);
}

/*
 * DO NOT MODIFY ANY OF THE CODE BELOW.
 */

void printInstruction(int instr)
{
    const char *instr_opcode_str;
    int instr_opcode = opcode(instr);
    if (ADD <= instr_opcode && instr_opcode <= NOOP)
    {
        instr_opcode_str = opcode_to_str_map[instr_opcode];
    }

    switch (instr_opcode)
    {
    case ADD:
    case NOR:
    case LW:
    case SW:
    case BEQ:
        printf("%s %d %d %d", instr_opcode_str, field0(instr), field1(instr), convertNum(field2(instr)));
        break;
    case JALR:
        printf("%s %d %d", instr_opcode_str, field0(instr), field1(instr));
        break;
    case HALT:
    case NOOP:
        printf("%s", instr_opcode_str);
        break;
    default:
        printf(".fill %d", instr);
        return;
    }
}

void printState(stateType *statePtr)
{
    printf("\n@@@\n");
    printf("state before cycle %d starts:\n", statePtr->cycles);
    printf("\tpc = %d\n", statePtr->pc);

    printf("\tdata memory:\n");
    for (int i = 0; i < statePtr->numMemory; ++i)
    {
        printf("\t\tdataMem[ %d ] = %d\n", i, statePtr->dataMem[i]);
    }
    printf("\tregisters:\n");
    for (int i = 0; i < NUMREGS; ++i)
    {
        printf("\t\treg[ %d ] = %d\n", i, statePtr->reg[i]);
    }

    // IF/ID
    printf("\tIF/ID pipeline register:\n");
    printf("\t\tinstruction = %d ( ", statePtr->IFID.instr);
    printInstruction(statePtr->IFID.instr);
    printf(" )\n");
    printf("\t\tpcPlus1 = %d", statePtr->IFID.pcPlus1);
    if (opcode(statePtr->IFID.instr) == NOOP)
    {
        printf(" (Don't Care)");
    }
    printf("\n");

    // ID/EX
    int idexOp = opcode(statePtr->IDEX.instr);
    printf("\tID/EX pipeline register:\n");
    printf("\t\tinstruction = %d ( ", statePtr->IDEX.instr);
    printInstruction(statePtr->IDEX.instr);
    printf(" )\n");
    printf("\t\tpcPlus1 = %d", statePtr->IDEX.pcPlus1);
    if (idexOp == NOOP)
    {
        printf(" (Don't Care)");
    }
    printf("\n");
    printf("\t\treadRegA = %d", statePtr->IDEX.valA);
    if (idexOp >= HALT || idexOp < 0)
    {
        printf(" (Don't Care)");
    }
    printf("\n");
    printf("\t\treadRegB = %d", statePtr->IDEX.valB);
    if (idexOp == LW || idexOp > BEQ || idexOp < 0)
    {
        printf(" (Don't Care)");
    }
    printf("\n");
    printf("\t\toffset = %d", statePtr->IDEX.offset);
    if (idexOp != LW && idexOp != SW && idexOp != BEQ)
    {
        printf(" (Don't Care)");
    }
    printf("\n");

    // EX/MEM
    int exmemOp = opcode(statePtr->EXMEM.instr);
    printf("\tEX/MEM pipeline register:\n");
    printf("\t\tinstruction = %d ( ", statePtr->EXMEM.instr);
    printInstruction(statePtr->EXMEM.instr);
    printf(" )\n");
    printf("\t\tbranchTarget %d", statePtr->EXMEM.branchTarget);
    if (exmemOp != BEQ)
    {
        printf(" (Don't Care)");
    }
    printf("\n");
    printf("\t\teq ? %s", (statePtr->EXMEM.eq ? "True" : "False"));
    if (exmemOp != BEQ)
    {
        printf(" (Don't Care)");
    }
    printf("\n");
    printf("\t\taluResult = %d", statePtr->EXMEM.aluResult);
    if (exmemOp > SW || exmemOp < 0)
    {
        printf(" (Don't Care)");
    }
    printf("\n");
    printf("\t\treadRegB = %d", statePtr->EXMEM.valB);
    if (exmemOp != SW)
    {
        printf(" (Don't Care)");
    }
    printf("\n");

    // MEM/WB
    int memwbOp = opcode(statePtr->MEMWB.instr);
    printf("\tMEM/WB pipeline register:\n");
    printf("\t\tinstruction = %d ( ", statePtr->MEMWB.instr);
    printInstruction(statePtr->MEMWB.instr);
    printf(" )\n");
    printf("\t\twriteData = %d", statePtr->MEMWB.writeData);
    if (memwbOp >= SW || memwbOp < 0)
    {
        printf(" (Don't Care)");
    }
    printf("\n");

    // WB/END
    int wbendOp = opcode(statePtr->WBEND.instr);
    printf("\tWB/END pipeline register:\n");
    printf("\t\tinstruction = %d ( ", statePtr->WBEND.instr);
    printInstruction(statePtr->WBEND.instr);
    printf(" )\n");
    printf("\t\twriteData = %d", statePtr->WBEND.writeData);
    if (wbendOp >= SW || wbendOp < 0)
    {
        printf(" (Don't Care)");
    }
    printf("\n");

    printf("end state\n");
    fflush(stdout);
}

// File
#define MAXLINELENGTH 1000 // MAXLINELENGTH is the max number of characters we read

void readMachineCode(stateType *state, char *filename)
{
    char line[MAXLINELENGTH];
    FILE *filePtr = fopen(filename, "r");
    if (filePtr == NULL)
    {
        printf("error: can't open file %s", filename);
        exit(1);
    }

    printf("instruction memory:\n");
    for (state->numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL; ++state->numMemory)
    {
        if (sscanf(line, "%d", state->instrMem + state->numMemory) != 1)
        {
            printf("error in reading address %d\n", state->numMemory);
            exit(1);
        }
        printf("\tinstrMem[ %d ]\t= 0x%08x\t= %d\t= ", state->numMemory,
               state->instrMem[state->numMemory], state->instrMem[state->numMemory]);
        printInstruction(state->dataMem[state->numMemory] = state->instrMem[state->numMemory]);
        printf("\n");
    }
}
