/*
 * allocator.h
 *
 *  Created on: 2018Äê7ÔÂ6ÈÕ
 *      Author: misonyo
 */

/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "allocator.h"

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */

void* allo_calloc(ms_int32_t nmemb, ms_int32_t size)
{
    return calloc(nmemb, size);
}
void* allo_malloc(ms_int32_t size)
{
    return malloc(size);
}
void allo_free(void *ptr)
{
    free(ptr);
}
void* allo_realloc(void *ptr, ms_int32_t size)
{
    return realloc(ptr, size);
}

