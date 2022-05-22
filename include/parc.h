#pragma once

#include <stdlib.h>
#include <string.h>

#define STR_BUF_SZ 256

//convinience conatiner for input arguments
typedef struct Item {
    char* name;
    char* value; 
    struct Item *next;
} Item;

//Item* constructor
Item* parc_item_alloc(){
    Item* v = (Item*)malloc(sizeof(Item));

    v->name = NULL;
    v->value = NULL;
    v->next = NULL;

    return v;
}

//Item* destructor
void parc_item_free(Item* it){
    free(it->name);
    free(it->value);
    free(it);
}

//splits string and fill name and value of Item*
//if failed to split. string is copied into name
void parc_item_parse(Item* it, const char* str, char sep){
    size_t sz = strlen(str);

    for (size_t i = 0; i < sz; i++){
        if (str[i] == sep){

            if (it->name == NULL)
                it->name = (char*)malloc(sizeof(char) * (i + 1));
            else it->name = (char*)realloc(it->name, sizeof(char) * (i + 1));

            memcpy(it->name, str, i);
            it->name[i] = '\0';

            if (it->value == NULL)
                it->value = (char*)malloc(sizeof(char) * (sz - i));
            else it->value = (char*)realloc(it->value, sizeof(char) * (sz - i));

            memcpy(it->value, str + i + 1, sz - i - 1);
            it->value[sz - i - 1] = '\0';

            return;
        }
    }

    free(it->value);
    it->value = NULL;

    if (it->name)
        it->name = (char*)realloc(it->name, sizeof(char) * strlen(str));
    else it->name = (char*)malloc(sizeof(char) * strlen(str));

    memcpy(it->name, str, strlen(str));
    it->name[strlen(str) - 1] = '\0';
}

//returns head of linked list of Item* elements
Item* item_list_alloc(size_t sz){
    Item* head = parc_item_alloc();

    for (Item* it = head;sz != 0; sz--){
        it->next = parc_item_alloc();
        it = it->next;
    }

    return head;
}

//item list destructor
void item_list_free(Item* head){
    Item* del;
    for (Item *it = head; it != NULL;){
        del = it;

        it = it->next;

        parc_item_free(del);
    }
}

Item* item_list_find(Item* head, const char* name){
    for (Item* it = head; it != NULL; it = it->next){
        if (strncmp(it->name, name, STR_BUF_SZ) == 0){
            return it;
        }
    }

    return NULL;
}

// #ifdef PARC_DBG
void print_item_list(Item* head){
    size_t count = 0;

    for (Item* it = head; it != NULL; it = it->next){
        printf("item: %zu\n", count++);
        printf("%s:%s\n", it->name, it->value);
    }
}
// #endif

//assuming name and value are NULL-terminated 'strings'
void parc_item_set(Item* it, const char* name, const char* value){
    memcpy(it->name, name, strlen(name));
    memcpy(it->value, value, strlen(value));
}

int parc_get_int(Item* head, const char* name){
    return atoi(item_list_find(head, name)->value);
}

//parse arguments and put them in list
Item* parc_parse(int argc, char **argv){
    Item* head = item_list_alloc(argc - 1);

    Item* it = head;
    for (int i = 1; i < argc; i++){
        parc_item_parse(it, argv[i], '=');
        it = it->next;
    }

    return head;
}