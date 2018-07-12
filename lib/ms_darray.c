/*
 * ms_darray.c
 *
 *  Created on: 2018Äê7ÔÂ6ÈÕ
 *      Author: misonyo
 */

/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ms_darray.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */

struct darray* darray_create(data_destroy_func data_destroy, ms_uint32_t init_num,void* ctx)
{
    struct darray* new_darray = malloc(sizeof(struct darray));
    struct darray* result;

    if (NULL != new_darray)
    {
        new_darray->data_destroy = data_destroy;
        new_darray->data_destroy_ctx = ctx;
        new_darray->used_num = 0;

        void** mem = (void**)malloc(sizeof(void*) * init_num);
        if(mem != NULL)
        {
            new_darray->p_array = mem;
            new_darray->total_num = init_num;
        }
        else
        {
            free(new_darray);
            new_darray = NULL;
        }
    }

    return new_darray;
}

ms_uint32_t darray_expand(struct darray* this, ms_uint32_t expand_num)
{
    RETURN_IF_FAIL(this != NULL, RET_INVALID_PARAMS);

    ms_uint32_t num, new_total_num, result;

    num = (expand_num < 20) ? 20 : expand_num;
    new_total_num = this->total_num + num;
    void** mem = (void**)realloc(this->p_array, sizeof(void*) * new_total_num);
    if(mem != NULL)
    {
        this->p_array = mem;
        this->total_num = new_total_num;
        result = this->total_num;
    }
    else
    {
        result = 0;
    }
    return result;
}

ms_int32_t darray_insert(struct darray* this, ms_uint32_t index, void* data)
{
    RETURN_IF_FAIL((this != NULL) && (this->used_num < this->total_num), RET_INVALID_PARAMS);

    ms_int32_t n, actual_index = -1;
    if (this->used_num < this->total_num)
    {
        if(index <= this->used_num)
        {
            for(n = this->used_num;n > index;n--)
            {
                this->p_array[n+1] = this->p_array[n];
            }

            this->p_array[index] = data;
            actual_index = index;
        }
        else
        {
            this->p_array[this->used_num + 1] = data;
            actual_index = this->used_num + 1;
        }

        this->used_num ++;
        if(this->used_num == this->total_num)
        {
            printf("array is full of data,please expand it!\n");
        }

    }
    else
    {
        printf("array is full of data,please expand it!\n");
    }

    return actual_index;
}

ret darray_append(struct darray* this, void* data)
{
    RETURN_IF_FAIL((this != NULL) && (this->used_num < this->total_num), RET_INVALID_PARAMS);
    ret result = RET_OK;
    if (this->used_num < this->total_num)
    {
        this->p_array[this->used_num + 1] = data;
        if(this->used_num == this->total_num)
        {
            printf("array is full of data,please expand it!\n");
        }
    }
    else
    {
        result = RET_INVALID_PARAMS;
    }

    return result;
}

ret darray_delete(struct darray* this, ms_uint32_t index)
{
    RETURN_IF_FAIL(this != NULL, RET_INVALID_PARAMS);
    ret result = RET_OK;
    ms_uint32_t n;

    if (index <= this->used_num)
    {
        for(n = index;n < this->used_num; n++)
        {
            this->p_array[n] = this->p_array[n+1];
        }

        this->used_num --;
        if(0 == this->used_num)
        {
            printf("the array is empty now!\n");
        }
    }
    else
    {
        result = RET_INVALID_PARAMS;
    }

    return result;
}

ms_int32_t darray_shrink(struct darray* this,ms_uint32_t shrink_num)
{
    RETURN_IF_FAIL(this != NULL, RET_INVALID_PARAMS);
    ms_uint32_t new_total_num;
    ms_int32_t remained_num = -1;

    if(shrink_num <= (this->total_num - this->used_num))
    {
        new_total_num = this->total_num - shrink_num;

        void** mem = (void**)realloc(this->p_array, sizeof(void*) * new_total_num);
        if(mem != NULL)
        {
            this->p_array = mem;
            this->total_num = new_total_num;
            remained_num = this->total_num - this->used_num;
        }
    }
    else
    {
        printf("don't have enough memory to shrink!\n");
    }

    return remained_num;
}

void** darray_get_by_index(struct darray* this, ms_uint32_t index)
{
    void** data = NULL;
    if (index <= this->used_num)
    {
        data = this->p_array[index];
    }

    return data;
}
ret darray_set_by_index(struct darray* this, ms_uint32_t index, void* data)
{
    RETURN_IF_FAIL(this != NULL && index < this->used_num, RET_INVALID_PARAMS);

    this->p_array[index] = data;


    return RET_OK;
}
ms_uint32_t darray_used_num(struct darray* this)
{
    return this->used_num;
}
ms_uint32_t darray_find(struct darray* this, data_compare_func cmp, void* ctx)
{

}
ret darray_foreach(struct darray* this, data_visit_func visit, void* ctx)
{

}
void darray_destroy(struct darray* this)
{

}


void bubble_sort_ascending(struct darray* this)
{
    ms_uint32_t i, j, max_index;

    for(i = 0; i < (this->used_num -1); i++)
    {
        for(j = 1, max_index = 0; j < (this->used_num - i); j++)
        {
            if ((int)this->p_array[j] > (int)this->p_array[max_index])
            {
                max_index = j;
            }
        }

        if ((int)this->p_array[this->used_num -1] < (int)this->p_array[max_index])
        {
            void* temp = this->p_array[this->used_num -1];
            this->p_array[this->used_num -1] =  this->p_array[max_index];
            this->p_array[max_index] = temp;
        }
    }
}
void bubble_sort_descending(struct darray* this)
{
    ms_uint32_t i, j, min_index;

    for(i = 0; i < (this->used_num -1); i++)
    {
        for(j = 1, min_index = 0; j < (this->used_num - i); j++)
        {
            if ((ms_int32_t)this->p_array[j] < (ms_int32_t)this->p_array[min_index])
            {
                min_index = j;
            }
        }

        if ((ms_int32_t)this->p_array[this->used_num -1] > (ms_int32_t)this->p_array[min_index])
        {
            void* temp = this->p_array[this->used_num -1];
            this->p_array[this->used_num -1] =  this->p_array[min_index];
            this->p_array[min_index] = temp;
        }
    }
}

ms_int32_t bin_search(struct darray* this, void* data)
{
    ms_int32_t temp, low, mid, high, result;

    high = this->used_num +1;
    low = mid = result = 0;

    while(low <= high)
    {
        mid = low + (high - low) >> 1;
        result = (ms_int32_t)data > (ms_int32_t)this->p_array[mid];
        if (0 == result)
        {
            return mid;
        }
        else if(result > 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid -1;
        }
    }
    return -1;
}
