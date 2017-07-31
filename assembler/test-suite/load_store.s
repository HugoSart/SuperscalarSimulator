        .data
zero:   .int    0
count:  .int    75
array:  .int    12

        .text
main:   lw      $t0, count

        mul     $t0, $t0, $t0
        sw      $t0, array
        addi    $t0, $t0, 25
        sw      $t0, zero

        addi    $v0, $zero, 1

        lw      $a0, zero
        NOP #
        NOP #
        NOP #
        NOP #
        NOP #
        NOP #
        syscall                 # printa count

        lw      $a0, array
        NOP #
        NOP #
        NOP #
        syscall                 # printa count

        lw      $a0, count
        NOP #
        NOP #
        NOP #
        syscall                 # printa count