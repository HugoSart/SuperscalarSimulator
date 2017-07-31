        .section data
arg0:   .int        0
arg1:   .int        0

zero:   .int        0

        .section text
        .globl  s_add
        .type   s_add, @function

s_add:  push    %rbp
        mov     %rsp, %rbp

        mov     %rdi, arg0
        mov     %rsi, arg1

        movl    zero, %eax
        addl    arg0, %eax
        addl    arg1, %eax

        mov     %rbp, %rsp
        pop     %rbp

        ret
