#include <lib_printf.h>
#include <lib_syscalls.h>

int
_start (int a1, int a2)
{
    int d = msgopen("thermal");
    if (d < 0) {
        printf("thermal not found.\n");
        exitprocess(1);
    }
    printf("%08x\n", msgsendint(d, 0));
    exitprocess(0);
    return 0;
}
