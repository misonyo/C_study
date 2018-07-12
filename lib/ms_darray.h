/*
 * ms_darray.h
 *
 *  Created on: 2018Äê7ÔÂ6ÈÕ
 *      Author: misonyo
 */

#ifndef LIB_MS_DARRAY_H_
#define LIB_MS_DARRAY_H_

#include "ms_def.h"

typedef void     (*data_destroy_func)(void* ctx, void* data);
typedef int      (*data_compare_func)(void* ctx, void* data);
typedef ret      (*data_visit_func)(void* ctx, void* data);

struct darray
{
    void** p_array;
    ms_uint32_t used_num;
    ms_uint32_t total_num;

    void* data_destroy_ctx;
    data_destroy_func data_destroy;
};

struct darray* darray_create(data_destroy_func data_destroy, void* ctx);
ms_uint32_t    darray_expand(struct darray* this, ms_uint32_t expand_num);
ret            darray_insert(struct darray* this, ms_uint32_t index, void* data);
ret            darray_append(struct darray* this, void* data);
ret            darray_delete(struct darray* this, ms_uint32_t index);
ret            darray_shrink(struct darray* this);
ret            darray_get_by_index(struct darray* this, ms_uint32_t index, void** data);
ret            darray_set_by_index(struct darray* this, ms_uint32_t index, void* data);
ms_uint32_t    darray_used_num(struct darray* this);
ms_uint32_t    darray_find(struct darray* this, data_compare_func cmp, void* ctx);
ret            darray_foreach(struct darray* this, data_visit_func visit, void* ctx);
void           darray_destroy(struct darray* this);

void           bubble_sort_ascending(void** p_array);
void           bubble_sort_descending(void** p_array);
ms_int32_t     bin_search(void** p_array);


#endif /* LIB_MS_DARRAY_H_ */
