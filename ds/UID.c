#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "UID.h"

const UID_t BAD_UID = {0, 0, 0};
/**************************************************************
* Initializes the necessary fields for the UID	               *
* Return Value:The UID.                                        *
***************************************************************/

UID_t UIDCreate()
{
    UID_t uid;
    static size_t counter = 1;

    uid.time_stamp = time(NULL);
    uid.counter = counter;
    uid.pid = getppid();

    ++counter;

    return (uid);
}

/***************************************************************
 * Checks if one UID is identical to another one               *
   Return Value: 1 - if true, 0 - if false                     *
   ************************************************************/
int UIDIsSame(const UID_t uid1, const UID_t uid2)
{
    return ((uid1.time_stamp == uid2.time_stamp) &&
            (uid1.counter == uid2.counter) &&
            (uid1.pid == uid2.pid));
}

/***************************************************************
 * Checks if one UID is an invalid UID                         *
   Return Value: 1 - if true, 0 - if false                     *
   ************************************************************/
int UIDISBad(const UID_t uid)
{
    return (!UIDIsSame(BAD_UID, uid));
}
