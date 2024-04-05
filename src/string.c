#include "string.h"

void memcpy(uint8_t* src, uint8_t* dest, int len)
{
    for(int i = 0; i < len; i++)
    {
        src[i] = dest[i];
    }
}

void memset(uint8_t* src, uint8_t data, int len)
{
    for(int i = 0; i < len; i++)
    {
        src[i] = data;
    }
}

void strcpy(char* src, char* dest, int len)
{
    for(int i = 0; i < len; i++)
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
