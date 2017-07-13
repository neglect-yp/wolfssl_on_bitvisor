LWIP_VERSION=1.4.1

CFLAGS += -I$(DIR)/include -I$(DIR)/include/arch -I$(DIR)/include/lwip \
	-I$(DIR)/lwip-$(LWIP_VERSION)/src/include \
	-I$(DIR)/lwip-$(LWIP_VERSION)/src/include/ipv4 \

objs-1 += lwip-$(LWIP_VERSION)/src/core/def.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/dhcp.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/dns.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/init.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/mem.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/memp.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/netif.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/pbuf.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/raw.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/stats.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/sys.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/tcp.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/tcp_in.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/tcp_out.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/udp.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/timers.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/ipv4/autoip.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/ipv4/igmp.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/ipv4/inet_chksum.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/ipv4/ip.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/ipv4/icmp.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/ipv4/inet.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/ipv4/ip_addr.o
objs-1 += lwip-$(LWIP_VERSION)/src/core/ipv4/ip_frag.o
objs-1 += lwip-$(LWIP_VERSION)/src/netif/etharp.o
objs-1 += lwip-$(LWIP_VERSION)/src/api/api_lib.o
objs-1 += lwip-$(LWIP_VERSION)/src/api/api_msg.o
objs-1 += lwip-$(LWIP_VERSION)/src/api/err.o
objs-1 += lwip-$(LWIP_VERSION)/src/api/netbuf.o
objs-1 += lwip-$(LWIP_VERSION)/src/api/netdb.o
objs-1 += lwip-$(LWIP_VERSION)/src/api/netifapi.o
objs-1 += lwip-$(LWIP_VERSION)/src/api/sockets.o
objs-1 += lwip-$(LWIP_VERSION)/src/api/tcpip.o

objs-1 += ip_sys.o arch/sys_arch.o
objs-1 += ip_main.o net_main.o
objs-1 += echo-server.o echo-client.o echoctl.o
objs-1 += bios_time.o
objs-1 += ctype.o
objs-1 += my_string.o
objs-1 += get_time.o
objs-1 += thermal.o

CFLAGS += -I$(DIR)/wolfssl -DBITVISOR -DBUILDING_WOLFSSL -DECC_SHAMIR -DECC_TIMING_RESISTANT -DHAVE_AESGCM -DHAVE_CHACHA -DHAVE_ECC -DHAVE_EXTENDED_MASTER -DHAVE_HASHDRBG -DHAVE_ONE_TIME_AUTH -DHAVE_POLY1305 -DHAVE_SUPPORTED_CURVES -DHAVE_THREAD_LS -DHAVE_TLS_EXTENSIONS -DNDEBUG -DNO_DES3 -DNO_DSA -DNO_HC128 -DNO_MD4 -DNO_PSK -DNO_PWDBASED -DNO_RABBIT -DNO_RC4 -DPIC -DTFM_ECC256 -DWC_NO_ASYNC_THREADING -DWC_RSA_BLINDING -DWOLFSSL_BASE64_ENCODE -DWOLFSSL_SHA224 -DWOLFSSL_SHA3 -DWOLFSSL_SHA384 -DWOLFSSL_SHA512 -DWOLFSSL_X86_64_BUILD -DNO_WOLFSSL_DIR -DUSE_FAST_MATH -DTFM_TIMING_RESISTANT -DWOLFSSL_NO_TRUSTED_CERTS_VERIFY

objs-1 += wolfssl/wolfcrypt/src/hmac.o
objs-1 += wolfssl/wolfcrypt/src/hash.o
objs-1 += wolfssl/wolfcrypt/src/random.o
objs-1 += wolfssl/wolfcrypt/src/sha256.o
objs-1 += wolfssl/wolfcrypt/src/rsa.o
objs-1 += wolfssl/wolfcrypt/src/aes.o
objs-1 += wolfssl/wolfcrypt/src/sha.o
objs-1 += wolfssl/wolfcrypt/src/sha512.o
objs-1 += wolfssl/wolfcrypt/src/sha3.o
objs-1 += wolfssl/wolfcrypt/src/logging.o
objs-1 += wolfssl/wolfcrypt/src/wc_encrypt.o
objs-1 += wolfssl/wolfcrypt/src/wc_port.o
objs-1 += wolfssl/wolfcrypt/src/error.o
objs-1 += wolfssl/wolfcrypt/src/signature.o
objs-1 += wolfssl/wolfcrypt/src/wolfmath.o
objs-1 += wolfssl/wolfcrypt/src/memory.o
# objs-1 += wolfssl/wolfcrypt/src/dh.o
objs-1 += wolfssl/wolfcrypt/src/asn.o
objs-1 += wolfssl/wolfcrypt/src/coding.o
objs-1 += wolfssl/wolfcrypt/src/poly1305.o
objs-1 += wolfssl/wolfcrypt/src/md5.o
objs-1 += wolfssl/wolfcrypt/src/chacha.o
objs-1 += wolfssl/wolfcrypt/src/chacha20_poly1305.o
objs-1 += wolfssl/wolfcrypt/src/tfm.o
objs-1 += wolfssl/wolfcrypt/src/ecc.o
objs-1 += wolfssl/src/internal.o
objs-1 += wolfssl/src/io.o
objs-1 += wolfssl/src/keys.o
objs-1 += wolfssl/src/ssl.o
objs-1 += wolfssl/src/tls.o
objs-1 += wolfssl/src/tls13.o

objs-1 += https_tcp.o https_test.o
