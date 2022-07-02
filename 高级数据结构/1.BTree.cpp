/*************************************************************************
	> File Name: 1.BTree.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 3
typedef struct Node {
    int n;
    int key[MAX_M];
    struct Node *next[MAX_M + 1];
} Node;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->n = 0;
    memset(p->next, 0, sizeof(Node *) * (MAX_M + 1));
    return p;
}

Node *insert_key(Node *root, int key) {
    if (root == NULL) {
        root = getNewNode();
        root->key[(root->n)++] = key;
        return root;
    }
    int pos = 0;
    while (pos < root->n && root->key[pos] < key) pos += 1;
    if (pos < root->n && root->key[pos] == key) return root;
    for (int i = root->n - 1; i >= pos; i--) {
        root->key[i + 1] = root->key[i];
    }
    root->key[pos] = key;
    return root;
}

Node *insert_maintain(Node *root, Node *child, int pos) {



}

Node *insert(Node *root, int key) {
    if (root == NULL || root->next[0] == NULL) {
        return insert_key(root, key);
    }
    int pos = 0;
    while (pos < root->n && root->key[pos] < key) pos += 1;
    if (pos < root->n && root->key[pos] == key) return root;
    insert(root->next[pos], key);
    return insert_maintain(root, root->next[pos], pos);
}

void clear(Node *root) {
    if (root == NULL) return ;
    if (root->next[0] != NULL) {
        for (int i = 0; i <= root->n; i++) {
            clear(root->next[i]);
        }
    }
    free(root);
    return ;
}

int main() {


    return 0;
}
