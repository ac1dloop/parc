#pragma once

#include <stdlib.h>
#include <string.h>

#define STR_BUF_SZ 256

//Item holds argument and value
typedef struct ParcItem {
    char* name;
    char* value; 
    struct ParcItem *next;
} ParcItem;

//Item* constructor
ParcItem* _parc_item_alloc(){
    ParcItem* v = (ParcItem*)malloc(sizeof(ParcItem));

    v->name = NULL;
    v->value = NULL;
    v->next = NULL;

    return v;
}

//Item* destructor
void _parc_item_free(ParcItem* it){
    free(it->name);
    free(it->value);
    free(it);
}

//splits string by 'sep' separator
//sets it->name to first part and it->value to second
//it->name contains fool string if nothing to split
void _parc_item_parse(ParcItem* it, const char* str, char sep){
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

    it->name = (char*)malloc(sizeof(char) * strlen(str) + 1);

    memcpy(it->name, str, strlen(str));

    it->name[strlen(str)] = '\0';
}

//returns head of linked list of Item* elements
ParcItem* _parc_item_list_alloc(size_t sz){
    ParcItem* head = _parc_item_alloc();

    for (ParcItem* it = head;sz != 0; sz--){
        it->next = _parc_item_alloc();
        it = it->next;
    }

    return head;
}

//item list destructor
void parc_free(ParcItem* head){
    ParcItem* del;
    for (ParcItem *it = head; it != NULL;){
        del = it;

        it = it->next;

        _parc_item_free(del);
    }
}

ParcItem* _parc_item_list_find(ParcItem* head, const char* name){
    for (ParcItem* it = head; it->next; it = it->next){
        if (strncmp(it->name, name, STR_BUF_SZ) == 0){
            return it;
        }
    }

    return NULL;
}

// #ifdef PARC_DBG
void _parc_print_item_list(ParcItem* head){
    size_t count = 0;

    for (ParcItem* it = head; it != NULL; it = it->next){
        printf("item: %zu\n", count++);
        printf("%s:%s\n", it->name, it->value);
    }
}
// #endif

//assuming name and value are NULL-terminated 'strings'
void parc_item_set(ParcItem* it, const char* name, const char* value){
    memcpy(it->name, name, strlen(name));
    memcpy(it->value, value, strlen(value));
}

//this is tipa API
ParcItem* parc_get_item(ParcItem* head, const char* name){
    ParcItem* it = _parc_item_list_find(head, name);

    return it;
}

int parc_get_int(ParcItem* head, const char* name){
    return atoi(_parc_item_list_find(head, name)->value);
}

double parc_get_double(ParcItem* head, const char* name){
    return atof(_parc_item_list_find(head, name)->value);
}

//user is responsible for returned memory
char* parc_get_str(ParcItem* head, const char* name){
    ParcItem* it = _parc_item_list_find(head, name);

    char* str = (char*)malloc(strlen(it->value));
    memcpy(str, it->value, strlen(it->value));
    return str;
}

int parc_int(ParcItem* head, const char* name, int default_value){
    ParcItem* it = parc_get_item(head, name);

    if (it != NULL)
        return atoi(it->value);
    
    return default_value;
}

double parc_double(ParcItem* head, const char* name, double default_value){
    ParcItem* it = parc_get_item(head, name);
    if (it)
        return atof(it->value);

    return default_value;
}

char* parc_str(ParcItem* head, const char* name, const char* default_value){
    ParcItem* it = parc_get_item(head, name);

    if (it){
        char* str = (char*)malloc(strlen(it->value));
        memcpy(str, it->value, strlen(it->value));
        return str;
    }

    char* str = (char*)malloc(strlen(default_value));
    memcpy(str, default_value, strlen(default_value));
    return str;
}

int parc_bool(ParcItem* head, const char* name){
    if (parc_get_item(head, name) != NULL)
        return 1;
    
    return 0;
}

//parse arguments and put them in list
ParcItem* parc_parse(int argc, char **argv){
    ParcItem* head = _parc_item_list_alloc(argc - 1);

    ParcItem* it = head;
    for (int i = 1; i < argc; i++){
        _parc_item_parse(it, argv[i], '=');
        it = it->next;
    }

    return head;
}