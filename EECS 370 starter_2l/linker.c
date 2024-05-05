/**
 * Project 2
 * LC-2K Linker
 */

// NOTES FOR TOMORROW
//  ERROR CHECKING
// CHECK ALL ERROR CHECKING !!!! ONE OF THEM IS NOT BEHAVING CORRECTLY, MONEY IS ON PART B, HAD PROBLEMS IN PAST :(

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 500
#define MAXLINELENGTH 1000
#define MAXFILES 6
#define BITMASKISO 0b11111111111111110000000000000000
#define BITMASKTXT 0b00000000000000001111111111111111
#define INTMAX 2147483647

typedef struct FileData FileData;
typedef struct SymbolTableEntry SymbolTableEntry;
typedef struct RelocationTableEntry RelocationTableEntry;
typedef struct CombinedFiles CombinedFiles;
typedef struct Pair Pair;

struct Pair
{
	char label[7];
	unsigned int lineNum;
};

struct SymbolTableEntry
{
	char label[7];
	char location;
	unsigned int offset;
};

struct RelocationTableEntry
{
	unsigned int offset;
	char inst[7];
	char label[7];
	unsigned int file;
};

struct FileData
{
	unsigned int textSize;
	unsigned int dataSize;
	unsigned int symbolTableSize;
	unsigned int relocationTableSize;
	unsigned int textStartingLine; // in final executable
	unsigned int dataStartingLine; // in final executable
	int text[MAXSIZE];
	int data[MAXSIZE];
	SymbolTableEntry symbolTable[MAXSIZE];
	RelocationTableEntry relocTable[MAXSIZE];
};

struct CombinedFiles
{
	unsigned int textSize;
	unsigned int dataSize;
	unsigned int symbolTableSize;
	unsigned int relocationTableSize;
	int text[MAXSIZE * MAXFILES];
	int data[MAXSIZE * MAXFILES];
	SymbolTableEntry symbolTable[MAXSIZE * MAXFILES];
	RelocationTableEntry relocTable[MAXSIZE * MAXFILES];
};

