#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

void data_free(void *d);
void print_list(linked_list *list);

void data_free(void *d)
{
    printf("free: %p (%d)\n", d, *(int*)d);
    free(d);
}

void print_list(linked_list *list)
{
    linked_list_node *node;

    if(!list)
    {
        puts("no list to print");
        return;
    }

    printf("  list size: %d\n", ll_size(list));
    printf("  top: %p  bottom: %p\n", list->top, list->bottom);

    node=list->top;
    while(node)
    {
        printf("    node %p data %p (%d)\n", node, node->data, *(int*)node->data);
        node=node->next;
    }
}

int main(int argc, char *argv[])
{
    ll_error error;
    linked_list *list;
    int *i, j;

    /**************************************************************************/
    puts("#### create & delete");
    list=ll_new();
    if(!list)
        puts("failed to create list");

    print_list(list);

    error=ll_delete(list, data_free);
    printf("delete error %d\n", error);

    /**************************************************************************/
    puts("\n#### create, append & delete");
    list=ll_new();
    if(!list)
        puts("failed to create list");

    i=malloc(sizeof(int));
    if(!i)
        puts("malloc failed");
    *i=12;
    error=ll_append(list, i);
    printf("append error %d\n", error);
    print_list(list);

    error=ll_delete(list, data_free);
    printf("delete error %d\n", error);

    /**************************************************************************/
    puts("\n#### create, insert & delete");
    list=ll_new();
    if(!list)
        puts("failed to create list");

    i=malloc(sizeof(int));
    if(!i)
        puts("malloc failed");
    *i=12;
    error=ll_insert(list, i, 0);
    printf("insert at 0 error %d\n", error);
    print_list(list);

    i=malloc(sizeof(int));
    if(!i)
        puts("malloc failed");
    *i=13;
    error=ll_insert(list, i, 0);
    printf("insert at 0 error %d\n", error);
    print_list(list);

    i=malloc(sizeof(int));
    if(!i)
        puts("malloc failed");
    *i=14;
    error=ll_insert(list, i, 1);
    printf("insert at 1 error %d\n", error);
    print_list(list);

    error=ll_delete(list, data_free);
    printf("delete error %d\n", error);

    /**************************************************************************/
    puts("\n#### queue");
    list=ll_new();
    if(!list)
        puts("failed to create list");

    /* insert 10 at start */
    for(j=0; j<10; ++j)
    {
        i=malloc(sizeof(int));
        if(!i)
            puts("malloc failed");
        *i=1+j;
        error=ll_insert(list, i, 0);
        if(error!=ll_ESUCCESS)
            printf("insert %d error %d\n", j, error);
    }

    /* add one and remove one */
    for(j=0; j<10; ++j)
    {
        i=malloc(sizeof(int));
        if(!i)
            puts("malloc failed");
        *i=10+j;
        error=ll_insert(list, i, 0);
        if(error!=ll_ESUCCESS)
            printf("insert %d error %d\n", j+10, error);
        error=ll_remove(list, ll_size(list)-1, (void**)&i);
        if(error!=ll_ESUCCESS)
            printf("remove %d error %d\n", j, error);
        if(*i!=1+j)
            printf("data %d\n", *i);
        free(i);
    }

    /* delete remaining */
    print_list(list);
    error=ll_delete(list, data_free);
    printf("delete error %d\n", error);

    return 0;
}

