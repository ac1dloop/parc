#include <stdio.h>
#include <parc.h>

int main(int argc, char **argv){

    Item* head = parc_parse(argc, argv);

    print_item_list(head);

    int a = parc_get_int(head, "port");

    printf("got port: %d\n", a);
    
    int b = parc_get_int(head, "gaga");

    printf("b: %d\n", b);

    int c = parc_get_int(head, "no such value");

    return 0;
}