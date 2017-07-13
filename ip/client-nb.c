/* client-nb.c
 *
 * Copyright (C) 2006-2016 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <wolfssl/wolfcrypt/settings.h>

#include <wolfssl/ssl.h>
#include <wolfssl/internal.h>
#include "tcp-conn-nb.h"
#include "client-nb.h"

#include <core/process.h>
#include <core/initfunc.h>

#define USE_CERT_BUFFERS_2048
#include <wolfssl/certs_test.h>

static int stat = CLIENT_BEGIN ;
static WOLFSSL_CTX* ctx     = 0 ;
static WOLFSSL*     ssl     = 0 ;
static SOCKET_T    sockfd  = 0 ;

// static const char msg[] = /* "hello wolfsssl!";  */
//                    "GET / HTTP/1.0\r\n\r\n" ;
static const char msg[] = "GET / HTTP/1.0\r\n\r\n" ;
static const int   port = 4443 ;
static const char* host = "10.6.18.156" ;

int client_nb(int m, int i)
{
    int err ;

    switch(stat) {
        case CLIENT_BEGIN:
            tcp_connect_init() ;
            stat = CLIENT_TCP_CONN ;

        case CLIENT_TCP_CONN:
            do { 
                err = tcp_connect(&sockfd, host, port, 0);
            } while(err == TCP_CONNECTING);
            if (err != TCP_CONNECTED)
                return -err;//break ;

            ctx = wolfSSL_CTX_new(wolfTLSv1_2_client_method());
            if (ctx == NULL) {
                err_sys("unable to get ctx");
                return -1;
            }

            // wolfSSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, 0);
            err =  wolfSSL_CTX_load_verify_buffer(ctx, ca_cert_der_2048,
                    sizeof_ca_cert_der_2048, SSL_FILETYPE_ASN1);
            
            if (err != SSL_SUCCESS) {
                err_sys("unable to load buffer");
                return -1;
            }

            tcp_close_nb() ;
            return -114514;

            ssl = wolfSSL_new(ctx);
            if (ssl == NULL) {
                err_sys("unable to get SSL object");
                return -1;
            }

            wolfSSL_SetIO_LwIP(ssl, sockfd, NULL, NULL, NULL);
            stat = CLIENT_SSL_CONN ;

        case CLIENT_SSL_CONN:           
            if (wolfSSL_connect(ssl) != SSL_SUCCESS) {
                err = wolfSSL_get_error(ssl, 0);
                if(err == SSL_ERROR_WANT_READ)
                    break ;
                err_sys("SSL_connect failed");
            }
            if (wolfSSL_write(ssl, msg, strlen(msg)) != strlen(msg))
                err_sys("SSL_write failed");
            stat = CLIENT_SSL_READ ;

        case CLIENT_SSL_READ: 
            {
                int input ;
                char reply[1024] ;

                input = wolfSSL_read(ssl, reply, sizeof(reply)-1);
                if (input > 0) {
                    reply[input] = 0;
                    printf("Server response: %s\n", reply);
                } else if (input < 0) {
                    int readErr = wolfSSL_get_error(ssl, 0);
                    if (readErr != SSL_ERROR_WANT_READ)
                        err_sys("wolfSSL_read failed");
                    break ;
                }

                wolfSSL_shutdown(ssl);
                wolfSSL_free(ssl);
                wolfSSL_CTX_free(ctx);
                tcp_close_nb() ;
                stat = CLIENT_BEGIN ;
                return 114514;
            }
    } /* end of switch */
    return -1;
}


static void wc_test_init_msg (void)
{
    msgregister("wc_test", client_nb);
}

INITFUNC("msg0", wc_test_init_msg);
