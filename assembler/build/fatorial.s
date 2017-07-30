        .data
resp:   .int    1

        .text
main:   addi    $v0, $zero, 5   # v0 será o n
        syscall

        addi    $v0, $v0, 1     # adiciona 1 para bne comparar certo
        addi    $t0, $zero, 1   # t0 será o contador
        addi    $t1, $zero, 1   # t1 será a resposta

loop:   mul     $t1, $t1, $t0
        addi    $t0, $t0, 1
        bne     $t0, $v0, loop

        sw      $t1, resp
        lw      $a0, resp
        addi    $v0, $zero, 1
        syscall




