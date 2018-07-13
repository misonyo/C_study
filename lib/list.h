/*
 * list.h
 *
 *  Created on: 2018Äê6ÔÂ27ÈÕ
 *      Author: misonyo
 */

#ifndef LIST_H_
#define LIST_H_

#include "locker_pthread.h"
#include "ms_def.h"

/**
 * Double List structure
 */
struct dlist_node
{
    struct dlist_node* next;                          /**< point to next node. */
    struct dlist_node* prev;                          /**< point to prev node. */
    void* data;
};

struct dlist_tcb
{
    struct locker* locker;
    struct dlist_node* first;
    ms_uint32_t node_count;
    void* data_destroy_ctx;
    void (*data_destroy_func)(void* ctx, void* data);
};

/**
 * Single List structure
 */
struct slist_node
{
    struct slist_node* next;                         /**< point to next node. */
};
typedef struct slist_node slist_t;                /**< Type for single linked list. */

struct dlist_tcb*       dlist_create(void (*data_destroy_func)(void* ctx, void* data), void* ctx, struct locker* locker);
ret                     dlist_insert(struct dlist_tcb* thiz, ms_int32_t index, void* data);
ret                     dlist_prepend(struct dlist_tcb* thiz, void* data);
ret                     dlist_append(struct dlist_tcb* thiz, void* data);
ret                     dlist_get_by_index(struct dlist_tcb* thiz, size_t index, void** data);
ret                     dlist_set_by_index(struct dlist_tcb* thiz, size_t index, void* data);
ms_int32_t              dlist_length(DList* thiz);
ms_int32_t              dlist_find(DList* thiz, DListDataCompareFunc cmp, void* ctx);
ret                     dlist_foreach(DList* thiz, DListDataVisitFunc visit, void* ctx);


struct dlist_node*      dlist_init(int node_num);
struct dlist_node*      dlist_create_node(void* data);
void                    dlist_delete_node(struct dlist_node* node);
void                    dlist_insert_before(struct dlist_node* node, struct dlist_node* new_node);
void                    dlist_insert_after(struct dlist_node* node, struct dlist_node* new_node);
void                    dlist_insert_head(struct dlist_node* list_head, struct dlist_node* new_node);
void                    dlist_insert_tail(struct dlist_node* list_head, struct dlist_node* new_node);
void                    dlist_foreach(struct dlist_node* list_head,void (*dlist_func)(void* ctx,void* data),void* ctx);
void                    print_int(void* ctx, void* data);
void                    find_max(void* ctx, void* data);
void                    cal_total(void* ctx, void* data);
void                    str_toupper(void* ctx, void* data);
void                    print_str(void* ctx, void* data);





#endif /* LIST_H_ */
