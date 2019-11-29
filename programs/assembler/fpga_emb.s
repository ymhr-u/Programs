        .text
        .globl main
        .section MAIN

main:   ori $t1, $0,19264 # set timer counter
        lui $t1,76
        mtc0 $t1, $11  # set Compare register in CP0

        mtc0 $0, $9    # reset Conter register in CP0 = timer reset

        lw   $t1, M_S_enable
        nop  # delay slot for lw
        mtc0 $t1, $12

        ori $t1, $0, 1  # set timer trigger
        ori $t2, $0, 0  # set LED status
        ori $t4, $0, 0  # set SEG status


        lw $t3, ledadr

loop:   bne $t1, $0, loop # wait timer trigger
        nop
        ori $t1, $0, 1  # set timer trigger

        #LED operation
        beq $t2, $0, disable
        ori $t2, $0, 0
par_ret:
        sw $t4,($t3)
        j exit
        nop

disable:ori     $t2, $0, 1
        ori     $t4, $0, 0x00
        sw      $t4,($t3)

TASK_A1:
count01s:
        la      $t5, time0
        lw      $t7, ($t5)
        addi    $t7,$t7,1
        sw      $t7, ($t5)
        bge     $t7,10,cont1s
        j       TASK_A2
cont1s:
        ori     $t7,$0,0
        sw      $t7, ($t5)
        la      $t5, time1
        lw      $t7, ($t5)
        addi    $t7,$t7,1
        sw      $t7, ($t5)
        bge     $t7,10 ,cont10s
        j       TASK_A2
cont10s:
        ori     $t7,$0,0
        sw      $t7, ($t5)
        la      $t5, time2
        lw      $t7, ($t5)
        addi    $t7,$t7,1
        sw      $t7, ($t5)
        bge     $t7,6 ,cont60s
        j       TASK_A2
cont60s:
        ori     $t7,$0,0
        sw      $t7, ($t5)
        la      $t5, time3
        lw      $t7, ($t5)
        addi    $t7,$t7,1
        sw      $t7, ($t5)
        bge     $t7,6 ,over
        j       TASK_A2
over:   ori     $t7,$0,0
        sw      $t7, ($t5)
        sw      $t7,($t6)

TASK_A2:
        lw      $t5, swtadr
        lw      $t6, ($t5)
        andi    $t7, $t6,2
        beqz    $t7, time_now

        la      $t5, time0_stop
        lw      $t6, ($t5)
        la      $t5, address_7seg_hex0
        lw      $t7, ($t5)
        sw      $t6, ($t7)

        la      $t5, time1_stop
        lw      $t6, ($t5)
        la      $t5, address_7seg_hex1
        lw      $t7, ($t5)
        sw      $t6, ($t7)

        la      $t5, time2_stop
        lw      $t6, ($t5)
        la      $t5, address_7seg_hex2
        lw      $t7, ($t5)
        sw      $t6, ($t7)

        la      $t5, time3_stop
        lw      $t6, ($t5)
        la      $t5, address_7seg_hex3
        lw      $t7, ($t5)
        sw      $t6, ($t7)

        j       TASK_B
time_now:
        la      $t5, time0
        lw      $t6, ($t5)
        la      $t5, address_7seg_hex0
        lw      $t7, ($t5)
        sw      $t6, ($t7)

        la      $t5, time1
        lw      $t6, ($t5)
        la      $t5, address_7seg_hex1
        lw      $t7, ($t5)
        sw      $t6, ($t7)

        la      $t5, time2
        lw      $t6, ($t5)
        la      $t5, address_7seg_hex2
        lw      $t7, ($t5)
        sw      $t6, ($t7)

        la      $t5, time3
        lw      $t6, ($t5)
        la      $t5, address_7seg_hex3
        lw      $t7, ($t5)
        sw      $t6, ($t7)

TASK_B:
pattern0:
        addiu   $sp,$sp,-4  # store $t2
        sw      $t2, 0($sp)
        addiu   $sp,$sp,-4  # store $t3
        sw      $t3, 0($sp)

        lw      $t2, swtadr
        lw      $t3, 0($t2)
        andi    $t2,$t3,1
        beqz    $t2,pattern1
        ori     $t4,$t4,0x1
