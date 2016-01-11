#include "linked_list.h"
#include <stdint.h>
#include <stdlib.h>

linked_list* ll_new()
{
    return calloc(1, sizeof(linked_list));
}

ll_error ll_delete(linked_list *list, ll_data_free_fn data_free)
{
    if(!list)
        return ll_ENOLIST;

    if(!data_free)
        return ll_ENOFUNCTION;

    while(list->size)
    {
        ll_error error=ll_removef(list, 0, data_free);
        if(error!=ll_ESUCCESS)
            return error;
    }

    free(list);

    return ll_ESUCCESS;
}

static linked_list_node* new_node(void *data)
{
    linked_list_node *node=calloc(1, sizeof(linked_list_node));
    if(node)
        node->data=data;
    return node;
}

linked_list_node* ll_at(linked_list *list, uint32_t at)
{
    linked_list_node *node;
    uint32_t i;

    if(!list)
        return 0;

    if(at>=list->size || !list->size)
        return 0;

    if(!at)
        return list->top;
    if(at==(list->size-1))
        return list->bottom;

    for(node=list->top, i=0; node->next && i<at; node=node->next, ++i) ;

    if(i!=at)
        return 0;

    return node;
}

ll_error ll_append(linked_list *list, void *data)
{
    linked_list_node *node;

    if(!list)
        return ll_ENOLIST;

    if(!list->size)
    {
        list->bottom=list->top=new_node(data);
        if(!list->top)
            return ll_ENODECREATIONFAILED;
        ++list->size;
        return ll_ESUCCESS;
    }

    node=list->bottom;
    node->next=new_node(data);
    if(!node->next)
        return ll_ENODECREATIONFAILED;
    list->bottom=node->next;
    ++list->size;
    return ll_ESUCCESS;
}

ll_error ll_insert(linked_list *list, void *data, uint32_t at)
{
    linked_list_node *node, *next_node;

    if(!list)
        return ll_ENOLIST;

    if(!at)
    {
        node=new_node(data);
        if(!node)
            return ll_ENODECREATIONFAILED;
        node->next=list->top;
        list->top=node;
        if(!list->size)
            list->bottom=list->top;
        ++list->size;
        return ll_ESUCCESS;
    }

    if(at>=list->size)
        return ll_append(list, data);

    node=ll_at(list, at-1);
    if(!node)
        return ll_EMISSINGNODE;

    next_node=node->next;
    node->next=new_node(data);
    if(!node->next)
    {
        node->next=next_node;
        return ll_ENODECREATIONFAILED;
    }
    node->next->next=next_node;
    ++list->size;
    return ll_ESUCCESS;
}

ll_error ll_remove(linked_list *list, uint32_t at, void **data)
{
    linked_list_node *node, *next_node;

    if(!list)
        return ll_ENOLIST;

    if(at>=list->size)
        return ll_EBOUNDS;

    if(!at)
    {
        node=list->top;
        list->top=node->next;
        *data=node->data;
        free(node);
        --list->size;
        return ll_ESUCCESS;
    }

    node=ll_at(list, at-1);
    if(!node)
        return ll_EMISSINGNODE;

    *data=node->next->data;
    next_node=node->next->next;
    free(node->next);
    node->next=next_node;
    --list->size;
    if(at==list->size)
        list->bottom=node;
    return ll_ESUCCESS;
}

ll_error ll_removef(linked_list *list, uint32_t at, ll_data_free_fn data_free)
{
    void *data=0;
    ll_error error;

    if(!list)
        return ll_ENOLIST;

    if(!data_free)
        return ll_ENOFUNCTION;

    error=ll_remove(list, at, &data);
    if(error!=ll_ESUCCESS)
        return error;
    data_free(data);

    return ll_ESUCCESS;
}
