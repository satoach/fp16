#include <stdio.h>
#include <stdlib.h>
#include "fp16.h"

int main(int argc, char *argv[])
{
    if (argc >= 2)
        printf("0x%04x\n", get_fp16(atof(argv[1])));
    else
        printf("%s x.bc\n", argv[0]);
    return 0;
}
