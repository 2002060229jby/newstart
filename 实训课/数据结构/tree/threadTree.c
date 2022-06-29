/*************************************************************************
	> File Name: threadTree.c
	> Author: Baiying
	> Mail: 
	> Created Time: Sat 25 Jun 2022 10:48:28 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define CHILD 0
#define THREAD 1
typedef struct Node {
    int val;
    struct Node *right;
    struct Node *left;
    int ltag,rtag;
}Node;
Node *initNode(int val){
    Node *n=(Node *)malloc(sizeof(Node));
    n->val=val;
    n->left=NULL;
    n->right=NULL;
    n->ltag=CHILD;
    n->rtag=CHILD;
    return n;
}
void freeNode(Node *p) {
    if(!p) {
        return ;
    }
    free(p);
    return ;
}
void insert(Node **raddr,int val) {
    if(!(*raddr)) {
        *raddr=initNode(val);
        return ;
    }
    if(val > (*raddr)->val) {
        insert(&((*raddr)->right),val);
    }else{
        insert(&((*raddr)->left),val);
    }
    return ;
}
void freeAll(Node *root) {
    if(!root) {
        return ;
    }
    if(root->ltag==CHILD){
        freeAll(root->left);
    }
    if(root->rtag==CHILD){
        freeAll(root->right);
    }
    freeNode(root);
    return ;
}
void inorderTrav(Node *root){
    if(!root) {
        return ;
    }
    inorderTrav(root->left);
    printf("%d ",root->val);
    inorderTrav(root->right);
    return ;
}
Node *pre=NULL;
void buildThread(Node *root) {
    if(!root) {
        return ;
    }
    //先去建立左子树的线索
    buildThread(root->left);
    //再构建根的线索
    //如果当前的左指针是空，让左指针指向前驱
    if(!root->left){
        root->left=pre;
        root->ltag=THREAD;
    }
    if(pre && !pre->right) {
        pre->right=root;
        pre->rtag=THREAD;
    }
    pre=root;
    //最后建立右子树的线索
    buildThread(root->right);
    return ;

}
Node *getLeftMost(Node *p){
    while(p && p->ltag==CHILD && p->left){
        p=p->left;
    }
    return p;
}
void output(Node *root) {
    if(!root) {
        return ;
    }
    Node *p=getLeftMost(root);
    while(p){
        printf("%d ",p->val);
        if(p->rtag==CHILD){
            p=getLeftMost(p->right);
        }else{
            p=p->right;
        }
    }
    putchar(10);
    return ;
}
int main(){
    srand(time(0));
    Node *root=NULL;
    int cnt=10;
    while(cnt--) {
        int val = rand()%100;
        insert(&root,val);
        printf("%d ", val);
    }
    putchar(10);//换行
    inorderTrav(root);
    putchar(10);//换行

    buildThread(root);
    output(root);

    freeAll(root);
    return 0;
}
