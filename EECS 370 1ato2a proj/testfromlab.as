        lw      0       2       five    load reg1 with 5 (symbolic address)
        sw      1       2       10000       load reg2 with -1 (numeric address)
start   add     1       2       1       decrement reg1
        beq     7       3       2       goto end of program when reg1==0
        beq     1       5       start   go back to the beginning of the loop
done      noop
done    halt                            end of program
five    .fill   5
neg1    .fill   -1
stAddr  .fill   start                   will contain the address of start (2)