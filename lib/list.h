/*
 * list.h
 *
 *  Created on: 2018Äê6ÔÂ27ÈÕ
 *      Author: misonyo
 */

#ifndef LIST_H_
#define LIST_H_

/**
 * Double List structure
 */
struct dlist_node
{
    struct dlist_node* next;                          /**< point to next node. */
    struct dlist_node* prev;                          /**< point to prev node. */
    void* data;
};
typedef struct dlist_node dlist_t;                  /**< Type for double linked lists. */

/**
 * Single List structure
 */
struct slist_node
{
    struct slist_node* next;                         /**< point to next node. */
};
typedef struct slist_node slist_t;                /**< Type for single linked list. */

typedef void (*dlist_func)(void* ctx,void* data);

struct dlist_node* dlist_init(int node_num);
void dlist_insert_before(struct dlist_node* node, struct dlist_node* new_node);
void dlist_insert_after(struct dlist_node* node, struct dlist_node* new_node);
void dlist_insert_head(struct dlist_node* list_head, struct dlist_node* new_node);
void dlist_insert_tail(struct dlist_node* list_head, struct dlist_node* new_node);
void dlist_foreach(struct dlist_node* list_head,dlist_func visit,void* ctx);
void print_int(void* ctx, void* data);
void find_max(void* ctx, void* data);
void cal_total(void* ctx, void* data);
void str_toupper(void* ctx, void* data);
void print_str(void* ctx, void* data);





#endif /* LIST_H_ */
