/**
 * Project 1
 * Assembler code fragment for LC-2K
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Every LC2K file will contain less than 1000 lines of assembly.
#define MAXLINELENGTH 1000
#define INT_MAX 2147483647
#define offSetMask 0xFFFF

// this is for when a label is used in place of a register or an offset field

int findLabelValue(char labels[1000][32], char *reg, size_t arraySize)
{

    // TODO
    // Use of undefined labels
    // implement in the linear search function
   

   for(int i = 0; i< arraySize; i++){

        if (strcmp(labels[i], reg) == 0)
        {
            return i;
        }
      
    }

    exit(1);
};

int findLabelDupe(char labels[1000][32], char *label, size_t arraySize)
{
    int temp = INT_MAX;

    // TODO
    // Use of undefined labels
    // implement in the linear search function
    for (int i = 0; i < arraySize; i++)
    {

        if (strcmp(labels[i], label) == 0)
        {
            return i;
        }
    }

    if (temp == INT_MAX)
    {
        exit(1);
    }
    return INT_MAX;
};

void checkRegisterError(char *reg)
{

    // TODO
    // function,since need this in every if, some do have certain registers,some dont depends on type
    // Non-integer register arguments
    // Registers outside the range [0, 7]

    if ((atoi(reg) < 0 || atoi(reg) > 7))
    {
        exit(1);
    }
};

void checkOffsetFieldBounds(int offSet)
{

    // make sure the offset fits in -32768 to 32767 , is 2's compliment, just do a direct comparison

    if (offSet < -32768 || offSet > 32767)
    {
        exit(1);
    }
};


int readAndParse(FILE *, char *, char *, char *, char *, char *);
static void checkForBlankLinesInCode(FILE *inFilePtr);
static inline int isNumber(char *);

int main(int argc, char **argv)
{
    struct labelLocPairs
    {
        char label[32];
        int lineNum;
    };

    char *inFileString, *outFileString;
    FILE *inFilePtr, *outFilePtr;
    char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH],
        arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

    if (argc != 3)
    {
        printf("error: usage: %s <assembly-code-file> <machine-code-file>\n",
               argv[0]);
        exit(1);
    }

    inFileString = argv[1];
    outFileString = argv[2];

    inFilePtr = fopen(inFileString, "r");
    if (inFilePtr == NULL)
    {
        printf("error in opening %s\n", inFileString);
        exit(1);
    }

    // Check for blank lines in the middle of the code.
    checkForBlankLinesInCode(inFilePtr);

    outFilePtr = fopen(outFileString, "w");
    if (outFilePtr == NULL)
    {
        printf("error in opening %s\n", outFileString);
        exit(1);
    }

    // what to do for each line:

    // translate into machine code

    // depending on the type of command, this may look different.

    // each command has a specific type, which maps parts to certain bits

    // grab line
    // /* here is an example for how to use readAndParse to read a line from
    //     inFilePtr */
    // if (! readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) ) {
    //     /* reached end of file */

    // }

    // make sure ptr actually moves, check if it accounts for if there are less things because some commands have less stuff

    // next

    // check if there is label,

    // yes encode it,using appropriate bits

    // may need to check opcode first

    // check each section, based on opcode, each is mapped to a certian number of bits

    // convert each into binary

    // then convert to decimal
    // NOTE: beaumont stated that C would do this automatically... how ??

    // NOTE: Apparently there is some loop stuff that happens with beq in the spec, ask about how that affects the translations!!

    // extra things:

    // handling labels, in spec says need 2 passes, 1 for translating labels to their addresses (basically find which line is the definition, thats the number you need.)
    // for lw/sw just use the line number, for beq line number - 1 = PC +1 + offset NOTE: need to code 2's compliment here to translate this into binary!!!!

    // then translating the lines as discussed in lecture

    /// implementing without checking label stuff first

    // what do I need still:

    // 4. .fill, sure the opcode is stored in its usual place but what about the value next to it ??

    // need 2 arrays, one for binary numbers to be printed, one for label pairs, need to create struct for that one

    // printing section:
    //  iterate over array and print all values, may take a while...

    // note: need to double check if should use int there...
    char labelSet[1000][32];


    int PC = 0;

    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) == 1)
    {

        // error stuff
        // Duplicate definition of labels
        // implement in the preprocessing section
        // TODO: make sure this works

        if (label[0] != '\0')
        {
            for(int i = 0; i<  sizeof(labelSet) / sizeof(labelSet[0]); i++){
            if (strcmp(labelSet[i], label) == 0)
            {
            exit(1);
            }
            }
            char temp[32];
            strcpy(temp,label);
            for(int i = 0; i< 32; i++){
            labelSet[PC][i] = temp[i];
            }
        }
        PC++;
    }

    // stuff for beq -> PC+1+offset = line number label established at
    // offset = line number label established at - 1 -PC

    // for lw/sw-> just use value that is there

    // stuff for preprocessing:

    // rewind the doc

    rewind(inFilePtr);

    PC = 0;

    while (readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) == 1)
    {

        // error stuff

        // need to see where would do this
        // offsetFields that don’t fit in 16-bit, 2’s complement number with a range of -32768 to 32767

        //, read in data until the end of the file, save the data in pieces to the following variables

        // part 1

        // NOTE: ALL CAN HAVE LABELS, lw/sw having a label for the last field is different than beq having it for the last field, see notes above

        // A: identify opcode

        if (!strcmp(opcode, "add"))
        {
            /* do whatever you need to do for opcode "add" */

            // opcode, field0, field1, and field2 are required fields:
            // field0 is a register (regA)
            // field1 is a register (regB)
            // field2 is a register (destReg)

            if (isNumber(arg0) && isNumber(arg1))
            {
                checkRegisterError(arg0);
                checkRegisterError(arg1);
                checkRegisterError(arg2);
            }
            else
            {
                exit(1);
            }
            int opCodeBin = 0b000;
            int regA = atoi(arg0);
            int regB = atoi(arg1);
            int destReg = atoi(arg2);

            int solution;

            // shift 3 then or twice
            solution = opCodeBin << 3;
            // use bitwise or
            solution = (solution | regA);

            solution = solution << 3;
            solution = (solution | regB);

            solution = solution << 16;

            solution = (solution | destReg);
            fprintf(outFilePtr, "%d\n", (solution));
        }

        else if (!strcmp(opcode, "nor"))
        {
            /* do whatever you need to do for opcode "add" */

            //     opcode, field0, field1, and field2 are required fields:
            // field0 is a register (regA)
            // field1 is a register (regB)
            // field2 is a register (destReg)
            if (isNumber(arg0) && isNumber(arg1))
            {
                checkRegisterError((arg0));
                checkRegisterError((arg1));
                checkRegisterError(arg2);
            }
            else
            {
                exit(1);
            }
            int opCodeBin = 0b001;
            int regA = atoi(arg0);
            int regB = atoi(arg1);
            int destReg = atoi(arg2);

            int solution;

            // shift 3 then or twice
            solution = opCodeBin << 3;
            // use bitwise or
            solution = (solution | regA);

            solution = solution << 3;
            solution = (solution | regB);

            solution = solution << 16;

            solution = (solution | destReg);
            fprintf(outFilePtr, "%d\n", (solution));
        }

        else if (!strcmp(opcode, "lw"))
        {
            /* do whatever you need to do for opcode "add" */

            //     opcode , field0 , field1 and field2 are required fields:
            // field0 is a register (regA)
            // field1 is a register (regB)
            // field2 is either a numeric address, or a symbolic address (represented by a label)
            if (isNumber(arg0) && isNumber(arg1))
            {
                checkRegisterError((arg0));
                checkRegisterError((arg1));
            }
            else
            {
                exit(1);
            }
            int opCodeBin = 0b010;
            int regA = atoi(arg0);
            int regB = atoi(arg1);
            int offSetField;

            if (isNumber(arg2))
            {
                offSetField = atoi(arg2);
            }
            else
            {
                offSetField = findLabelValue(labelSet, arg2, sizeof(labelSet) / sizeof(labelSet[0]));
            }
            checkOffsetFieldBounds(offSetField);

            int solution;

            // shift 3 then or twice
            solution = opCodeBin << 3;
            // use bitwise or
            solution = (solution | regA);

            solution = solution << 3;
            solution = (solution | regB);

            offSetField = (offSetField & offSetMask);

            solution = solution << 16;

            solution = (solution | offSetField);

            fprintf(outFilePtr, "%d\n", (solution));
        }

        else if (!strcmp(opcode, "sw"))
        {
            /* do whatever you need to do for opcode "add" */

            //     opcode , field0 , field1 and field2 are required fields:
            // field0 is a register (regA)
            // field1 is a register (regB)
            // field2 is either a numeric address, or a symbolic address (represented by a label)
            if (isNumber(arg0) && isNumber(arg1))
            {
                checkRegisterError(arg0);
                checkRegisterError(arg1);
            }
            else
            {
                exit(1);
            }
            int opCodeBin = 0b011;
            int regA = atoi(arg0);
            int regB = atoi(arg1);
            int offSetField;

            if (isNumber(arg2))
            {
                offSetField = atoi(arg2);
            }
            else
            {
                offSetField = findLabelValue(labelSet, arg2, sizeof(labelSet) / sizeof(labelSet[0]));
            }
            checkOffsetFieldBounds(offSetField);

            int solution;

            // shift 3 then or twice
            solution = opCodeBin << 3;
            // use bitwise or
            solution = (solution | regA);

            solution = solution << 3;
            solution = (solution | regB);

            offSetField = (offSetField & offSetMask);

            solution = solution << 16;

            solution = (solution | offSetField);

            fprintf(outFilePtr, "%d\n", (solution));
        }

        else if (!strcmp(opcode, "beq"))
        {
            /* do whatever you need to do for opcode "add" */

            //     opcode , field0 , field1 and field2 are required fields:
            // field0 is a register (regA)
            // field1 is a register (regB)
            // field2 is either a numeric address, or a symbolic address (represented by a label)
            if (isNumber(arg0) && isNumber(arg1))
            {
                checkRegisterError(arg0);
                checkRegisterError(arg1);
            }
            else
            {
                exit(1);
            }
            int opCodeBin = 0b100;
            int regA = atoi(arg0);
            int regB = atoi(arg1);
            int offSetField;

            if (isNumber(arg2))
            {
                offSetField = atoi(arg2);
            }
            else
            {
                // offset = line number label established at - 1 -PC
                offSetField = findLabelValue(labelSet, arg2, sizeof(labelSet) / sizeof(labelSet[0])) - 1 - PC;
            }

            checkOffsetFieldBounds(offSetField);

            int solution;

            // shift 3 then or twice
            solution = opCodeBin << 3;
            // use bitwise or
            solution = (solution | regA);

            solution = solution << 3;
            solution = (solution | regB);

            offSetField = (offSetField & offSetMask);

            solution = solution << 16;

            solution = (solution | offSetField);

            fprintf(outFilePtr, "%d\n", (solution));
        }

        else if (!strcmp(opcode, "jalr"))
        {
            /* do whatever you need to do for opcode "add" */
            // opcode, field0, and field1 are required fields:
            // field0 is a register (regA)
            // field1 is a register (regB)

            // bits 24 - 22 : opcode
            //  bits 21 - 19 : reg A
            //  bits 18 - 16 : reg B
            //  bits 15 - 0 : unused(should all be 0)
            if (isNumber(arg0) && isNumber(arg1))
            {
                checkRegisterError(arg0);
                checkRegisterError(arg1);
            }
            else
            {
                exit(1);
            }

            int opCodeBin = 0b101;
            int regA = atoi(arg0);
            int regB = atoi(arg1);

            int solution;

            // new question: do I need to isolate the 3 bits in question from each register before I do the bitwise or like done in lab 1 ??
            //  opcode
            //   shift by n
            // regA takes up 3 spaces
            solution = opCodeBin << 3;
            // use bitwise or
            solution = (solution | regA);

            // repeat
            // regB takes up 3 spaces
            solution = solution << 3;
            solution = (solution | regB);

            // new question :
            // do I need to shift it one more time to get the zeros at the end ??

            fprintf(outFilePtr, "%d\n", (solution << 16));
        }

        else if (!strcmp(opcode, "halt"))
        {
            fprintf(outFilePtr, "%d\n", (0b110 << 22));
        }

        else if (!strcmp(opcode, "noop"))
        {
            fprintf(outFilePtr, "%d\n", (0b111 << 22));
        }

        else if (!strcmp(opcode, ".fill"))
        {

            if (isNumber(arg0))
            {
                fprintf(outFilePtr, "%d\n", atoi(arg0));
            }
            else
            {

                // call the linear search algorithm used for when label is used in place of register
                fprintf(outFilePtr, "%d\n", findLabelValue(labelSet, arg0, sizeof(labelSet) / sizeof(labelSet[0])));
            }
        }

        else
        {
            // Unrecognized opcodes error
            exit(1);
        }

        // populate the array here ??

        PC++;
    }

    // B: based on opcode translate the appropriate stuff aka only some of these will be used, some wont. note: character pointers used for all, find a way to translate those
    //  into numbers, into binary

    // part 2

    // implement the loop/address stuff with lw/sw

    // part 3 error checking as stated in spec

    // /* here is an example for how to use readAndParse to read a line from
    //     inFilePtr */
    // if (! readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2) ) {
    //     /* reached end of file */

    // }

    // /* this is how to rewind the file ptr so that you start reading from the
    //     beginning of the file */
    // rewind(inFilePtr);

    // /* after doing a readAndParse, you may want to do the following to test the
    //     opcode */

    // if (!strcmp(opcode, "add")) {
    //     /* do whatever you need to do for opcode "add" */

    // }

    // print section

    return (0);
}

