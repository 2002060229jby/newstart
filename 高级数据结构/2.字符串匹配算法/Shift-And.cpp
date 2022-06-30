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
#define DEFAULT_LEN 50
char s[MAX_N + 5], t[MAX_N + 5];

#define TEST(func) { \
    char temp_s[MAX_N + 5] = {0}; \
    sprintf(temp_s, "%s(\"%s\", \"%s\") = %3d\n", #func, s, t, func(s, t)); \
    int n = DEFAULT_LEN - strlen(temp_s); \
    while (n >= 0) n -= printf(" "); \
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

void free_next(int *next) {
    free(next);
    return ;
}

void free_jump(int **jump, int n) {
    for (int i = 0; i < n; i++) free(jump[i - 1]);
    free(jump - 1);
    return ;
}

int **getJump(int *next,  const char *t, int n) {
    int **jump = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) jump[i] = (int *)malloc(sizeof(int) * 26);
    jump += 1;
    for (int i = 0; i < 26; i++) jump[-1][i] = -1; 
    jump[-1][t[0] - 'a'] = 0;
    for (int i = 0, I = n - 1; i < I; i++) {
        for (int j = 0; j < 26; j++) jump[i][j] = jump[next[i]][j];
        jump[i][t[i + 1] - 'a'] = i + 1;
    }
    return jump;
}

int kmp(const char *s, const char *t) {
    int len;
    int *next = getNext(t, &len);
    for (int i = 0, j = -1; s[i]; i++) {
        while (j != -1 && t[j + 1] != s[i]) j = next[j];
        if (t[j + 1] == s[i]) j += 1;
        if (t[j + 1] == '\0') {
            free_next(next);
            return i - len + 1;
        }
    }
    free_next(next);
    return -1;
}


int kmp_opt(const char *s, const char *t) {
    int len;
    int *next = getNext(t, &len);
    int **jump = getJump(next, t, len);
    for (int i = 0, j = -1; s[i]; i++) {
        j = jump[j][s[i] - 'a'];
        if (j == len - 1) {
            free_next(next);
            free_jump(jump, len);
            return i - len + 1;
        }
    }
    free_next(next);
    free_jump(jump, len);
    return -1;
}
int sunday(const char *s, const char *t) {
    int tlen=strlen(t),slen=strlen(s);
    int jump[128]={0};//每一种字符出现在第几位。
    for(int i=0;i<128;i++) jump[i]=tlen+1;//默认是tlen+1;
    for(int i=0;t[i];i++) jump[t[i]]=tlen-i;//维护每个字符最后出现的位置。
    for(int i=0;i+tlen<=slen;){
        if(brute_one_match(s+i,t)) return i;
        i+=jump[s[i+tlen]];
    }
    return -1;
}

int shift_and(const char *s, const char *t) {
    int code[128] = {0}, n = 0;
    for (;t[n];n++) code[t[n]] |= (1<<n);
    int p = 0;
    for (int i=0;s[i];i++) {
        p=(p<<1 | 1) & code[s[i]];
        if (p & (1 << (n-1))) return i-n+1;
    }
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
        TEST(kmp_opt);
        TEST(sunday);
        TEST(shift_and);
    }
    return 0;
}

