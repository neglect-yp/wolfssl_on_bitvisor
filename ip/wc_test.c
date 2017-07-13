#include <lwip/sockets.h>
#include <wolfssl/ssl.h>

#include "../core/initfunc.h"

#define USE_CERT_BUFFERS_2048
#include <wolfssl/certs_test.h>

typedef struct {
    char ip[16];
    int port;
} S;

static int
wc_test(char *ip, int port)
{
    // int sockfd;
    WOLFSSL_CTX* ctx;
    WOLFSSL* ssl;
    WOLFSSL_METHOD* method;
    struct sockaddr_in servaddr;
    const char message[] = "Hello, World!";
    
	/* create and set up socket */
    // sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = inet_addr(ip);

    /* connect to socket */
    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    /* initialize wolfssl library */
    wolfSSL_Init();
    method = wolfTLSv1_2_client_method(); /* use TLS v1.2 */

    /* make new ssl context */
    if ( (ctx = wolfSSL_CTX_new(method)) == NULL) {
        return 1;
    }

    wolfSSL_SetIORecv(ctx, );
    wolfSSL_SetIOSend(ctx, );

    /* make new wolfSSL struct */
    if ( (ssl = wolfSSL_new(ctx)) == NULL) {
        return 2;
    }

    /* Add cert to ctx */
    if (wolfSSL_CTX_load_verify_buffer(ctx, ca_cert_der_2048,
                sizeof_ca_cert_der_2048, SSL_FILETYPE_ASN1) != SSL_SUCCESS) {
        return 3;
    }

    /* Connect wolfssl to the socket, server, then send message */
    // wolfSSL_set_fd(ssl, sockfd);
    wolfSSL_connect(ssl);
    wolfSSL_write(ssl, message, strlen(message));

    /* frees all data before client termination */
    wolfSSL_free(ssl);
    wolfSSL_CTX_free(ctx);
    wolfSSL_Cleanup();

    return 0;
}

static int
wc_test_msghandler(int m, int c, struct msgbuf *buf, int bufcnt)
{
    if (m != MSG_BUF)
        return -1;
    if (bufcnt != 1)
        return -1;
    S s = *((S *)buf->base);
    return s.port;
}

static void
wc_test_init_msg (void)
{
    msgregister("wc_test", wc_test_msghandler);
}

INITFUNC("msg0", wc_test_init_msg);
