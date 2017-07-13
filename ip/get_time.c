#include <core/process.h>
#include <core/initfunc.h>
#include "bios_time.h"

static time_t
get_time(int m, int i) {
    return time(0);
}

static void
get_time_init_msg() {
    msgregister("get_time", get_time);
}

INITFUNC("msg0", get_time_init_msg);
