/*
 * EECS 370, University of Michigan
 * Project 4: LC-2K Cache Simulator
 * Instructions are found in the project spec.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CACHE_SIZE 256
#define MAX_BLOCK_SIZE 256
#define MIN_INT -2147483648
#define MAX_INT 21474836

// **Note** this is a preprocessor macro. This is not the same as a function.
// Powers of 2 have exactly one 1 and the rest 0's, and 0 isn't a power of 2.
#define is_power_of_2(val) (val && !(val & (val - 1)))

/*
 * Accesses 1 word of memory.
 * addr is a 16-bit LC2K word address.
 * write_flag is 0 for reads and 1 for writes.
 * write_data is a word, and is only valid if write_flag is 1.
 * If write flag is 1, mem_access does: state.mem[addr] = write_data.
 * The return of mem_access is state.mem[addr].
 */
extern int mem_access(int addr, int write_flag, int write_data);

/*
 * Returns the number of times mem_access has been called.
 */
extern int get_num_mem_accesses(void);

// Use this when calling printAction. Do not modify the enumerated type below.
enum actionType
{
    cacheToProcessor,
    processorToCache,
    memoryToCache,
    cacheToMemory,
    cacheToNowhere
};

/* You may add or remove variables from these structs */
typedef struct blockStruct
{
    int data[MAX_BLOCK_SIZE];
    int dirty;
    int lruLabel;
    int tag;
    int valid;

    int currentStartingAddress;

} blockStruct;

typedef struct cacheStruct
{
    blockStruct blocks[MAX_CACHE_SIZE];
    // for calculating the number of bits needed for the block offset(aka index for memory retrieval)
    int blockSize;
    int numSets;
    int blocksPerSet;
    // blocks per Set * block size = bytes per set, use the power of 2s on it to get the # of set bits
    // tag bits = word - (offset+set)

    // we need these bits for bitmasking!
    // bitmask varies this time rather than being a set number
    // bitmask the given address to get each

} cacheStruct;

/* Global Cache variable */
cacheStruct cache;

void printAction(int, int, enum actionType);
void printCache(void);

/*
 * Set up the cache with given command line parameters. This is
 * called once in main(). You must implement this function.
 */
void cache_init(int blockSize, int numSets, int blocksPerSet)
{
    if (blockSize <= 0 || numSets <= 0 || blocksPerSet <= 0)
    {
        printf("error: input parameters must be positive numbers\n");
        exit(1);
    }
    if (blocksPerSet * numSets > MAX_CACHE_SIZE)
    {
        printf("error: cache must be no larger than %d blocks\n", MAX_CACHE_SIZE);
        exit(1);
    }
    if (blockSize > MAX_BLOCK_SIZE)
    {
        printf("error: blocks must be no larger than %d words\n", MAX_BLOCK_SIZE);
        exit(1);
    }
    if (!is_power_of_2(blockSize))
    {
        printf("warning: blockSize %d is not a power of 2\n", blockSize);
    }
    if (!is_power_of_2(numSets))
    {
        printf("warning: numSets %d is not a power of 2\n", numSets);
    }
    printf("Simulating a cache with %d total lines; each line has %d words\n",
           numSets * blocksPerSet, blockSize);
    printf("Each set in the cache contains %d lines; there are %d sets\n",
           blocksPerSet, numSets);

    // Your code here

    cache.blockSize = blockSize;
    cache.blocksPerSet = blocksPerSet;
    cache.numSets = numSets;

    // need to see if I need to do anything to the blocks array

    // yup I do
    for (int j = 0; j < MAX_CACHE_SIZE; j++)
    {
        cache.blocks[j].tag = -1;
        cache.blocks[j].valid = 0;
    }

    return;
}

/*
 * Access the cache. This is the main part of the project,
 * and should call printAction as is appropriate.
 * It should only call mem_access when absolutely necessary.
 * addr is a 16-bit LC2K word address.
 * write_flag is 0 for reads (fetch/lw) and 1 for writes (sw).
 * write_data is a word, and is only valid if write_flag is 1.
 * The return of mem_access is undefined if write_flag is 1.
 * Thus the return of cache_access is undefined if write_flag is 1.
 */
