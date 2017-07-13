#include <core/string.h>
#include <core/mm.h>
#include "my_string.h"
#include "ctype.h"

void *my_memcpy(void *dest, const void *src, size_t n)
{
    return memcpy(dest, (void *)src, n);
}

int my_memcmp(const void *s1, const void *s2, size_t n)
{
    return memcmp((void *)s1, (void *)s2, n);
}

int my_strlen(const char *s)
{
    return strlen((char *)s);
}

void *memmove(void *dest, const void *src, size_t n)
{
    if (n == 0 || src == dest)
        return dest;

    char *d = (char *)d;
    const char *s = (const char *)src;

    // if these arrays don't overlap, use memcpy()
    if (s + n - 1 < d || d + n - 1 < s)
        memcpy(dest, (void *)src, n);

    if (d + n - 1 >= s) {
        for (int i = 0; i < n; i++)
            d[i] = s[i];
    }

    if (s + n - 1 >= d) {
        for (int i = n-1; i >= 0; i--)
            d[i] = s[i];
    }

    return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
        dest[i] = '\0';

    return dest;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    for (i = 0; i < n; i++) {
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
            break;
    }

    if (i == n)
        return 0;
    else
        return s1[i] - s2[i];
}

int strncasecmp(const char *s1, const char *s2, size_t n)
{
    size_t i;
    char c1, c2;

    for (i = 0; i < n; i++) {
        c1 = (char)toupper(s1[i]);
        c2 = (char)toupper(s2[i]);
        if (c1 != c2 || c1 == '\0' || c2 == '\0')
            break;
    }

    if (i == n)
        return 0;
    else
        return c1 - c2;
}

char *strchr(const char *s, int c)
{
    for (char *p = (char *)s;; p++) {
        if (*p == (char)c)
            return p;
        if (*p == '\0')
            break;
    }

    return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
    while (*haystack != '\0') {
        for (int i = 0;; i++) {
            if (needle[i] == '\0')
                return (char *)haystack;
            if (haystack[i] == '\0')
                return NULL;
            if (haystack[i] != needle[i])
                break;
        }
        haystack++;
    }
    return NULL;
}

// mystrnstr in wolfssl/src/ssl.c
char* strnstr(const char* s1, const char* s2, size_t n)
{
    unsigned int s2_len = (unsigned int)my_strlen(s2);

    if (s2_len == 0)
        return (char*)s1;

    while (n >= s2_len && s1[0]) {
        if (s1[0] == s2[0])
            if (my_memcmp(s1, s2, s2_len) == 0)
                return (char*)s1;
        s1++;
        n--;
    }

    return NULL;
}
