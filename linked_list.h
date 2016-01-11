#pragma once

#include <stdint.h>

typedef struct linked_list_node linked_list_node;
struct linked_list_node{
    void *data;
    linked_list_node *next;
};

typedef struct{
    linked_list_node *top;
    linked_list_node *bottom;
    uint32_t size;
} linked_list;

typedef enum{
    ll_ESUCCESS=0,
    ll_ENOLIST=-1,
    ll_ENODECREATIONFAILED=-2,
    ll_EMISSINGNODE=-3,
    ll_EBOUNDS=-4,
    ll_ENOFUNCTION=-5
} ll_error;

typedef void (*ll_data_free_fn)(void*);

linked_list* ll_new(void);
ll_error ll_delete(linked_list *list, ll_data_free_fn data_free);

linked_list_node* ll_at(linked_list *list, uint32_t at);
#define ll_size(list) ((list)->size)

ll_error ll_append(linked_list *list, void *data);
ll_error ll_insert(linked_list *list, void *data, uint32_t at);
ll_error ll_remove(linked_list *list, uint32_t at, void **data);

ll_error ll_removef(linked_list *list, uint32_t at, ll_data_free_fn data_free);
