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

#include "nest_locker.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */

static ret nest_locker_lock(struct nest_locker* thiz)
{
    ret result = RET_OK;

    if (thiz->owner == thiz->task_self_func)
    {
        thiz->ref_count ++;
    }
    else
    {
        result =  pthread_mutex_lock(&thiz->p_mutex);
        if (RET_OK == result)
        {
            thiz->owner = thiz->task_self_func;
            thiz->ref_count = 1;
        }
    }

    return result;
}

static ret nest_locker_unlock(struct nest_locker* thiz)
{
    ret result = RET_OK;

    if (thiz->owner == thiz->task_self_func)
    {
        thiz->ref_count --;

        if (0 == thiz->ref_count)
        {
            thiz->owner = NULL;
            result =  pthread_mutex_unlock(&thiz->p_mutex);
        }
    }
    else
    {
        result = RET_INVALID_PARAMS;
    }

    return result;
}

static ret nest_locker_destroy(struct nest_locker* thiz)
{
    ret result = RET_OK;

    result = pthread_mutex_destroy(&thiz->p_mutex);

    if (0 == result)
    {
        SAFE_FREE(thiz);
    }

    return result == 0 ? RET_OK : RET_FAIL;
}

struct locker* nest_locker_create(int (*task_self_func)(void))
{
    struct nest_locker* new_locker;

    new_locker = (struct locker*)malloc(sizeof(struct nest_locker));

    if (new_locker != NULL)
    {
        pthread_mutex_init(&new_locker->p_mutex,NULL);
        new_locker->owner = NULL;
        new_locker->ref_count = 0;
        new_locker->task_self_func = task_self_func;

        new_locker->lock = nest_locker_lock;
        new_locker->unlock = nest_locker_unlock;
        new_locker->destroy = nest_locker_destroy;
    }

    return new_locker;
}
