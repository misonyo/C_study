/*
 * allocator.h
 *
 *  Created on: 2018Äê7ÔÂ6ÈÕ
 *      Author: misonyo
 */

#ifndef LIB_ALLOCATOR_H_
#define LIB_ALLOCATOR_H_

#include "ms_def.h"

void* allo_calloc(ms_int32_t nmemb, ms_int32_t size);
void* allo_malloc(ms_int32_t size);
void allo_free(void *ptr);
void* allo_realloc(void *ptr, ms_int32_t size);


#endif /* LIB_ALLOCATOR_H_ */
