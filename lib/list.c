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

void dlist_foreach(struct dlist_node* list_head,dlist_func visit,void* ctx)
{
    struct dlist_node* temp = list_head;

    do{
        visit(ctx, temp->data);
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
