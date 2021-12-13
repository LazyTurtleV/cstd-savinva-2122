#include <stdio.h>

void ___print_mem___(void *_ptr, unsigned int _n)
{
    for (char *p = (char*)_ptr, i = 0; i < _n; i++, p++)
    {
        if( !(i % 8) ) printf("\n0x%08x: ", p);
        printf("%02x ", *p & 0xFF);
    }

    puts("\n");
    fflush(stdout);
}