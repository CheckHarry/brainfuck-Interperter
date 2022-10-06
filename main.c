#include <stdio.h>
#include <string.h>
#include "bf_interperter.c"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("incorrect input number\n");
        return -1;
    }

    char bf_prg[4096];
    int prg_size;
    FILE *f;
    f = fopen(argv[1] , "r");

    if( NULL == f ){
        printf( "open failure\n" );
        return 1;
    }else{
        prg_size = fread(bf_prg , 1 , sizeof(bf_prg) , f);
    }
    
    printf("prg size : %d\n" , prg_size);
    bf_interperter_t bf_i;

    bf_init(&bf_i);

    bf_run(
        &bf_i,
        bf_prg,
        prg_size
    );

}