int main(int argc, char *argv[])
{
	char *inFileString, *outFileString;
	FILE *inFilePtr, *outFilePtr;
	unsigned int i, j;

	if (argc <= 2)
	{
		printf("error: usage: %s <obj file> ... <output-exe-file>\n",
			   argv[0]);
		exit(1);
	}

	outFileString = argv[argc - 1];

	outFilePtr = fopen(outFileString, "w");
	if (outFilePtr == NULL)
	{
		printf("error in opening %s\n", outFileString);
		exit(1);
	}

	FileData files[MAXFILES];

	// read in all files and combine into a "master" file
	for (i = 0; i < argc - 2; i++)
	{
		inFileString = argv[i + 1];

		inFilePtr = fopen(inFileString, "r");
		printf("opening %s\n", inFileString);

		if (inFilePtr == NULL)
		{
			printf("error in opening %s\n", inFileString);
			exit(1);
		}

		char line[MAXLINELENGTH];
		unsigned int textSize, dataSize, symbolTableSize, relocationTableSize;

		// parse first line of file
		fgets(line, MAXSIZE, inFilePtr);
		sscanf(line, "%d %d %d %d",
			   &textSize, &dataSize, &symbolTableSize, &relocationTableSize);

		files[i].textSize = textSize;
		files[i].dataSize = dataSize;
		files[i].symbolTableSize = symbolTableSize;
		files[i].relocationTableSize = relocationTableSize;

		// read in text section
		int instr;
		for (j = 0; j < textSize; j++)
		{
			fgets(line, MAXLINELENGTH, inFilePtr);
			instr = strtol(line, NULL, 0);
			files[i].text[j] = instr;
		}

		// read in data section
		int data;
		for (j = 0; j < dataSize; j++)
		{
			fgets(line, MAXLINELENGTH, inFilePtr);
			data = strtol(line, NULL, 0);
			files[i].data[j] = data;
		}

		// read in the symbol table
		char label[7];
		char type;
		unsigned int addr;
		for (j = 0; j < symbolTableSize; j++)
		{
			fgets(line, MAXLINELENGTH, inFilePtr);
			sscanf(line, "%s %c %d",
				   label, &type, &addr);
			files[i].symbolTable[j].offset = addr;
			strcpy(files[i].symbolTable[j].label, label);
			files[i].symbolTable[j].location = type;
		}

		// read in relocation table
		char opcode[7];
		for (j = 0; j < relocationTableSize; j++)
		{
			fgets(line, MAXLINELENGTH, inFilePtr);
			sscanf(line, "%d %s %s",
				   &addr, opcode, label);
			files[i].relocTable[j].offset = addr;
			strcpy(files[i].relocTable[j].inst, opcode);
			strcpy(files[i].relocTable[j].label, label);
			files[i].relocTable[j].file = i;
		}
		fclose(inFilePtr);
	} // end reading files

	// *** INSERT YOUR CODE BELOW ***
	//    Begin the linking process
	//    Happy coding!!!

	CombinedFiles combined;
	int prevIterStopTXT = 0;
	int countTXT = 0;

	int prevIterStopDATA = 0;
	int countDATA = 0;

	int prevIterStopRELOC = 0;
	int countRELOC = 0;

	int prevIterStopSYM = 0;
	int countSYM = 0;

	int countSYMTABLEstrt = 0;
	int tableSYMStart[7];
	tableSYMStart[0] = 0;
	tableSYMStart[1] = INTMAX;
	tableSYMStart[2] = INTMAX;
	tableSYMStart[3] = INTMAX;
	tableSYMStart[4] = INTMAX;
	tableSYMStart[5] = INTMAX;
	tableSYMStart[6] = INTMAX;

	for (int i = 0; i < argc - 2; i++)
	{

		// add to get total data size, text size, symbol size, relocation size for the combined file
		combined.dataSize += files[i].dataSize;
		combined.textSize += files[i].textSize;
		combined.relocationTableSize += files[i].relocationTableSize;
		combined.symbolTableSize += files[i].symbolTableSize;

		int count = 0;
		// for each text section: read in the data, this is already translated into machine code
		prevIterStopTXT += files[i].textSize;
		while (countTXT < prevIterStopTXT)
		{
			combined.text[countTXT] = files[i].text[count];
			countTXT++;
			count++;
		}

		// for each data section: read in the data, this is already populated
		count = 0;
		prevIterStopDATA += files[i].dataSize;
		while (countDATA < prevIterStopDATA)
		{
			combined.data[countDATA] = files[i].data[count];
			countDATA++;
			count++;
		}

		count = 0;
		prevIterStopRELOC += files[i].relocationTableSize;
		while (countRELOC < prevIterStopRELOC)
		{
			combined.relocTable[countRELOC] = files[i].relocTable[count];
			countRELOC++;
			count++;
		}

		count = 0;
		prevIterStopSYM += files[i].symbolTableSize;
		while (countSYM < prevIterStopSYM)
		{
			combined.symbolTable[countSYM] = files[i].symbolTable[count];
			countSYM++;
			count++;
		}

		countSYMTABLEstrt++;
		tableSYMStart[countSYMTABLEstrt] = countSYM;
	}

	Pair tableSYMVals[combined.symbolTableSize];
	char tableGlobalLabels[1000][7];
	int countNumGlobal = 0;

	// handle error checking here

	for (int ill = 0; ill < combined.symbolTableSize; ill++)
	{

		// A -> check if Stack is defined somewhere -> this means that it will be a label in the table
		// And that it will have D/T as its location

		if (!strcmp(combined.symbolTable[ill].label, "Stack") && (((combined.symbolTable[ill].location) == 'D') || (combined.symbolTable[ill].location == 'T')))
		{
			exit(1);
		}

		if (combined.symbolTable[ill].location == 'U')
		{
				if(!strcmp(combined.symbolTable[ill].label, "Stack")){
					continue;
				}

			strcpy(tableSYMVals[ill].label, combined.symbolTable[ill].label);
			tableSYMVals[ill].lineNum = INTMAX;
			// add the values to the array of global labels
			strcpy(tableGlobalLabels[ill], combined.symbolTable[ill].label);
			countNumGlobal++;
		}
		else
		{

			int fileIn = 0;
			// find out what file it is in
			// loop to find out which file
			for (int jkl = (argc - 2) - 1; jkl >= 0; jkl--)
			{
				if (ill >= tableSYMStart[jkl] && tableSYMStart[jkl] != INTMAX)
				{
					fileIn = jkl;
					break;
				}
			}

			int origLine = combined.symbolTable[ill].offset;
			// next find out what line it is in the file
			// read in the location label to see what specifically it is
			//  in data section
			if (combined.symbolTable[ill].location == 'D')
			{

				origLine += combined.textSize;
				for (int imo = 0; imo < fileIn; imo++)
				{
					origLine += files[imo].dataSize;
				}
			}

			else
			{

				for (int imok = 0; imok < fileIn; imok++)
				{
					origLine += files[imok].textSize;
				}
			}

			// save in combined symbol table vals with label as a pair
			strcpy(tableSYMVals[ill].label, combined.symbolTable[ill].label);
			tableSYMVals[ill].lineNum = origLine;
		}
	}

// part C -> checking for dupe labels but for the ones that are not used 
	// loop through the combined symbol table
	int countDUPE = 0;
	//grab the label we are checking for
	for (int cc = 0; cc < combined.symbolTableSize; cc++)
	{
		countDUPE = 0;


	//check if that is a definition for that label and include in total if so 
		if((combined.symbolTable[cc].location == 'T'||combined.symbolTable[cc].location == 'D')){
			countDUPE++;
		}

		// grab all the terms that are after it
		for (int cci = cc+1; cci < combined.symbolTableSize; cci++)
		{
			//check if that is the same label we are looking for and that it is a definition 
			if(!strcmp(combined.symbolTable[cc].label,combined.symbolTable[cci].label)&&(combined.symbolTable[cci].location == 'T'||combined.symbolTable[cci].location == 'D')){
          //include in total if so 
			countDUPE++;
			}
			
			
		}
		//if there is more than one definition for that label then break 
		if(countDUPE > 1){
			exit(1);
		}

	}
	
	// keep for B, cannot have a U without a D/T, needs to be a pair
	//  B-> check that all global labels are defined, and that they are only defined once
	//   for every global label that we come accross that has location U, save it in another array,
	//   loop through the array, checking symbol vals table, if it has an entry with an actual number not -1 -> defined, else not defined

	int flag = 0;
	for(int check = 0; check < combined.symbolTableSize; check++){
		flag = 0;

		if(combined.symbolTable[check].location == 'U' && (strcmp(combined.symbolTable[check].label, "Stack"))){
			for(int checkDef = 0;checkDef < combined.symbolTableSize; checkDef++ ){
				if(!strcmp(combined.symbolTable[check].label,combined.symbolTable[checkDef].label) && (combined.symbolTable[checkDef].location != 'U')){
						flag = 1;
					
				}
			}
			if(flag == 0){
			exit(1);
		}
		}

		}

	


	////finding start of text
	// for each text section
	// textstart += prev text size
	// if first text block then 0

	// for each data section
	/// datastart += previous data size
	// if first data block then set equal to total text size

	// accessing the relocation table for each file
	for (int a = 0; a < argc - 2; a++)
	{

		// handling STACK
		// when accessing the corresponding entry in the data/text section:
		// previous file's datasize+ index/line number in the reloc table

		// ex:
		//  read no file in so 0 for prev datasize:
		// 0+0-> 0, 0+1 -> 1....
		//  read in a file(file number 1), now doing stuff to file #2
		//  prev file size+= file number 1 size
		//  0+ prev file size -> first entry in file #2, etc.

		// same even when switch to data section for symbol table
		for (int reloc = 0; reloc < files[a].relocationTableSize; reloc++)
		{

			// if stack then find out whether it is the text/data section that needs to be updated and update accordingly
			if (!strcmp(files[a].relocTable[reloc].label, "Stack"))
			{

				// set the offset to combined text size + combined data size
				int offSetSTACK = combined.dataSize + combined.textSize;

				// find the file that the entry is in
				int indexFile = files[a].relocTable[reloc].file;

				// update data section
				if (!strcmp(files[a].relocTable[reloc].inst, ".fill"))
				{


					// finding the index in which the data is in the table for the combined file
					int indFind = 0;

					for (int isi = 0; isi < indexFile; isi++)
					{
						indFind += files[isi].dataSize;
					}

					// add the offset from the reloc table entry
					indFind += files[indexFile].relocTable[reloc].offset;

					// index into the data table
					// add the offset to the data section in the combined file
					combined.data[indFind] = offSetSTACK;
				}

				// update text section
				else
				{

					// find where in the text section the relocation table entry is referring to

					int indFind = 0;

					for (int ikk = 0; ikk < indexFile; ikk++)
					{
						indFind += files[ikk].textSize;
					}

					// add the offset from the reloc table entry
					indFind += files[indexFile].relocTable[reloc].offset;

					// index into the text table
					// zero out the offset section with bitmask so the offset is set to 0
					files[indexFile].text[indFind] = (files[indexFile].text[indFind] & BITMASKISO);

					// add the offset to the amount (line number in the combined file - 1)
					combined.text[indFind] += offSetSTACK;
				}
			}

			else // either a local or global label that is not Stack
			{
				// note: this only handles local labels not global 1!

				// check if global
				// is global
				if (isupper(files[a].relocTable[reloc].label[0]))
				{

					// update data section
					if (!strcmp(files[a].relocTable[reloc].inst, ".fill"))
					{
						// find where in the data section for the combined file that we need to index
						// into to update it
						int indUsed = files[a].relocTable[reloc].file;

						// finding the index in which the data is in the table for the combined file
						int indFind = 0;
						for (int ii = 0; ii < indUsed; ii++)
						{
							indFind += files[ii].dataSize;
						}

						// add the offset from the reloc table entry
						indFind += files[indUsed].relocTable[reloc].offset;

						// loop through preprocessed data and find the value from there

						for (int is = 0; is < combined.symbolTableSize; is++)
						{
							if (!strcmp(tableSYMVals[is].label, files[a].relocTable[reloc].label) && tableSYMVals[is].lineNum != INTMAX)
							{
								combined.data[indFind] = tableSYMVals[is].lineNum;
								break;
							}
						}
					}
					else
					{

						// file where the relocation is from
						int indUsed = files[a].relocTable[reloc].file;

						// find what line in the text section of the combined file is supposed to be updated
						int indFind = 0;
						for (int fis = 0; fis < indUsed; fis++)
						{
							indFind += files[fis].textSize;
						}

						// add the offset from the reloc table entry
						indFind += files[indUsed].relocTable[reloc].offset;

						// loop through preprocessed data and find the value from there

						for (int ji = 0; ji < combined.symbolTableSize; ji++)
						{
							if (!strcmp(tableSYMVals[ji].label, files[a].relocTable[reloc].label) && tableSYMVals[ji].lineNum != INTMAX)
							{
								combined.text[indFind] = combined.text[indFind] & BITMASKISO;

								combined.text[indFind] += tableSYMVals[ji].lineNum;

								break;
							}
						}
					}
				}
				// is local
				else
				{
					// update data section
					if (!strcmp(files[a].relocTable[reloc].inst, ".fill"))
					{
						// find where in the data section for the combined file that we need to index
						// into to update it
						int indUsed = files[a].relocTable[reloc].file;

						// finding the index in which the data is in the table for the combined file
						int indFind = 0;
						for (int iff = 0; iff < indUsed; iff++)
						{
							indFind += files[iff].dataSize;
						}

						// add the offset from the reloc table entry
						indFind += files[indUsed].relocTable[reloc].offset;

						// now find where the label is defined in the old file since it would not change sections
						//  when combined aka use the symbolid address :)

						// index into the data table to get the old symbolic address aka what line number
						//  it is in the original file

						// label is defined in the data section
						if (files[indUsed].data[files[indUsed].relocTable[reloc].offset] >= files[indUsed].textSize)
						{

							// this gives me what line is being updated in the data section
							//  if I had to index into 1 array that represents the whole file

							// this is where the data we are updating is located in the combined file
							//  add text size for the combined file + data size for the files that come before the
							// data section that the definition is in  + offset from relocation
							// this is where it is defined in the combined file

							/// at the last line for the text section doing this
							int indFindNew = 0;

							// add all the text sizes and the data sizes up to the and including the file that is being used(only for text not for data, <indUsed for Data)
							indFindNew += files[indUsed].data[files[indUsed].relocTable[reloc].offset];
							indFindNew += combined.textSize;
							indFindNew -= files[indUsed].textSize;

							for (int fol = 0; fol < indUsed; fol++)
							{
								indFindNew += files[fol].dataSize;
							}

							// set the data section equal to the new line value

							combined.data[indFind] = indFindNew;
						}
						// label is defined in the text section
						else
						{

							// adding text size of each file only up to the file that the label is defined in
							// find the specific line starting from the start of that text file, that is where it is in the combined file

							int indFindNew = 0;
							indFindNew += files[indUsed].data[files[indUsed].relocTable[reloc].offset];

							for (int ilk = 0; ilk < indUsed; ilk++)
							{
								indFindNew += files[ilk].textSize;
							}

							combined.data[indFind] = indFindNew;
						}
					}
					// update text section
					else
					{

						// file where the relocation is from
						int indUsed = files[a].relocTable[reloc].file;

						// find what line in the text section of the combined file is supposed to be updated
						int indFind = 0;
						for (int foo = 0; foo < indUsed; foo++)
						{
							indFind += files[foo].textSize;
						}

						// add the offset from the reloc table entry
						indFind += files[indUsed].relocTable[reloc].offset;

						// finding where the label is being defined

						// index into the text section that is being referred to by the relocation table

						// the label is defined in the data section
						if ((files[indUsed].text[files[indUsed].relocTable[reloc].offset] & BITMASKTXT) >= files[indUsed].textSize)
						{

							int findNew = 0;
							findNew += (files[indUsed].text[files[indUsed].relocTable[reloc].offset] & BITMASKTXT);
							findNew += combined.textSize;
							findNew -= files[indUsed].textSize;

							// add the sizes of all but the last file's data sections
							for (int fo = 0; fo < indUsed; fo++)
							{
								findNew += files[fo].dataSize;
							}

							// bitmask off the new
							combined.text[indFind] = combined.text[indFind] & BITMASKISO;

							combined.text[indFind] += findNew;
						}

						// the label is defined in the text section
						else
						{

							int findNew = 0;
							findNew += (files[indUsed].text[files[indUsed].relocTable[reloc].offset] & BITMASKTXT);
							// add the sizes of all the text sections
							for (int itt = 0; itt < indUsed; itt++)
							{
								findNew += files[itt].textSize;
							}

							combined.text[indFind] = combined.text[indFind] & BITMASKISO;

							combined.text[indFind] += findNew;
						}
					}
				}
			}
		}
	}

	// printing section

	// print out the following
	// text section of file
	//  data section of file
	for (int ik = 0; ik < combined.textSize; ik++)
	{
		fprintf(outFilePtr, "%d\n", combined.text[ik]);
	}
	for (int jk = 0; jk < combined.dataSize; jk++)
	{
		fprintf(outFilePtr, "%d\n", combined.data[jk]);
	}

} // main
