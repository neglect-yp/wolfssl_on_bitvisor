#include <core/process.h>
#include <core/initfunc.h>
#include "../core/asm.h"

static int
get_thermal(int m, int i) {
    unsigned int a, d;
    asm_rdmsr32(0x19c, &a, &d);
    return a;
}

static void
thermal_init_msg() {
    msgregister("thermal", get_thermal);
}

INITFUNC("msg0", thermal_init_msg);