// need to see if supposed to add stuff here for keeping write data and the write flag
// maybe

int cache_access(int addr, int write_flag, int write_data)
{
    int start;
    int end;

    int blockBits = log2(cache.blockSize);
    double numSetBits = log2(cache.numSets);

    // maximum number represented by the number of bits for the set/line and the block offset
    int maxSetBits = pow(2, numSetBits) - 1;
    int maxBlockBits = pow(2, blockBits) - 1;

    // set/line supposed to look through
    int setBitsAddr = (addr >> blockBits) & maxSetBits;
    // data block we are accessing for reading/writing
    int blockOffset = addr & maxBlockBits;

    // total bits for set/line and the block offset
    // for masking to isolate the tag

    // double check tag isolation

    // DOUBLE CHECK HERE, 16 for the tag when doing address = 23
    //  int totalBitsTag = 16 - (blockBits + numSetBits);
    //  int maxTotalBits = pow(2, totalBitsTag) - 1;
    int sum = (blockBits + numSetBits);
    // int invTag = maxTotalBits << sum;
    // isolated tag
    int tagBitsAddress = addr >> sum;

    // this is for if we have to bring in a whole chunk from memory or kick out a whole chunk (write to memory)
    // zero out the block offset so that we can iterate over the data block for kicking out/writing to the block
    int inv = ~maxBlockBits;
    int startAddress = addr & inv;

    // start and ending index for searching in cache for hit/miss

    //  if fully associative
    // there is one set(whole cache), the number of blocks per set== the number of blocks in whole cache
    //  loop through the whole cache
    if (cache.numSets == 1 && cache.blocksPerSet > 1)
    {
        start = 0;
        end = cache.blocksPerSet;
    }

    // if direct mapped
    // number of sets == number of blocks in the cache, each set has one block
    // the line addr/set addr are the same bits, so start == index supposed to search at == set/line bit in the addr
    // end = start + 1 b/c for loop used for all cases, ensure no loss of generality

    else if (cache.numSets > 1 && cache.blocksPerSet == 1)
    {
        start = setBitsAddr;
        end = setBitsAddr + 1;
    }

    // if set associative
    /// x sets in the cache, n blocks per set
    // set # * blocks per set = 1st line in the set
    //  (set # +1) * blocks per set = 1st line in the next set
    else
    {
        // populate start and end
        // start of the set to look through
        start = setBitsAddr * cache.blocksPerSet;
        // end of it, removing -1 at the end so that for all for loops purely <
        end = ((setBitsAddr + 1) * cache.blocksPerSet);
    }

    // checking if hit or miss
    int hitMiss = 0;
    // saving the block where we have a hit
    int hitAddress = MIN_INT;

    // checking for smallest LRU
    int indexSmallestLRU = 0;
    int smallestLRU = MAX_INT;

    // checking for an empty space
    int indexFirstEmptySpace = MIN_INT;

    // searching through the cache set
    for (int i = start; i < end; i++)
    {
        // check for the LRU
        if (cache.blocks[i].lruLabel < smallestLRU)
        {
            smallestLRU = cache.blocks[i].lruLabel;
            indexSmallestLRU = i;
        }

        // check for an empty space
        if (cache.blocks[i].valid == 0 && indexFirstEmptySpace == MIN_INT)
        {
            indexFirstEmptySpace = i;
        }

        // check for it the tag we are looking for is in the cache
        if (cache.blocks[i].tag == tagBitsAddress)
        {
            hitMiss = 1;
            hitAddress = i;
            break;
        }
    }

    /// miss cache
    if (hitMiss == 0)
    {
        // Allocation then WB
        // put it in the cache

        if (indexFirstEmptySpace != MIN_INT)
        {
            // populate all data associated

            cache.blocks[indexFirstEmptySpace].dirty = 0;
            cache.blocks[indexFirstEmptySpace].tag = tagBitsAddress;
            cache.blocks[indexFirstEmptySpace].valid = 1;

            printAction(startAddress, cache.blockSize, memoryToCache);
            cache.blocks[indexFirstEmptySpace].currentStartingAddress = startAddress;

            for (int jk = 0; jk < cache.blockSize; jk++)
            {
                // increment the tagBitAddress and pass in as the address for populating the data block

                // double check write data being used here
                cache.blocks[indexFirstEmptySpace].data[jk] = mem_access(startAddress, 0, write_data);

                startAddress++;
            }

            if (write_flag == 1)
            {
                cache.blocks[indexFirstEmptySpace].dirty = 1;
                printAction(addr, 1, processorToCache);
                cache.blocks[indexFirstEmptySpace].data[blockOffset] = write_data;
            }

            // marking that transferring stuff from memory to cache
            // double check that it is supposed to be the tag bits address in here

            // updating the LRU since we also do WB in here too

            // ASK if this is a read only or write only or both situation

            // double check this

            int x = cache.blocks[indexFirstEmptySpace].lruLabel;
            cache.blocks[indexFirstEmptySpace].lruLabel = cache.blocksPerSet - 1;

            for (int k = start; k < end; k++)
            {
                if (k != indexFirstEmptySpace && cache.blocks[k].lruLabel > x)
                {
                    cache.blocks[k].lruLabel--;
                }
            }

            if (write_flag == 0)
            {
                printAction(addr, 1, cacheToProcessor);
                return cache.blocks[indexFirstEmptySpace].data[blockOffset];
            }
        }
        // option B no empty space, therefore use the smallest LRU value
        else
        {

            // need to add write to RAM here for instruction we are kicking out
            if (cache.blocks[indexSmallestLRU].dirty == 1)
            {
                printAction(cache.blocks[indexSmallestLRU].currentStartingAddress, cache.blockSize, cacheToMemory);

                // loop to kick everything out
                for (int jk = 0; jk < cache.blockSize; jk++)
                {
                    mem_access(cache.blocks[indexSmallestLRU].currentStartingAddress, 1, cache.blocks[indexSmallestLRU].data[jk]);
                    cache.blocks[indexSmallestLRU].currentStartingAddress++;
                }
            }

            else
            {
                printAction(cache.blocks[indexSmallestLRU].currentStartingAddress, cache.blockSize, cacheToNowhere);
            }

            cache.blocks[indexSmallestLRU].valid = 1;
            cache.blocks[indexSmallestLRU].tag = tagBitsAddress;

            cache.blocks[indexSmallestLRU].currentStartingAddress = startAddress;
            printAction(startAddress, cache.blockSize, memoryToCache);

            for (int jk = 0; jk < cache.blockSize; jk++)
            {
                // increment the tagBitAddress and pass in as the address for populating the data block
                cache.blocks[indexSmallestLRU].data[jk] = mem_access(startAddress, 0, write_data);
                startAddress++;
            }

            if (write_flag == 1)
            {
                cache.blocks[indexSmallestLRU].dirty = 1;
                printAction(addr, 1, processorToCache);
                cache.blocks[indexSmallestLRU].data[blockOffset] = write_data;
            }
            else
            {
                cache.blocks[indexSmallestLRU].dirty = 0;
            }

            // marking that transferring stuff from memory to cache

            int x = cache.blocks[indexSmallestLRU].lruLabel;
            cache.blocks[indexSmallestLRU].lruLabel = cache.blocksPerSet - 1;

            for (int k = start; k < end; k++)
            {
                if (k != indexSmallestLRU && cache.blocks[k].lruLabel > x)
                {

                    cache.blocks[k].lruLabel--;
                }
            }

            if (write_flag == 0)
            {
                printAction(addr, 1, cacheToProcessor);
                return cache.blocks[indexSmallestLRU].data[blockOffset];
            }
        }
    }
    // hit
    else
    {
        // WB only

        cache.blocks[hitAddress].valid = 1;

        if (write_flag == 1)
        {
            cache.blocks[hitAddress].dirty = 1;
            cache.blocks[hitAddress].data[blockOffset] = write_data;

            // check if this is the right value
            printAction(addr, 1, processorToCache);
        }

        // increment all entries that come before MRU aka hitAddress
        //  check slides for how to manage this

        int x = cache.blocks[hitAddress].lruLabel;

        cache.blocks[hitAddress].lruLabel = cache.blocksPerSet - 1;

        for (int k = start; k < end; k++)
        {
            if (k != hitAddress && cache.blocks[k].lruLabel > x)
            {
                cache.blocks[k].lruLabel--;
            }
        }

        if (write_flag == 0)
        {
            printAction(addr, 1, cacheToProcessor);

            return cache.blocks[hitAddress].data[blockOffset];
        }
    }

    // allocation and writing policy
    // allocation: if not in cache put in cache
    // WB: if in cache put in cache, if kick out -> out in RAM -> call mem access
    // hit if in cache, miss if not in cache

    // if miss then allocation policy and  WB both occur

    // if hit then WB only

    // finding where I am supposed to put in cache
    //  use the set bits from the address in order to figure out which set
    //  translate that into an starting and ending section of a set in cache if > 1 block is in the set

    // set associative stuff for when there is > 1 block in a set

    // start = set num from address * blocksPerSet
    // end = (set num from address -1) * blocksPerSet

    // special case -> if blocks per set = 1 then literally, set bit = place in cache to put it exactly

    // allocate stage
    // then loop through the set starting at start, ending at end inclusive
    // if valid != 1 -> put it there and stop
    // if no valid != 1 -> find the largest LRU and put it there instead, set dirty to 0, valid = 1
    // call mem access here, pass the stuff, for the instruction we are kicking out, if dirty = 1
    // set LRU to 1, increment all other LRU in the cache

    // WB only
    // find a way to have the location b/c we know it is in the cache
    // simply set dirty = 1

    /* The next line is a placeholder to connect the simulator to
    memory with no cache. You will remove this line and implement
    a cache which interfaces between the simulator and memory. */

    // CHECK IF SHOULD BE HERE

    return 0;

    // things to ask about
    //  1. what is write flag and write data used for
    //  2. is mem access how we are supposed to write to memory
    //  3. do I need to store write flag and write data with each block??? (due to needing to write to RAM upon kicking out the cache entry)

    // 4. please explain the sw/lw/fetch connection to this cache

    // 5. replacing LRU is set specific???
}

