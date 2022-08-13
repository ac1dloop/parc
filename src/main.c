#include <stdio.h>
#include <parc.h>

int main(int argc, char **argv){

    Item* head = parc_parse(argc, argv);

    int port = parc_get_int(head, "port");

    printf("port: %d\n", port);

    parc_free(head);

    return 0;
}