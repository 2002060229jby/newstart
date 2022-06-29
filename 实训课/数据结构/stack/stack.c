/*************************************************************************
	> File Name: stack.c
	> Author: Baiying
	> Mail: 
	> Created Time: Fri 24 Jun 2022 09:36:56 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
typedef struct Stack{
	int *data;
	int top;
	int size;
} Stack;
int expand(Stack *s);
Stack *initStack(int n) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->data=(int *)malloc(sizeof(int)*n);
	s->top=-1;
	s->size=n;
	return s;
}

void freeStack(Stack **saddr) { //值-结果参数返回法
	if(!(*saddr)) {
		return ;
	}
	free((*saddr)->data);
	free((*saddr));
	*saddr=NULL;
	return ;
}

int push(Stack *s,int val) {
	if(!s) {
		return 0;
	}
	if(s->top == s->size-1){
		if(!expand(s)){
			return 0;
		}
	}
	s->data[++s->top]=val;
	return 1;
}
int isEmpty(Stack *s){
	// return !s || s->top==-1;
	return !(s && s->top!=-1);
}
int pop(Stack *s) {
	return s->data[s->top--];
}
void showStack(Stack *s) {
	if(isEmpty(s)) {
		return ;
	}
	printf("Stack:[");
	int i;
	for(int i=0;i<=s->top;i++){
		i && printf(",");
		printf("%d", s->data[i]);
	}
	printf("]\n");
	return ;
}
int expand(Stack *s){
	if(!s) {
		return 0;
	}
	int expsize=s->size;
	int *tmp;
	while(expsize){
		tmp=(int *)realloc(s->data,sizeof(int)*(s->size+expsize));
		if(tmp){
			break;
		}
		expsize>>=1;
	}
	if(!tmp){
		return 0;
	}
	s->data=tmp;
	s->size+=expsize;

	printf("expand successfully~,new size is %d\n",s->size);
	return 1;
}

int main(){
	srand(time(0));

	Stack *s=initStack(1);
	int cnt=20;
	while(cnt--) {
		int val=rand()%100;
		int opt=rand()%4;
		switch(opt) {
			case 0:
			case 1:
			case 2:
				printf("push %d, res=%s\n",val,push(s,val)?"SUC":"ERR");
				break;
			case 3:
				isEmpty(s)?printf("pop nothing~\n"):printf("pop %d\n",pop(s));
				break;
		}
		showStack(s);
	}
	freeStack(&s);//子函数改变主函数中的变量，传入变量的地址
	// printf("%#x\n",s);

	return 0;
}
