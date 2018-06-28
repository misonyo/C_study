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

typedef void (*dlist_data_print)(void* data);

void dlist_init(struct dlist_node* list);
void dlist_insert_before(struct dlist_node* node,struct dlist_node* new_node);
void dlist_insert_after(struct dlist_node* node,struct dlist_node* new_node);
void dlist_insert_head(struct dlist_node* list_head,struct dlist_node* new_node);
void dlist_insert_tail(struct dlist_node* list_head,struct dlist_node* new_node);
void dlist_print(struct dlist_node* list_head,dlist_data_print print_func);
void print_int(void* data);



#endif /* LIST_H_ */