pattern1:
        lw      $t2, swtadr
        lw      $t3, 0($t2)
        andi    $t2,$t3,2
        beqz    $t2,pattern2
        ori     $t4,$t4,2
pattern2:
        lw      $t2, swtadr
        lw      $t3, 0($t2)
        andi    $t2,$t3,4
        beqz    $t2,pattern3
        ori     $t4,$t4,4
pattern3:
        lw      $t2, swtadr
        lw      $t3, 0($t2)
        andi    $t2,$t3,8
        beqz    $t2,skip
        ori     $t4,$t4,8
skip:
        lw      $t3, 0($sp)
        addiu   $sp,$sp,4 #restore $t3
        lw      $t2,0($sp)
        addiu   $sp,$sp,4  # restore $t2
        sw      $t4,($t3)

TASK_C:
keychec:
        lw      $t5, swtadr
        lw      $t6, ($t5)
        andi    $t7, $t6,2
        beqz    $t7, notswt
        la      $t5, key1_prev
        lw      $t7,($t5)
        beq     $t7,1,skip3
        ori     $t7, $0,1
        sw      $t7, ($t5)

cnt01_inC:
        la      $t5, time0
        lw      $t6, ($t5)
        la      $t5, time0_stop
        sw      $t6, ($t5)
cnt1_inC:
        la      $t5, time1
        lw      $t6, ($t5)
        la      $t5, time1_stop
        sw      $t6, ($t5)
cnt10_inC:
        la      $t5, time2
        lw      $t6, ($t5)
        la      $t5, time2_stop
        sw      $t6, ($t5)
cnt60_inC:
        la      $t5, time3
        lw      $t6, ($t5)
        la      $t5, time3_stop
        sw      $t6, ($t5)
        j       skip3
notswt:
        la      $t5, key1_prev
        lw      $t7, ($t5)
        ori     $t7, $0,0
        sw      $t7, ($t5)
skip3:

        bge     $t8,10,TASK_D
        bge     $t9,10,TASK_E
        j       TASK_F

TASK_D:
        la      $t5, time1
        lw      $t7,($t5)
        addi    $t7,$t7,1
        sw      $t7, ($t5)
        j       TASK_F

TASK_E:

        la      $t5, time1
        lw      $t7,($t5)
        addi    $t7,$t7,-1
        sw      $t7, ($t5)
        blt     $t7,0,minus2
        j       exit
minus2:
        ori     $t7,$0,9
        sw      $t7,($t5)
        la      $t5,time2
        lw      $t7,($t5)
        addi    $t7,$t7,-1
        sw      $t7,($t5)
        blt     $t7,0,minus3
        j       TASK_F

minus3:
        ori     $t7,$0,5
        sw      $t7,($t5)
        la      $t5,time3
        lw      $t7,($t5)
        addi    $t7,$t7,-1
        sw      $t7,($t5)
        j       TASK_F

TASK_F:
        lw      $t5,swtadr
        lw      $t6,($t5)
        andi    $t7,$t6,4
        beqz    $t7,npsh
        addi    $t8,$t8,1
        j       new

npsh:   ori     $t8,$0,0
        lw      $t5,swtadr
        lw      $t6,($t5)
        andi    $t7,$t6,8
        beqz    $t7,npsh2
        addi    $t9,$t9,1
        j       new
npsh2:  ori     $t9,$0,0


new:
        lw      $t2, swtadr
        lw      $t3, 0($t2)
        andi    $t2,$t3,1
        beqz    $t2,new1

        ori     $t8,$0,0
        ori     $t9,$0,0

        la      $t5, kit_timer1
        lw      $t7, ($t5)
        beqz    $t7,nps0
        la      $t5, address_7seg_hex1
        lw      $t6, ($t5)
        sw      $t7, ($t6)
        j       xxx
nps0:
        ori     $t6,$0,0
        la      $t5, address_7seg_hex1
        lw      $t7, ($t5)
        sw      $t6, ($t7)
xxx:

        la      $t5, kit_timer3
        lw      $t7, ($t5)
        beqz    $t7,nps1
        la      $t5, address_7seg_hex3
        lw      $t6, ($t5)
        sw      $t7, ($t6)
        j       yyy
