/*************************************************************************
	> File Name: 1.binary_search_tree.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define KEY(n) (n ? n->key : 0)
#define TEST(func) { \
    while (~scanf("%d", &key)) { \
        if (key == -1) break; \
        root = func(root, key); \
        printf("\n=== %s %d to BST ===\n", #func, key); \
        output(root); \
        inorder_ouput(root), printf("\n"); \
    } \
}

typedef struct Node {
    int key;
    Node *lchild, *rchild;
} Node;

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NULL) return root;
    if (root->key > key) root->lchild = erase(root->lchild, key);
    else if (root->key < key) root->rchild = erase(root->rchild, key);
    else {
        if (root->lchild == NULL && root->rchild == NULL) {
            free(root);
            return NULL;
        } else if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    return root;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void print_node(Node *root) {
    printf("( %3d | %3d, %3d )\n", 
        KEY(root), 
        KEY(root->lchild), KEY(root->rchild)
    );
    return ;
}

void output(Node *root) {
    if (root == NULL) return ;
    print_node(root);
    output(root->lchild);
    output(root->rchild);
    return ;
}

void inorder_ouput(Node *root) {
    if (root == NULL) return ;
    inorder_ouput(root->lchild);
    printf("%d ", root->key);
    inorder_ouput(root->rchild);
    return ;
}

int main() {
    Node *root = NULL;
    int key;
    // insert operator
    TEST(insert);

    //erase operator
    TEST(erase);

    clear(root);
    return 0;
}
