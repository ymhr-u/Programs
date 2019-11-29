        .data
N:      .word 10    # The length of Array
A:      .word 8     # A[0] = 8
        .word 4     # A[1] = 4
        .word 7
        .word 12
        .word 13
        .word 19
        .word 23
        .word 43
        .word 56    # A[8] = 56
        .word 32    # A[9] = 32
S:      .word 0

        .text
main:   or $8,$0,$0
        la $9,A
        or $11,$0,$0
        lw $12,N
        lw $13,S
loop:   beq $8,$12,loopend
        lw $10,0($9)
        addi $9,4
        add  $11,$10,$11
        addi $8,1
        j loop
loopend:
        sw  $11,S