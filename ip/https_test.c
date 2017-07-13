#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <core/mm.h>
#include <core/process.h>
#include <core/initfunc.h>
#include <core/printf.h>

#include "tcpip.h"
#include "https_test.h"

int https_test(int m, int i)
{
    int ipaddr[] = {133, 130, 101, 146}; // neglect-yp.xyz
    // int ipaddr[] = {216, 58, 197, 131}; // google.co.jp
    // int ipaddr[] = {10, 6, 18, 156};
    int port = 443;
    struct arg *a;
    
    a = alloc(sizeof *a);
    if (a) {
        for (int i = 0; i < 4; i++)
            a->ipaddr_a[i] = ipaddr[i];
        a->port = port;
        tcpip_begin(tcp_client_init, a);
    } else {
        return -1;
    }

    https_test_init(NULL);

    return 0;
}


static void wc_test_init_msg (void)
{
    msgregister("wc_test", https_test);
}

INITFUNC("msg0", wc_test_init_msg);
