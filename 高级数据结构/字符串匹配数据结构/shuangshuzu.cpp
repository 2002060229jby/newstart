#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BASE 26
#define MAX_N 10000
char s[MAX_N + 5];

typedef struct Node {
    int flag; //记录是否独立成词;1表示到这里为止可以独立成词；0表示不能独立成词
    struct Node *next[BASE]; //记录边的信息
} Node;

typedef struct DANode {//结构体数组，开辟连续空间
    int base, check; //check值：记录父节点的位置。
} DANode;

DANode da_trie[MAX_N + 5];
int da_root; //记录根节点

__attribute__((constructor)) 
void init_da_trie() {
    memset(da_trie, 0, sizeof(da_trie));
    da_root = 1;
    da_trie[da_root].check = 1;// 根节点的父节点就是自己
    return ;
}

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    memset(p->next, 0, sizeof(Node *) * BASE);
    return p;
}

inline int code(char c) {
    return c - 'a';
}

void insert(Node *root, const char *s) {
    Node *p = root;
    for (int i = 0; s[i]; i++) {
        int ind = code(s[i]);
        if (p->next[ind] == NULL) p->next[ind] = getNewNode();
        p = p->next[ind];
    }
    p->flag = 1;
    return ;
}

int search(Node *root, const char *s) {
    Node *p = root;
    for (int i = 0; s[i]; i++) {
        int ind = code(s[i]);
        p = p->next[ind];
        if (p == NULL) return 0;
    }
    return p->flag;//返回是否独立成词
}

void clear(Node *root) {
    if (root == NULL) return ;
    for (int i = 0; i < BASE; i++) clear(root->next[i]);
    free(root);
    return ;
}

int getBase(Node *root, DANode *da_trie) {
    int base = 1;
    do {
        for (int i = 0; i < BASE; i++) {
            if (root->next[i] == NULL) continue;//没这条边就跳过
            if (da_trie[base + i].check == 0) continue;//能继续说明，到当前子节点base值还行得通。
            base = -base;
            break;
        }
        if (base > 0) return base;
        base = -base + 1;
    } while (1);
    return -1;
}

int transform_trie_to_double_array(Node *root, int ind, DANode *da_trie) {
    if (root == NULL) return ind;
    int max_ind = ind;
    int base = getBase(root, da_trie);
    da_trie[ind].base = base;
    //标记所有子节点的check值
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue; //没有这条边就跳过
        if (root->next[i]->flag) da_trie[base + i].check = -ind;
        else da_trie[base + i].check = ind;
    }
    //确定所有子节点的base值
    for (int i = 0; i < BASE; i++) {
        if (root->next[i] == NULL) continue;
        int temp_ind = transform_trie_to_double_array(root->next[i], base + i, da_trie);
        if (temp_ind > max_ind) max_ind = temp_ind;
    }
    return max_ind;
} 

void output_double_array_trie(DANode *da_trie, int max_ind) {
    for (int i = 1; i <= max_ind; i++) {
        printf("( %2d | %2d, %3d)\t", i, da_trie[i].base, da_trie[i].check);
        if (i % 5 == 0) printf("\n");
    }
    printf("\n");
    return ;
}

int da_search(DANode *da_trie, const char *s) {
    int p = da_root;
    for (int i = 0; s[i]; i++) {
        int ind = code(s[i]);
        if (abs(da_trie[da_trie[p].base + ind].check) != p) return 0;//子节点编号的check值记录着父节点编号，核对一下绝对值是否相等。
        p = da_trie[p].base + ind;
    }
    return da_trie[p].check < 0;
}

int main(){
    Node *root = getNewNode();
    while (~scanf("%s", s)) {
        if (strcmp(s, "__end__") == 0) break;
        insert(root, s);
    }
    int max_ind = transform_trie_to_double_array(root, da_root, da_trie);
    output_double_array_trie(da_trie, max_ind);

    while (~scanf("%s", s)) {
        if (strcmp(s, "__end__") == 0) break;
        printf("search %s from double array trie = %d\n", s, da_search(da_trie, s));
    }
    return 0;
}