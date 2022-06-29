/*************************************************************************
	> File Name: hash.c
	> Author: Baiying
	> Mail: 
	> Created Time: Mon 27 Jun 2022 09:37:06 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
typedef struct Node {
	char *str;
	struct Node *next;
}Node;
typedef struct HashTable{
	Node **data;
	int size;
}HashTable;
Node *initNode(char *str){
	Node *n=(Node *)malloc(sizeof(Node));
	n->str=strdup(str);
	n->next=NULL;
	return n;
}
void freeNode(Node *p){
	if(!p) {
		return ;
	}
	free(p->str);
	free(p);
	return ;
}
void freeList(Node *head){
	if(!head){
		return ;
	}
	Node *k;
	while(head){
		k=head;
		head=head->next;
		freeNode(k);
	}
	return ;
}
HashTable *initHashTable(int n){
	HashTable *h=(HashTable *)malloc(sizeof(HashTable));
	h->size=2*n;
	h->data=(Node **)calloc(h->size,sizeof(Node *));
	return h;
}
void freeHashTable(HashTable *h){
	int i;
	for(i=0;i<h->size;i++){
		freeList(h->data[i]);
	}
	free(h->data);
	free(h);
	return ;
}
Node *insertNode(Node *head,Node *p){
	p->next=head;
	return p;
}
int BKDHash(char *str){
	int seed=31,hash=0;
	while(*str){
		hash=hash*seed+str[0];
		str++;
	}
	return hash & 0x7fffffff;
}
int insertHash(HashTable *h,char *str){
	if(!h) {
		return 0;
	}
	int hash=BKDHash(str);
	int idx=hash%h->size;
	h->data[idx]=insertNode(h->data[idx],initNode(str));
	return 1;
}
Node *searchList(Node *p,char *str){
	while(p && strcmp(p->str,str)){
		p=p->next;
	}
	return p;
}
Node *searchHash(HashTable *h, char *str){
	if(!h) {
		return NULL;
	}
	int hash=BKDHash(str);
	int idx=hash%h->size;
	return searchList(h->data[idx],str);
}
//生成随机长度字符串
char *makeStr(char *str,int n){
	int len=rand()%(n-1)+1;
	char tmp;
	int i;
	for(i=0;i<len;i++){
		switch(rand()%3){
			case 0:
				tmp='A'+rand()%26;
				break;
			case 1:
				tmp='a'+rand()%26;
				break;
			case 2:
				tmp='0'+rand()%10;
				break;
			default:
				tmp='x';
		}
		str[i]=tmp;
	}
	str[len]=0;
	return str;
}
int main(){
	srand(time(0));
	#define N 10
	char str[8];
	int cnt=N;
	HashTable *h = initHashTable(N);
	while(cnt--){
		makeStr(str,8);
		insertHash(h,str);
		printf("%s ",str);
	}
	putchar(10);
	while(~scanf("%s",str)){
		if(!strcmp(str,"q")){
			break;
		}
		Node *f=searchHash(h,str);
		if(f){
			printf("hash=%d addr=%p str=%s\n",BKDHash(str),f,f->str);
		}else{
			printf("%s not found~\n",str);
		}
	}
	freeHashTable(h);
	#undef N
	return 0;
}