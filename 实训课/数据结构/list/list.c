#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node{
    int val;
    struct Node *next;
    struct Node *prev;
}Node;
typedef struct List {
    Node head;
    int len;
}List;
Node *initNode(int val) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->val=val;
    n->next=NULL;
    n->prev=NULL;
    return n;
}
void freeNode(Node *n) {
    if(n) {
        free(n);
    }
    return ;
}
List *initList(){
    List *l=(List *)malloc(sizeof(List));
    l->head.next=NULL;
    l->head.prev=NULL;
    l->len=0;
    return l;
}
void freeList(List *l) {
    if(!l) {
        return ;
    }
    Node *p=l->head.next;
    Node *k;
    while(p) {
        k=p;
        p=p->next;
        freeNode(k);
    }
    free(l);
    return ;
}

int insertNode(List *l,int idx, Node *n){
    if(!l)
        return 0;
    if(idx<0 | idx>l->len) {
        return 0;
    }
    Node *p=&(l->head);
    while(idx--){
        p=p->next;
    }
    //插入节点
    n->next=p->next;
    p->next=n;

    //双向链表
    n->prev=p;
    if(n->next){//最后一个节点
        n->next->prev=n;
    }
    //管理节点节点个数++
    l->len++;
    return 1;
}
int insertVal(List *l,int idx, int val){
    Node *n=initNode(val);
    if(!insertNode(l,idx,n)){
        freeNode(n);
        return 0;
    }
    return 1;
}
int erase(List *l,int idx){
    if(!l){
        return 0;
    }
    if(idx<0 | idx>=l->len){
        return 0;
    }
    Node *p=&(l->head);
    while(idx--){
        p=p->next;
    }
    Node *k=p->next;
    p->next=k->next;

    if(k->next){
        k->next->prev=p;
    }
    freeNode(k);
    l->len--;
    return 1;
}
void showList(List *l) {
    if(!l) {
        return ;
    }
    Node *p=l->head.next;
    Node *k=&(l->head);
    printf("List+:[");
    while(p){
        k=p;
        printf("%d->",p->val);
        p=p->next;
    }
    printf("NULL]\n");

    printf("List-:[");
    while(k!=&(l->head)){
        printf("%d->",k->val);
        k=k->prev;
    }
    printf("HEAD]\n");
    return ;
}
int reverse(List *l) {
    if(!l) {
        return 0;
    }
    Node *p=l->head.next;
    Node *k;
    l->head.next=NULL;
    l->len=0;
    while(p){
        k=p;
        p=p->next;

        insertNode(l,0,k);
    }
    return 1;
}
int main(){
    srand(time(0));
    int cnt=20;
    List *l=initList();

    while(cnt--){
        int val=rand()%100;
        int opt=rand()%4;
        int idx=rand()%(l->len+3)-1;
        switch(opt) {
            case 0:
            case 1:
            case 2:
                printf("insert %d at %d,res=%s\n",val,idx,insertVal(l,idx,val)?"SUC":"ERR");
                break;
            case 3:
                printf("erase at %d,res=%s\n",idx,erase(l,idx)?"SUC":"ERR");
                break;
            case 4:
                printf("reverse, res=%s\n",reverse(l)?"SUC":"ERR");
        }
        showList(l);
    }
    freeList(l);
    return 0;
}
