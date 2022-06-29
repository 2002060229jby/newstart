/*************************************************************************
	> File Name: listStack.c
	> Author: Baiying
	> Mail: 
	> Created Time: Fri 24 Jun 2022 10:09:53 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
typedef struct Node{
	int val;
	struct Node *next;
}Node;

typedef struct Stack{
	Node *head;
}Stack;

Node *initNode(int val){
	Node *n=(Node *)malloc(sizeof(Node));
	if(!n){
		return NULL;
	}
	n->val=val;
	n->next=NULL;
	return n;
}
void freeNode(Node *p){
	if(p){
		free(p);
	}
	return ;
}
Stack *initStack(){
	Stack *s=(Stack *)malloc(sizeof(Stack));
	s->head=NULL;
	return s;
}
void freeStack(Stack *s){
	if(!s) {
		return ;
	}
	Node *p=s->head, *k;
	while(p){
		k=p;
		p=p->next;
		freeNode(k);
	}
	free(s);
	return ;
}
int push(Stack *s, int val) {
	if(!s) {
		return 0;
	}
	Node *n=initNode(val);
	if(!n) {
		return 0;
	}
	n->next=s->head;
	s->head=n;
	return 1;
}
int isEmpty(Stack *s){
	return !(s && s->head);
}
int pop(Stack *s){
	Node *k=s->head;
	int tmp=k->val;
	s->head=k->next;
	freeNode(k);
	return tmp;
}
void showStack(Stack *s){
	if(!s) {
		return ;
	}
	printf("Stack:[");
	Node *p=s->head;
	while(p){
		printf("%d->",p->val);
		p=p->next;
	}
	printf("NULL]\n");
}
int main(){
	srand(time(0));
	Stack *s=initStack(5);
	
	int cnt=20;
	while(cnt--){
		int val=rand()%100;
		int opt=rand()%4;
		switch(opt) {
			case 0:
			case 1:
			case 2:
				printf("push %d,res=%s\n",val,push(s,val)?"SUC":"ERR");
				break;
			case 3:
				isEmpty(s)?printf("pop nothing~\n"):printf("pop %d\n",pop(s));
				break;
		}
		showStack(s);
	}
	freeStack(s);
	return 0;
}
