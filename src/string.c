#include "string.h"

void memcpy(void* src, void* dest, uint32_t len)
{
    uint8_t* tmp1 = src;
    uint8_t* tmp2 = dest;
    for(uint32_t i = 0; i < len; i++)
    {
        tmp1[i] = tmp2[i];
    }
}

void memset(void* src, uint8_t data, uint32_t len)
{
    uint8_t* tmp = src;
    for(uint32_t i = 0; i < len; i++)
    {
        tmp[i] = data;
    }
}

void strcpy(char* src, char* dest, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        src[i] = dest[i];
    }
}

int strcmp(const char* s1, const char* s2)
{
    int i = 0;
    do {
        i++;
        if(s1[i] != s2[i])
            return 0;
    }  while(s1[i] == s2[i]);

    return 1;
}

int strlen(const char* s)
{
    int i = 0;
    while(s[i] != 0)
    {
        i++;
    }

    return i;
}

void itoa(char *buf, int base, int d) {
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    /* If %d is specified and D is minus, put ‘-’ in the head. */
    if (base == 'd' && d < 0) {
        *p++ = '-';
        buf++;
        ud = -d;
    } else if (base == 'x')
        divisor = 16;

    /* Divide UD by DIVISOR until UD == 0. */
    do {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    /* Terminate BUF. */
    *p = 0;

    /* Reverse BUF. */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}
