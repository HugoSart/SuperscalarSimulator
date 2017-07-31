        .text
main:   addi    $t1, $zero, 0       # t0 é a base, t1 é o expoente, t2 é o contador, a0 é o resultado

read_1: addi    $v0, $zero, 5       # código de read_int
        syscall                     # syscall read_int
        addi    $t0, $v0, 0         # t0 é a base

read_2: addi    $v0, $zero, 5       # código de read_int
        syscall                     # syscall read_int
        addi    $t1, $v0, 0         # t1 é o expoente

        addi    $a0, $zero, 1       # a0 = 1
        beq     $t1, $zero, end     # se expoente == 0

        addi    $a0, $t0, 0         # a0 = t0
        addi    $t4, $zero, 1
        beq     $t1, $t4, end       # se expoente == 1

        addi    $t2, $zero, 1       # t2 é o contador
        addi    $a0, $t0, 0         # passa o t0 para o a0 para ser usado como resposta
loop:   jal     pow
        addi    $t2, $t2, 1         # t2++
        bne     $t2, $t1, loop      # enquanto t2 != t0
        j       end

pow:    mul     $a0, $a0, $t0       # código de print_int
        jr      $ra                 # continua onde estava no loop

end:    addi    $v0, $zero, 1       # código de print_int
        syscall                     # printa a0