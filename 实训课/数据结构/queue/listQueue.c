/*************************************************************************
	> File Name: listQueue.c
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

typedef struct Queue{
	Node *head;
	Node *tail;
}Queue;

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
Queue *initQueue(){
	Queue *q=(Queue *)malloc(sizeof(Queue));
	q->head=NULL;
	q->tail=NULL;
	return q;
}
void freeQueue(Queue *q){
	if(!q) {
		return ;
	}
	Node *p=q->head, *k;
	while(p){
		k=p;
		p=p->next;
		freeNode(k);
	}
	free(q);
	return ;
}
int push(Queue *q, int val) {
	if(!q) {
		return 0;
	}
	Node *n=initNode(val);
	if(!n) {
		return 0;
	}
	if(q->tail){
		q->tail->next=n;
		q->tail=n;
	}else{
		q->head=n;
		q->tail=n;
	}
	
	return 1;
}
int isEmpty(Queue *q){
	return !(q && q->head);
}
int pop(Queue *q){
	Node *k=q->head;
	int tmp=k->val;
	q->head=k->next;
	freeNode(k);
	if(!q->head){
		q->tail=NULL;
	}
	return tmp;
}
void showQueue(Queue *q){
	if(!q) {
		return ;
	}
	printf("Queue:[");
	Node *p=q->head;
	while(p){
		printf("%d->",p->val);
		p=p->next;
	}
	printf("NULL]\n");
	return ;
}
int main(){
	srand(time(0));
	Queue *q=initQueue(5);
	
	int cnt=20;
	while(cnt--){
		int val=rand()%100;
		int opt=rand()%4;
		switch(opt) {
			case 0:
			case 1:
			case 2:
				printf("push %d,res=%s\n",val,push(q,val)?"SUC":"ERR");
				break;
			case 3:
				isEmpty(q)?printf("pop nothing~\n"):printf("pop %d\n",pop(q));
				break;
		}
		showQueue(q);
	}
	freeQueue(q);
	return 0;
}
