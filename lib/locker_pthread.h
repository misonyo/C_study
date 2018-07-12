/*
 * locker_pthread.h
 *
 *  Created on: 2018Äê7ÔÂ12ÈÕ
 *      Author: misonyo
 */

#ifndef LIB_LOCKER_PTHREAD_H_
#define LIB_LOCKER_PTHREAD_H_

typedef int (*tasf_self_func)(void);

struct locker
{
    pthread_mutex_t p_mutex;

    ret (*lock)(struct locker* thiz);
    ret (*unlock)(struct locker* thiz);
    void (*destroy)(struct locker* thiz);
};

static inline ret locker_lock(struct locker* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->lock != NULL, RET_INVALID_PARAMS);

    return thiz->lock(thiz);
}

static inline ret locker_unlock(struct locker* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->unlock != NULL, RET_INVALID_PARAMS);

    return thiz->unlock(thiz);
}

static inline void locker_destroy(struct locker* thiz)
{
    return_if_fail(thiz != NULL && thiz->destroy != NULL);

    thiz->destroy(thiz);

    return;
}

struct locker* locker_pthread_create(void);



#endif /* LIB_LOCKER_PTHREAD_H_ */
