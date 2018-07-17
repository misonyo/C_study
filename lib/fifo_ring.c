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
    ms_uint32_t r_cursor;
    ms_uint32_t w_cursor;
    ms_uint32_t data_count;
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
        new->data_count = 0;
        new->length = length;
    }

    return new;
}

ret fifo_ring_push(struct fifo_ring* thiz, void* data)
{
    ret result = RET_FAIL;

    if (thiz->data_count < thiz->length)
    {
        thiz->data[thiz->w_cursor] = data;
        thiz->w_cursor ++;
        thiz->data_count ++;
        if (thiz->w_cursor == thiz->length)
        {
            thiz->w_cursor = 0;
        }
        result = RET_OK;
    }

    return result;
}

ret fifo_ring_pop(struct fifo_ring* thiz, void** data)
{
    ret result = RET_FAIL;

    if (thiz->data_count != 0)
    {
        *data = thiz->data[thiz->r_cursor];
        thiz->r_cursor ++;
        thiz->data_count --;
        if (thiz->r_cursor == thiz->length)
        {
            thiz->r_cursor = 0;
        }
        result = RET_OK;
    }

    return result;
}
