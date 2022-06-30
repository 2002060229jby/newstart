char * longestPalindrome(char * s){
    long long h1[1005] = {0}, h2[1005] = {0}, base = 31, MOD = (1e9 + 7);
    long long mul[1005] = {0};
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        h1[i + 1] = (h1[i] * base + s[i]) % MOD;
    }
    for (int i = n - 1; i >= 0; i--) {
        h2[i + 1] = (h2[i + 2] * base + s[i]) % MOD;
    }
    mul[0] = 1;
    for (int i = 1; i <= n; i++) mul[i] = mul[i - 1] * base % MOD;
    char *ret;
    for (int l = n; l >= 1; l--) {
        for (int i = 1; i + l - 1 <= n; i++) {
            int j = i + l - 1;
            int code1 = (h1[j] - h1[i - 1] * mul[l] % MOD + MOD) % MOD;
            int code2 = (h2[i] - h2[j + 1] * mul[l] % MOD + MOD) % MOD;
            if (code1 - code2) continue;
            ret = (char *)malloc(sizeof(char) * (l + 1));
            ret[l] = 0;
            strncpy(ret, s + i - 1, l);
            return ret;
        }
    }
    return NULL;
}