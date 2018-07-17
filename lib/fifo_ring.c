/*
 * locker_pthread.c
 *
 *  Created on: 2018Äê7ÔÂ6ÈÕ
 *      Author: misonyo
 */

/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ms_def.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
struct fifo_ring
{
    int r_cursor;
    int w_cursor;
    ms_uint32_t length;
    void* data[0];
};
/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */

struct fifo_ring* fifo_ring_create(ms_uint32_t length)
{
    struct fifo_ring* new;

    new = malloc(sizeof((struct fifo_ring) + length));

    if (new != NULL)
    {
        new->r_cursor = 0;
        new->w_cursor = 0;
        new->length = length;
    }

    return new;
}

ret fifo_ring_push(struct fifo_ring* thiz, void* data)
{
    if (thiz->w_cursor < thiz->length)
    {
        thiz->data[thiz->w_cursor] = data;
        thiz->w_cursor ++;
    }
}
