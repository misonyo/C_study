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
    struct dlist_node *next;                          /**< point to next node. */
    struct dlist_node *prev;                          /**< point to prev node. */
};
typedef struct dlist_node dlist_t;                  /**< Type for double linked lists. */

/**
 * Single List structure
 */
struct slist_node
{
    struct slist_node *next;                         /**< point to next node. */
};
typedef struct slist_node slist_t;                /**< Type for single linked list. */





#endif /* LIST_H_ */
