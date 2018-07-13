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

#include "locker_pthread.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */

/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */

/* ============================ [ LOCALS    ] ====================================================== */

/* ============================ [ FUNCTIONS ] ====================================================== */

static ret locker_pthread_lock(struct locker* thiz)
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

static ret locker_pthread_unlock(struct locker* thiz)
{
    ret result = RET_OK;

    if (thiz->owner == thiz->task_self_func)
    {
        thiz->ref_count --;

        if (0 == thiz->ref_count)
        {
            thiz->owner = NULL;
            result =  pthread_mutex_lock(&thiz->p_mutex);
        }
    }
    else
    {
        result = RET_INVALID_PARAMS;
    }

    return result;
}

static ret locker_pthread_destroy(struct locker* thiz)
{
    ret result = RET_OK;

    result = pthread_mutex_destroy(&thiz->p_mutex);

    if (0 == result)
    {
        SAFE_FREE(thiz);
    }

    return result == 0 ? RET_OK : RET_FAIL;
}

struct locker* locker_pthread_create(int (*task_self_func)(void))
{
    struct locker* new_locker;

    new_locker = (struct locker*)malloc(sizeof(struct locker));

    if (new_locker != NULL)
    {
        pthread_mutex_init(&new_locker->p_mutex,NULL);
        new_locker->owner = NULL;
        new_locker->ref_count = 0;
        new_locker->task_self_func = task_self_func;

        new_locker->lock = locker_pthread_lock;
        new_locker->unlock = locker_pthread_unlock;
        new_locker->destroy = locker_pthread_destroy;
    }

    return new_locker;
}