/*
 * print end of run statistics like in the spec. **This is not required**,
 * but is very helpful in debugging.
 * This should be called once a halt is reached.
 * DO NOT delete this function, or else it won't compile.
 * DO NOT print $$$ in this function
 */
void printStats(void)
{
    int numHits;
    int numMisses;
}

/*
 * Log the specifics of each cache action.
 *
 *DO NOT modify the content below.
 * address is the starting word address of the range of data being transferred.
 * size is the size of the range of data being transferred.
 * type specifies the source and destination of the data being transferred.
 *  -    cacheToProcessor: reading data from the cache to the processor
 *  -    processorToCache: writing data from the processor to the cache
 *  -    memoryToCache: reading data from the memory to the cache
 *  -    cacheToMemory: evicting cache data and writing it to the memory
 *  -    cacheToNowhere: evicting cache data and throwing it away
 */
void printAction(int address, int size, enum actionType type)
{
    printf("$$$ transferring word [%d-%d] ", address, address + size - 1);

    if (type == cacheToProcessor)
    {
        printf("from the cache to the processor\n");
    }
    else if (type == processorToCache)
    {
        printf("from the processor to the cache\n");
    }
    else if (type == memoryToCache)
    {
        printf("from the memory to the cache\n");
    }
    else if (type == cacheToMemory)
    {
        printf("from the cache to the memory\n");
    }
    else if (type == cacheToNowhere)
    {
        printf("from the cache to nowhere\n");
    }
    else
    {
        printf("Error: unrecognized action\n");
        exit(1);
    }
}

/*
 * Prints the cache based on the configurations of the struct
 * This is for debugging only and is not graded, so you may
 * modify it, but that is not recommended.
 */
void printCache(void)
{
    printf("\ncache:\n");
    for (int set = 0; set < cache.numSets; ++set)
    {
        printf("\tset %i:\n", set);
        for (int block = 0; block < cache.blocksPerSet; ++block)
        {
            printf("\t\t[ %i ]: {", block);
            for (int index = 0; index < cache.blockSize; ++index)
            {
                printf(" %i", cache.blocks[set * cache.blocksPerSet + block].data[index]);
            }
            printf(" }\n");
        }
    }
    printf("end cache\n");
}
