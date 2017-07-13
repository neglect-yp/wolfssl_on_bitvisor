#include <lib_lineinput.h>
#include <lib_printf.h>
#include <lib_syscalls.h>

typedef struct {
    char ip[16];
    int port;
} S;

int
_start (int a1, int a2)
{
    S s;
    char buf[6];

    int d = msgopen("wc_test");
    if (d < 0) {
        printf("wc_test not found.\n");
        exitprocess(1);
    }
    
    /*
    //TODO: validation check
    printf("ip> ");
    lineinputi(s.ip, 16);
    printf("port> ");
    lineinput(buf, 6);
    s.port = stol(buf, NULL, 10);
    
    struct msgbuf mbuf;
    setmsgbuf(&mbuf, &s, sizeof(S*), 0);
    printf("%d\n", msgsendbuf(d, 0, &mbuf, 1));
    */

    printf("%d\n", msgsendint(d, 0));

    msgclose(d);
    exitprocess(0);
    return 0;
}