// Returns non-zero if the line contains only whitespace.
static int lineIsBlank(char *line)
{
    char whitespace[4] = {'\t', '\n', '\r', ' '};
    int nonempty_line = 0;
    for (int line_idx = 0; line_idx < strlen(line); ++line_idx)
    {
        int line_char_is_whitespace = 0;
        for (int whitespace_idx = 0; whitespace_idx < 4; ++whitespace_idx)
        {
            if (line[line_idx] == whitespace[whitespace_idx])
            {
                line_char_is_whitespace = 1;
                break;
            }
        }
        if (!line_char_is_whitespace)
        {
            nonempty_line = 1;
            break;
        }
    }
    return !nonempty_line;
}

// Exits 2 if file contains an empty line anywhere other than at the end of the file.
// Note calling this function rewinds inFilePtr.
static void checkForBlankLinesInCode(FILE *inFilePtr)
{
    char line[MAXLINELENGTH];
    int blank_line_encountered = 0;
    int address_of_blank_line = 0;
    rewind(inFilePtr);

    for (int address = 0; fgets(line, MAXLINELENGTH, inFilePtr) != NULL; ++address)
    {
        // Check for line too long
        if (strlen(line) >= MAXLINELENGTH - 1)
        {
            printf("error: line too long\n");
            exit(1);
        }

        // Check for blank line.
        if (lineIsBlank(line))
        {
            if (!blank_line_encountered)
            {
                blank_line_encountered = 1;
                address_of_blank_line = address;
            }
        }
        else
        {
            if (blank_line_encountered)
            {
                printf("Invalid Assembly: Empty line at address %d\n", address_of_blank_line);
                exit(2);
            }
        }
    }
    rewind(inFilePtr);
}

/*
 * NOTE: The code defined below is not to be modifed as it is implimented correctly.
 */

/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if all went well
 *
 * exit(1) if line is too long.
 */
int readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
                 char *arg1, char *arg2)
{
    char line[MAXLINELENGTH];
    char *ptr = line;

    /* delete prior values */
    label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

    /* read the line from the assembly-language file */
    if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL)
    {
        /* reached end of file */
        return (0);
    }

    /* check for line too long */
    if (strlen(line) == MAXLINELENGTH - 1)
    {
        printf("error: line too long\n");
        exit(1);
    }

    // Ignore blank lines at the end of the file.
    if (lineIsBlank(line))
    {
        return 0;
    }

    /* is there a label? */
    ptr = line;
    if (sscanf(ptr, "%[^\t\n ]", label))
    {
        /* successfully read label; advance pointer over the label */
        ptr += strlen(label);
    }

    /*
     * Parse the rest of the line.  Would be nice to have real regular
     * expressions, but scanf will suffice.
     */
    sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]",
           opcode, arg0, arg1, arg2);

    return (1);
}

static inline int
isNumber(char *string)
{
    int num;
    char c;
    return ((sscanf(string, "%d%c", &num, &c)) == 1);
}
