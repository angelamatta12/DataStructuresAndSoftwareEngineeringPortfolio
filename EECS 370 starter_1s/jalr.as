        lw      0   0   num
        jalr    0   1
fail    noop
        beq     0   0   fail
done    halt
num     .fill   4