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
    ret result;

    result =  pthread_mutex_lock(&thiz->p_mutex);

    return result == 0 ? RET_OK : RET_FAIL;
}

static ret locker_pthread_unlock(struct locker* thiz)
{
    ret result;

    result = pthread_mutex_unlock(&thiz->p_mutex);

    return result == 0 ? RET_OK : RET_FAIL;
}

static ret locker_pthread_destroy(struct locker* thiz)
{
    ret result;

    result = pthread_mutex_destroy(&thiz->p_mutex);

    if (0 == result)
    {
        SAFE_FREE(thiz);
    }

    return result == 0 ? RET_OK : RET_FAIL;
}

struct locker* locker_pthread_create(void)
{
    struct locker* new_locker;

    new_locker = (struct locker*)malloc(sizeof(struct locker));

    if (new_locker != NULL)
    {
        pthread_mutex_init(&new_locker->p_mutex,NULL);
        new_locker->lock = locker_pthread_lock;
        new_locker->unlock = locker_pthread_unlock;
        new_locker->destroy = locker_pthread_destroy;
    }

    return new_locker;
}
