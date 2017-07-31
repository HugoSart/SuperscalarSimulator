        .data
testesl0:   .int    0
testesl1:   .int    1

        .text
main:   lw      $t0, zero
        lw      $t1, um
        addi    $t7, $0, 0      # scan

        addi    $v0, $0, 5
        syscall                 # scan

        movz    $s0, $v0, $t0
        blez    $s0, fim

loop:   movz    $a0, $t0, $0
        addi    $v0, $0, 1
        syscall                 # mostra t0

        movz    $s1, $t1, $0
        add     $t1, $t0, $t1
        movz    $t0, $s1, $0

        addi    $t7, $t7, 1     # T7++
        beq     $t7, $s0, fim   # Se T7 == S0 -> fim
        j       loop

fim:    addi $v0, $0, 10
        syscall                 # exit