nps1:
        ori     $t6,$0,0
        la      $t5, address_7seg_hex3
        lw      $t7, ($t5)
        sw      $t6, ($t7)
yyy:


        ori     $t6,$0,0
        la      $t5, address_7seg_hex0
        lw      $t7, ($t5)
        sw      $t6, ($t7)

        ori     $t6,$0,0
        la      $t5, address_7seg_hex2
        lw      $t7, ($t5)
        sw      $t6, ($t7)


set_t:

        lw      $t5, swtadr
        lw      $t6, 0($t5)
        andi    $t5, $t6,4
        beqz    $t5, skip6
        la      $t5, key2_prev
        lw      $t7, ($t5)
        beq     $t7, 1,set_t1
        ori     $t7, $0,1
        sw      $t7, ($t5)

        la      $t5, address_7seg_hex1
        lw      $t6, ($t5)
        la      $t5, kit_timer1
        lw      $t7, ($t5)
        addi    $t7, $t7,1
        sw      $t7, ($t5)
        sw      $t7, ($t6)

        j       set_t1
skip6:
        la      $t5, key2_prev
        lw      $t6, ($t5)
        ori     $t7, $0,0
        sw      $t7, ($t5)


set_t1:

        lw      $t5, swtadr
        lw      $t6, 0($t5)
        andi    $t5, $t6,8
        beqz    $t5, skip7
        la      $t5, key3_prev
        lw      $t7, ($t5)
        beq     $t7, 1,zzz
        ori     $t7, $0,1
        sw      $t7, ($t5)

        la      $t5, address_7seg_hex3
        lw      $t6, ($t5)
        la      $t5, kit_timer3
        lw      $t7, ($t5)
        addi    $t7, $t7,1
        sw      $t7, ($t5)
        sw      $t7, ($t6)

        j       zzz
skip7:
        la      $t5, key3_prev
        lw      $t6, ($t5)
        ori     $t7, $0,0
        sw      $t7, ($t5)

zzz:
        la      $t5, kit_timer3
        lw      $t7, ($t5)
        bne     $t7, 10,exit
        ori     $t7, $0,9
        sw      $t7, ($t5)

        la      $t5, kit_timer1
        lw      $t7, ($t5)
        bne     $t7, 10,exit
        ori     $t7, $0,0
        sw      $t7, ($t5)
        la      $t5, kit_timer2
        lw      $t7, ($t5)
        addi    $t7,    $t7,1
        sw      $t7, ($t5)

new1:
exit:   nop

        .section INT
__vector0:
        addiu   $sp,$sp,-4  # store $t2
        sw      $t2,0($sp)

        lw      $t2, M_S_disable   #interrupt disable
        nop     # delay slot for lw
        mtc0    $t2, $12

        ori     $t2, $0,19264 # set timer counter
        lui     $t2,76
        mtc0    $t2, $11  # set Compare register in CP0 = interrupt flag clear
        mtc0    $0, $9    # reset Conter register in CP0 = timer reset
        ori     $t1, $0, 0  # release timer trigger

        lw      $t2, M_S_enable   #interrupt enable
        nop     #delay slot for lw
        mtc0    $t2, $12

        lw      $t2,0($sp)
        addiu   $sp,$sp,4  # restore $t2
        eret

       .data
M_S_enable :.word 272662529  # 0001 0000 0100 0000 1000 0000 0000 0001
M_S_disable:.word 272662528  # 0001 0000 0100 0000 1000 0000 0000 0000
ledadr:     .word 0xc0000000
swtadr:     .word 0xd0000000
time0:      .word 0
time1:      .word 0
time2:      .word 0
time3:      .word 0
time0_stop: .word 0
time1_stop: .word 0
time2_stop: .word 0
time3_stop: .word 0
key1_prev:  .word 0
key2_prev:  .word 0
key3_prev:  .word 0
kit_timer0: .word 0
kit_timer1: .word 0
kit_timer2: .word 0
kit_timer3: .word 0
kit_key2:   .word 0
kit_key3:   .word 0

        .global array
address_7seg_hex0: .word 3758096384
address_7seg_hex1: .word 3758096388
address_7seg_hex2: .word 3758096392
address_7seg_hex3: .word 3758096396