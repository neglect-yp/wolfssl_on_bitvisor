#ifndef MY_STRING_H
#define MY_STRING_H

/* 
 * wrapper functions to hide warnings about 'const'
 * changing args of functions in core/string.h is the best
 * but the change can have a big impact
 */
void *my_memcpy(void *dest, const void *src, size_t n);
int my_memcmp(const void *s1, const void *s2, size_t n);
int my_strlen(const char *s);

// functions not defined in core/string.h 
void *memmove(void *dest, const void *src, size_t n);
char *strncpy(char *dest, const char *src, size_t n);
int strncmp(const char *s1, const char *s2, size_t n);
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
char *strnstr(const char *s1, const char *s2, size_t n);

#endif
