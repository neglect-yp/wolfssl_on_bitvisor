#include <lib_printf.h>
#include <lib_syscalls.h>

int
_start (int a1, int a2)
{
    int d = msgopen("get_time");
    if (d < 0) {
        printf("get_time not found.\n");
        exitprocess(1);
    }
    printf("%d\n", msgsendint(d, 0));
    msgclose(d);
    exitprocess(0);
    return 0;
}
