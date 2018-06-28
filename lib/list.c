/*
 * list.c
 *
 *  Created on: 2018Äê6ÔÂ27ÈÕ
 *      Author: misonyo
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stdint.h>

#include <assert.h>
#include "list.h"

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */

struct dlist_node* dlist_init(void)
{
    struct dlist_node* list_head = NULL;

    list_head = malloc(sizeof(struct dlist_node));

    list_head->next = NULL;
    list_head->prev = NULL;
    list_head->data = NULL;

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

void dlist_print(struct dlist_node* list_head,dlist_data_print print_func)
{
    struct dlist_node* temp = list_head;

    do{
        print_func(temp->data);
        temp = temp->next;
    }while(temp != list_head);
}

void print_int(void* data)
{
    printf("%d\n",(int)data);
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
