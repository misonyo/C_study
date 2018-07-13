/*
 * list.c
 *
 *  Created on: 2018Äê6ÔÂ27ÈÕ
 *      Author: misonyo
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "list.h"

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */

struct dlist_node* dlist_create_node(void* data)
{
    struct dlist_node* new_node;

    new_node = (struct dlist_node*)malloc(sizeof(struct dlist_node));
    new_node->next = new_node;
    new_node->prev = new_node;
    new_node->data = data;

    return new_node;
}

void dlist_delete_node(struct dlist_node* node)
{
     node->prev = node->next;
     node->next = node->prev;
     free(node);
}

struct dlist_node* dlist_get_node(struct dlist_tcb* thiz, ms_int32_t index)
{
    struct dlist_node* index_node = NULL;

    if ((index <= thiz->node_count) && (index > 0))
    {
        for (index_node = thiz->first; index_node != thiz->first; index_node = index_node->next)
        {
            if (1 == index)
            {
                break;
            }
            index --;
        }
    }

    return index_node;
}
struct dlist_tcb* dlist_create(void (*data_destroy_func)(void* ctx, void* data), void* ctx, struct locker* locker)
{
    struct dlist_tcb* new_dlist_tcb;

    new_dlist_tcb = (struct dlist_tcb*)malloc(sizeof(struct dlist_tcb));

    if (new_dlist_tcb != NULL)
    {
        new_dlist_tcb->data_destroy_ctx = ctx;
        new_dlist_tcb->data_destroy_func = data_destroy_func;
        new_dlist_tcb->first = NULL;
        new_dlist_tcb->locker = locker;
        new_dlist_tcb->node_count = 0;
    }

    return new_dlist_tcb;
}

ret dlist_insert(struct dlist_tcb* thiz, ms_int32_t index, void* data)
{
    struct dlist_node* new_node = NULL;
    struct dlist_node* index_node = NULL;
    ret result = RET_OK;
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    do
    {
        new_node = dlist_create_node(data);

        if (NULL == new_node)
        {
            result = RET_FAIL;
            break;
        }

        thiz->locker->lock(thiz->locker);

        if (NULL == thiz->first)
        {
            thiz->first = new_node;
            thiz->node_count ++;
            break;
        }

        index_node = dlist_get_node(thiz, index);
        if (index_node != NULL)
        {
            dlist_insert_before(index_node, new_node);
        }
        else
        {
            if (thiz->first->prev != NULL)
            {
                dlist_insert_after(thiz->first->prev,index_node);
            }
            else
            {
                dlist_insert_after(thiz->first,index_node);
            }
        }
    }while(0);

    thiz->locker->unlock(thiz->locker);

    return result;
}
ret dlist_prepend(struct dlist_tcb* thiz, void* data)
{
    return dlist_insert(thiz, 1, data);
}
ret dlist_append(struct dlist_tcb* thiz, void* data)
{
    return dlist_insert(thiz, -1, data);
}

ret dlist_get_by_index(struct dlist_tcb* thiz, size_t index, void** data)
{
    ret result = RET_OK;
    struct dlist_node* index_node = NULL;

    thiz->locker->lock(thiz->locker);
    index_node = dlist_get_node(thiz, index);
    thiz->locker->unlock(thiz->locker);

    if (index_node != NULL)
    {
        *data = index_node->data;
    }
    else
    {
        result = RET_INVALID_PARAMS;
    }

    return result;
}

ret dlist_set_by_index(struct dlist_tcb* thiz, size_t index, void* data)
{
    ret result = RET_OK;
    struct dlist_node* index_node = NULL;

    thiz->locker->lock(thiz->locker);
    index_node = dlist_get_node(thiz, index);
    thiz->locker->unlock(thiz->locker);

    if (index_node != NULL)
    {
        index_node->data = data;
    }
    else
    {
        result = RET_INVALID_PARAMS;
    }
    return result;
}


struct dlist_node* dlist_init(int node_num)
{
    struct dlist_node* new_node, *list_head;
    int n;

    for (n=0;n<node_num;n++)
    {
        if (0 == n)
        {
            list_head = (struct dlist_node*)malloc(sizeof(struct dlist_node));
            list_head->next = list_head;
            list_head->prev = list_head;
            list_head->data = NULL;
        }
        else
        {
            new_node = (struct dlist_node*)malloc(sizeof(struct dlist_node));
            new_node->data = NULL;

            dlist_insert_after(list_head,new_node);
        }
    }

    return list_head;
}



/**
 * @brief insert a node before a list
 *
 * @param new_node: new node to be inserted
 * @param list: list to insert it
 */
void dlist_insert_before(struct dlist_node* node,struct dlist_node* new_node)
{
    new_node->next = node;
    new_node->prev = node->prev;

    node->prev->next = new_node;
    node->prev = new_node;
}

void dlist_insert_after(struct dlist_node* node,struct dlist_node* new_node)
{
    new_node->next = node->next;
    new_node->prev = node;

    node->next->prev = new_node;
    node->next = new_node;
}

void dlist_insert_head(struct dlist_node* list_head,struct dlist_node* new_node)
{
    new_node->next = list_head;
    new_node->prev = list_head->prev;

    list_head->prev->next = new_node;
    list_head->prev = new_node;

    list_head = new_node;
}

void dlist_insert_tail(struct dlist_node* list_head,struct dlist_node* new_node)
{
    new_node->next = list_head;
    new_node->prev = list_head->prev;

    list_head->prev->next = new_node;
    list_head->prev = new_node;
}

void dlist_foreach(struct dlist_node* list_head,void (*dlist_func)(void* ctx,void* data),void* ctx)
{
    struct dlist_node* temp = list_head;

    do{
        dlist_func(ctx, temp->data);
        temp = temp->next;
    }while(temp != list_head);
}

void print_int(void* ctx, void* data)
{
    printf("%d  ",(int)data);
}

void find_max(void* ctx, void* data)
{

    if ((int)data > *((int*)ctx))
    {
        *(int*)ctx = (int)data;
    }

}

void cal_total(void* ctx, void* data)
{
    (*(int*)ctx) += (int)data;
}

void print_str(void* ctx, void* data)
{
    printf("%s  ",(char*)data);
}

void str_toupper(void* ctx, void* data)
{
    char* str = data;

    int n = 0;
    char temp;

    while(str[n] != '\0')
    {
        temp = toupper(str[n]);
        str[n] = temp;
        n++;
    }
}
void slist_init(struct dlist_node* list)
{
    list->next = NULL;

}

void slist_insert_after(struct slist_node* node,struct slist_node* new_node)
{
    new_node->next = node->next;
    node->next = new_node;
}

void slist_insert_head(struct slist_node* list_head,struct slist_node* new_node)
{
    new_node->next = list_head;
    list_head = new_node;
}

void slist_insert_tail(struct slist_node* list_tail,struct slist_node* new_node)
{
    new_node->next = NULL;
    list_tail->next = new_node;
    list_tail = new_node;
}
