/*
 * nest_locker.h
 *
 *  Created on: 2018Äê7ÔÂ12ÈÕ
 *      Author: misonyo
 */

#ifndef LIB_NEST_LOCKER_H_
#define LIB_NEST_LOCKER_H_

#include "ms_def.h"
#include <pthread.h>

struct nest_locker
{
    pthread_mutex_t p_mutex;

    void* owner;
    ms_int8_t ref_count;
    void* (*task_self_func)(void);

    ret (*lock)(struct nest_locker* thiz);
    ret (*unlock)(struct nest_locker* thiz);
    void (*destroy)(struct nest_locker* thiz);
};

struct nest_locker* locker_nest_create(int (*task_self_func)(void));


#endif /* LIB_NEST_LOCKER_H_ */
