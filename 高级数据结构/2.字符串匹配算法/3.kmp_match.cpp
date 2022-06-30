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

int brute_one_match(const char *s, const char *t) {
    printf("brute_one_match called\n");
    for (int j = 0; t[j]; j++) {
        if (s[j] == t[j]) continue;
        return 0;
    }
    return 1;
}

int brute_force(const char *s, const char *t) {
    for (int i = 0; s[i]; i++) {
        if (brute_one_match(s + i, t)) return i;
    }
    return -1;
}

int quick_mod(int a, int b, int c) {
    int ans = 1, temp = a;
    while (b) {
        if (b & 1) ans = ans * temp % c;
        temp = temp * temp % c;
        b >>= 1;
    }
    return ans;
}

int hash_match(const char *s, const char *t) {
    int len = strlen(t), base = 31, P = 9973, nbase = quick_mod(base, len, P);
    int h = 0, th = 0;
    for (int i = 0; t[i]; i++) th = (th * base + t[i]) % P;
    for (int i = 0; s[i]; i++) {
        h = (h * base + s[i]) % P;
        if (i >= len) h = (h - (s[i - len] * nbase % P) + P) % P;
        if (i + 1 < len) continue;
        if (h != th) continue;
        if (brute_one_match(s + i - len + 1, t)) return i - len + 1;
    }
    return -1;
}

int *getNext(const char *t, int *n) {
    *n = strlen(t);
    int *next = (int *)malloc(sizeof(int) * (*n));
    next[0] = -1;
    for (int i = 1, j = -1; t[i]; i++) {
        while (j != -1 && t[j + 1] != t[i]) j = next[j];
        if (t[j + 1] == t[i]) j += 1;
        next[i] = j;
    }
    return next;
}

int kmp(const char *s, const char *t) {
    int len;
    int *next = getNext(t, &len);
    for (int i = 0, j = -1; s[i]; i++) {
        while (j != -1 && t[j + 1] != s[i]) j = next[j];
        if (t[j + 1] == s[i]) j += 1;
        if (t[j + 1] == '\0') {
            free(next); 
            return i - len + 1;
        }
    }
    free(next);
    return -1;
}

int test_func(const char *s, const char *t) {
    return -1;
}

int main() {
    while (~scanf("%s%s", s, t)) {
        TEST(brute_force);
        TEST(hash_match);
        TEST(kmp);
    }
    return 0;
}
