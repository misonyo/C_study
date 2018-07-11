/*
 * locker.h
 *
 *  Created on: 2018Äê7ÔÂ11ÈÕ
 *      Author: misonyo
 */

#ifndef LIB_LOCKER_H_
#define LIB_LOCKER_H_
#include "ms_def.h"

struct locker;

typedef ret (*lock_func)(struct locker* this);
typedef ret (*unlock_func)(struct locker* this);
typedef void (*destroy_func)(struct locker* this);

struct locker
{
    lock_func lock;
    unlock_func unlock;
    destroy_func destroy;
}

#endif /* LIB_LOCKER_H_ */
