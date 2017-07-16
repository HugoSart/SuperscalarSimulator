        .data
var1:   .int    9,2,3,-485,5
var2:   .int    3,2,3,4
var3:   .int    20
end3:   .int    0x40

        .text
main:   lw      $0, end3
        add     $5, $0, $0
        mul     $2, $0, $5


