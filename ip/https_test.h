#ifndef HTTPS_TEST_H
#define HTTPS_TEST_H

#if 1
#define printd(X...) do { printf (X); } while (0)
#else
#define printd(X...)
#endif

struct arg {
	int ipaddr_a[4];
	int port;
};

void tcp_client_init (void *arg);
void tcp_client_close(void *arg);
void https_test_init (void *arg);

#endif
