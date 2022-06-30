/*************************************************************************
	> File Name: 1.string_match.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000
#define DEFAULT_LEN 40
char s[MAX_N + 5], t[MAX_N + 5];

#define TEST(func) { \
    char temp_s[MAX_N + 5]; \
    sprintf(temp_s, "%s(\"%s\", \"%s\") = %3d\n", #func, s, t, func(s, t)); \
    int n = DEFAULT_LEN - strlen(temp_s); \
    while (n--) printf(" "); \
    printf("%s", temp_s); \
}

int brute_force(const char *s, const char *t) {
    for (int i = 0; s[i]; i++) {
        bool flag = true;
        for (int j = 0; t[j]; j++) {
            if (s[i + j] == t[j]) continue;
            flag = false;
            break;
        }
        if (flag) return i;
    }
    return -1;
}

int test_func(const char *s, const char *t) {
    return -1;
}

int main() {
    while (~scanf("%s%s", s, t)) {
        TEST(brute_force);
        TEST(test_func);
    }
    return 0;
}
