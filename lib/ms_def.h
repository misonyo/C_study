/*
 * ms_def.h
 *
 *  Created on: 2018Äê7ÔÂ6ÈÕ
 *      Author: misonyo
 */

#ifndef LIB_MS_DEF_H_
#define LIB_MS_DEF_H_

#include <stdio.h>

/* MS basic data type definitions */
typedef signed   char                   ms_int8_t;      /**<  8bit integer type */
typedef signed   short                  ms_int16_t;     /**< 16bit integer type */
typedef signed   long                   ms_int32_t;     /**< 32bit integer type */
typedef unsigned char                   ms_uint8_t;     /**<  8bit unsigned integer type */
typedef unsigned short                  ms_uint16_t;    /**< 16bit unsigned integer type */
typedef unsigned long                   ms_uint32_t;    /**< 32bit unsigned integer type */
typedef int                             ms_bool_t;      /**< boolean type */


typedef enum
{
    RET_OK,
    RET_OOM,
    RET_STOP,
    RET_INVALID_PARAMS,
    RET_FAIL
}ret;

typedef void     (*data_destroy_func)(void* ctx, void* data);
typedef int      (*data_compare_func)(void* ctx, void* data);
typedef ret      (*data_visit_func)(void* ctx, void* data);
typedef int      (*data_hash_func)(void* data);

#define return_if_fail(p)                                               \
    if(!(p))                                                            \
    {                                                                   \
        printf("%s: %d warning: "#p" failed.\n",__func__,__LINE__);     \
        return;                                                         \
    }

#define return_val_if_fail(p,ret)                                       \
    if(!(p))                                                            \
    {                                                                   \
        printf("%s: %d warning: "#p" failed.\n",__func__,__LINE__);     \
        return (ret);                                                    \
    }

#define SAFE_FREE(p)    if(p != NULL)    {free(p); p = NULL;}
#endif /* LIB_MS_DEF_H_ */
