#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include <parc.h>

/* this is file is intended to show all features of project */
int main(int argc, char **argv){

    /* parse input */
    ParcItem* parc = parc_parse(argc, argv);
    
    /* if user entered './parc help' this will return 1 */
    int h = parc_bool(parc, "help");

    /* './parc version' this will return 1 */
    int v = parc_bool(parc, "version");

    if (h){
        printf("usage %s action=[] val1=[] val2=[]\n", argv[0]);
        printf("where action is one of following:\n");
        printf("\tsum\n\tpow\n\tmul\n");
        printf("val1 and val2 are values of type double\n");
        parc_free(parc);
        return 0;
    }

    if (v){
        printf("1.0.1\n");
        parc_free(parc);
        return 0;
    }

    /* dont forget to free memory. default 'sum' will be returned if no action specified */
    char* act = parc_str(parc, "action", "sum");

    double a = parc_double(parc, "val1", 0.0);
    double b = parc_double(parc, "val2", 0.0);
    
    double res = 0.0;

    if (strcmp(act, "pow") == 0){

        res = pow(a, b);

    } else if (strcmp(act, "sum") == 0){

        res = a + b;

    } else if (strcmp(act, "mul") == 0){

        res = a * b;

    } else {

        printf("impossible!!!\n");

    }

    printf("result: %lf\n", res);
    free(act);
    parc_free(parc);

    return 0;
}