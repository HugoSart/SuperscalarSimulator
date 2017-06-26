#include "bop.h"
#include <malloc.h>

char *itbs(unsigned int bits, int n) {
    int c, d, count;
    char *pointer;

    count = 0;
    pointer = (char*)malloc(bits+1);

    if ( pointer == NULL )
        return NULL;

    for ( c = bits - 1 ; c >= 0 ; c-- ) {
        d = n >> c;

        if ( d & 1 )
            *(pointer+count) = 1 + '0';
        else
            *(pointer+count) = 0 + '0';

        count++;
    }

    *(pointer+count) = '\0';

    return  pointer;
}

int bsti(char *bs) {

    return (int)strtol(bs, NULL, 2);

}

int itbscat(int n1, int n2) {

    char *s1 = itbs(32, n1);
    char *s2 = itbs(32, n2);

}

