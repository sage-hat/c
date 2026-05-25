#include <stdio.h>
#include "my_string.h"

int my_strlen(const char *str)
{
    int i = 0;
    char c;

    while((c = str[i])) {
        i++;
    }
    return i;
}

int my_strcmp(const char *s1, const char *s2)
{
    int s1_len, s2_len;
    
    s1_len = my_strlen(s1);
    s2_len = my_strlen(s2);

    if(s1_len == s2_len) {
        int i;

        for(i = 0; i < s1_len; i++) {
            if(s1[i] != s2[i]) {
                return -1;
                break;
            }
        }
        return 0;
    }
    return -1;
}

void my_strcpy(char *dest, char *source)
{
    int i;
    for(i = 0; source[i] != '\0'; i++) {
        dest[i] = source[i];
    }
    dest[i+1] = '\0';
}
