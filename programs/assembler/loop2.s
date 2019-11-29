        .data
N:      .word 10
A:      .word 8
        .word 4
        .word 7
        .word 12
        .word 13
        .word 19
        .word 23
        .word 43
        .word 56
        .word 32

	.text
main:   or $8,$0,$0
        la $10,A
        or $11,$0,$0
        lw $13,N
outloop:beq $8,$13,outloopend
        lw $9,N
        addi $9,-2
inloop: beq $9,$8,inloopend
        lw $11,0($10)
        lw $12,4($10)
hikaku:	slt $14,$12,$11
        beq $14,$0,hikakuend
        beq $12,$0,hikakuend
        add $15,$11,$0
        sw $12,0($10)
        sw $15,4($10)
hikakuend:
	addi $10,4
        addi $9,-1
        j inloop
inloopend:
        addi $8 1
        j outloop
outloopend:
exit:   j    exit