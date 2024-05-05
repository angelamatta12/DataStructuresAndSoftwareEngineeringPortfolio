            lw      0       0       mcand
            lw      1       1       iStart
            lw      2       2       iStart
            lw      3       3       iStart
            lw      4       4       iMax
            lw      5       5       mplier
            lw      6       6       mask
            lw      7       7       mask
start       beq     3       4       done
            nor     6       6       6
            nor     5       5       5
            nor     5       6       5 
            nor     6       6       6
            beq     5       6       mAdd  
cont        add     6       6       6
            add     7       3       3 
            lw      2       5       mplier
            add     0       0       0
            beq     3       3       start
mAdd    add     0       1       1
            beq     0       0       cont
done        halt
mcand       .fill   6203
mplier      .fill   1429
iStart   .fill   0
iMax     .fill   15
mask        .fill   1
