        .data
A:
	.word 0
	.word 1
	.word 0
	.word 0
	.word 2
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	.word 3
	.word 0
	.word 0
	.word 4
	.word 0
	
B:		
	.word 1
	.word 2
	.word 3
	.word 4
	.word 5
	.word 6
	.word 7
	.word 8
	.word 9
	.word 10
	.word 11
	.word 12
	.word 13
	.word 14
	.word 15
	.word 16
	
C:	
	.space 64
	.text
	
main:	
	la $16,A
	la $17,B
	la $18,C
	ori $19,$0,0
	ori $20,$0,0
	ori $21,$0,0
	ori $22,$0,0
	ori $23,$0,4
iloop:  beq $19,$23 iloopend
	ori $20,$0,0
jloop:  beq $20,$23 jloopend
        ori $21,$0,0
	ori $22,$0,0
kloop:  beq $21,$23 kloopend
	lw  $a0,0($16)
	lw  $a1,0($17)
	jal MUL
	add $22,$22,$2
	addi $16,$16,4
	addi $17,$17,16
	addi $21,$21,1
	j kloop
kloopend:
	addi $20,$20,1
	addi $16,$16,-16
	addi $17,$17,-60
	sw $22, 0($18)
	addi $18,$18,4
	j jloop
jloopend:
	la $17,B
	addi $16,$16,16
	addi $19,$19,1
	j iloop
iloopend:
MUL:    or $8,$a0,$0
	or $9,$a1,$0
	ori $10,$0,0  #積
	ori $11,$0,16 #16回
	or $12,$0,$0  #ループ変数
	ori $13,$0,1  #シフト命令用
loop:   beq $11,$12 loopend
	addi $12,$12,1
	and $14,$8,$13
	beq $14,$0,skip
	add $10,$10,$9
skip:   addu $9,$9,$9
	add $13,$13,$13
	j loop
loopend:
	ori $v0,$10,0
	jr $ra