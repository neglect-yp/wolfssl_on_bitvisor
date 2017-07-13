#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/ssl.h>
#include <wolfssl/internal.h>
#define USE_CERT_BUFFERS_1024
#include <wolfssl/certs_test.h>

#include <core/thread.h>
#include <core/printf.h>

#include "bios_time.h"
#include "https_test.h"

static const char msg[] = "GET / HTTP/1.0\r\n\r\n";

static struct tcp_pcb *https_client_pcb;
static ip_addr_t destip;
static int destport;

static WOLFSSL_CTX* ctx = 0;
static WOLFSSL* ssl = 0;

static int connected = 0;

static err_t tcp_client_sent (void *arg, struct tcp_pcb *tpcb, u16_t len)
{
	printd ("Sent.\n");
	return ERR_OK;
}

static void tcp_client_error (void *arg, err_t err)
{
	printd ("Error: %d\n", err);
}

static err_t tcp_client_recv (void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
	int i;
	char *str;

	printd ("Received.\n");
	if (!p) {
		/* Disconnected by remote. */
		printd ("Disconnected!\n");
		https_client_pcb = NULL;
		return ERR_OK;
	} else if (err != ERR_OK) {
		/* Error occurred. */
		printd ("Error: %d\n", err);
		return err;
	} else {
		/* Really received. */
		tcp_recved (pcb, p->len);
		str = p->payload;
		for (i = 0; i < p->len; i++)
			printf ("%c", str[i]);
		return ERR_OK;
	}
}

static err_t tcp_client_connected (void *arg, struct tcp_pcb *pcb, err_t err)
{
	if (err == ERR_OK) {
		printf ("Connection established!\n");
		tcp_arg (pcb, NULL);
		tcp_sent (pcb, tcp_client_sent);
		tcp_recv (pcb, tcp_client_recv);
		tcp_err (pcb, tcp_client_error);
        connected = 1;
	} else {
		printf ("Connection missed!\n");
	}
	return ERR_OK;
}


void tcp_client_init (void *arg)
{
    struct arg *a = arg;
    int *ipaddr = a->ipaddr_a;
    int port = a->port;
    
	struct tcp_pcb *pcb;
	err_t e;

	IP4_ADDR (&destip,
		  ipaddr[0],
		  ipaddr[1],
		  ipaddr[2],
		  ipaddr[3]);
	destport = port;

	printd ("New Connection.\n");
	pcb = tcp_new ();
	if (pcb) {
		e = tcp_connect(pcb, &destip, destport,
				 tcp_client_connected);
		if (e == ERR_OK) {
			printf ("Connecting...\n");
			https_client_pcb = pcb;
		} else {
			printf ("Connect failed!\n");
		}
	} else {
		printf ("New context failed.\n");
	}

    free(a);
}

void tcp_client_close(void *arg)
{
    tcp_close(https_client_pcb);
}

void https_test_init(void *arg)
{
    int err;

    err = wolfSSL_Init();

    if (err != SSL_SUCCESS) {
        printf("failed to initialize wolfSSL library\n");
        return;
    }

    ctx = wolfSSL_CTX_new(wolfTLSv1_2_client_method());
    if (ctx == NULL) {
        printf("unable to get ctx\n");
        return;
    }

    printf("wolfSSL_CTX_load_verify_buffer: start\n");

    err = wolfSSL_CTX_load_verify_buffer(ctx, ca_cert_der_1024,
            sizeof_ca_cert_der_1024, SSL_FILETYPE_ASN1);
    if (err != SSL_SUCCESS) {
        printf("unable to load buffer\n");
        return;
    }

    wolfSSL_SetIORecv(ctx, wolfSSL_LwIP_Receive);
    wolfSSL_SetIOSend(ctx, wolfSSL_LwIP_Send);

    ssl = wolfSSL_new(ctx);
    if (ssl == NULL) {
        printf("unable to get SSL object\n");
        return;
    }

    wolfSSL_SetIO_LwIP(ssl, https_client_pcb, NULL, NULL, NULL);

    if (wolfSSL_connect(ssl) != SSL_SUCCESS) {
        err = wolfSSL_get_error(ssl, 0);
        if(err == SSL_ERROR_WANT_READ){
            return;
        }
        printf("SSL_connect failed err=%d\n", err);
    }

    printf("ssl connect done.\n");

    if (wolfSSL_write(ssl, msg, strlen(msg)) != strlen(msg))
        printf("SSL_write failed\n");

    printf("ssl write done.\n");

    int input ;
    char reply[1024] ;

    input = wolfSSL_read(ssl, reply, sizeof(reply)-1);
    if (input > 0) {
        reply[input] = 0;
        printf("Server response: %s\n", reply);
    } else if (input < 0) {
        int readErr = wolfSSL_get_error(ssl, 0);
        if (readErr != SSL_ERROR_WANT_READ)
            printf("wolfSSL_read failed\n");
        return;
    }

    printf("all is done.\n");

    wolfSSL_free(ssl);
    wolfSSL_CTX_free(ctx);
    wolfSSL_Cleanup();
}

int is_connect_done()
{
    return connected;
}
