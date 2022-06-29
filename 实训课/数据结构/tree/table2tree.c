/*************************************************************************
	> File Name: tree.c
	> Author: Baiying
	> Mail: 
	> Created Time: Sat 25 Jun 2022 09:32:15 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
typedef struct Node {
	int val;
	struct Node *left;
	struct Node *right;
} Node;
typedef struct Tree{
	Node *root;
	int len;
}Tree;
Node *initNode(int val) {
	Node *n=(Node *)malloc(sizeof(Node));
	n->val=val;
	n->left=NULL;
	n->right=NULL;
	return n;
}
void freeNode(Node *p) {
	if(!p) {
		return ;
	}
	free(p);
	return ;
}
Tree *initTree(){
	Tree *t=(Tree *)malloc(sizeof(Tree));
	t->root=NULL;
	t->len=0;
	return t;
}

void insert(Node **raddr,int val) {
	if(!(*raddr)) {
		*raddr=initNode(val);
		return ;
	}
	if(val>(*raddr)->val) {//插入右子树
		insert(&((*raddr)->right),val);
	}else{
		insert(&((*raddr)->left),val);
	}
	return ;
}
void insertTree(Tree *t,int val) {
	if(!t){
		return ;
	}
	insert(&(t->root),val);
	t->len++;
	return ;
}

void preorderTrav(Node *root) {
	if(!root) {
		return ;
	}
	printf("%d,",root->val);
	preorderTrav(root->left);
	preorderTrav(root->right);
	return ;
}
void preorderTree(Tree *t){
	if(!t) {
		return ;
	}
	printf("Pre:[");
	preorderTrav(t->root);
	printf("]\n");
}
void outputTable(Node *root) {
	if(!root) {
		return ;
	}
	printf("%d",root->val);
	if(!root->left && !root->right)
		return ;
	printf("(");
	outputTable(root->left);
	printf(",");
	outputTable(root->right);
	printf(")");
	return ;
}
void outputTableTree(Tree *t){
	if(!t) {
		return ;
	}
	printf("Tabl:[");
	outputTable(t->root);
	printf("]\n");
}
void inorderTrav(Node *root) {
	if(!root) {
		return ;
	}
	inorderTrav(root->left);
	printf("%d,",root->val);
	inorderTrav(root->right);
	return ;
}
void inorderTree(Tree *t){
	if(!t) {
		return ;
	}
	printf("In:[");
	inorderTrav(t->root);
	printf("]\n");
}
void postorderTrav(Node *root) {
	if(!root) {
		return ;
	}
	postorderTrav(root->left);
	postorderTrav(root->right);
	printf("%d,",root->val);
	return ;
}
void postorderTree(Tree *t){
	if(!t) {
		return ;
	}
	printf("Post:[");
	postorderTrav(t->root);
	printf("]\n");
}

void freeAll(Node *root) {
	if(!root) {
		return ;
	}
	freeAll(root->left);
	freeAll(root->right);
	freeNode(root);//后序释放
	return ;
}
void freeTree(Tree *t) {
	if(!t) {
		return ;
	}
	freeAll(t->root);
	free(t);
	return ;
}
Node *findNode(Node *root, int val) {
	if(!root) {
		return NULL;
	}
	if(val == root->val) {
		return root;
	}
	if(val > root->val){
		return findNode(root->right,val);
	}else{
		return findNode(root->left,val);
	}
}

Node *findTree(Tree *t,int val) {
	if(!t) {
		return NULL;
	}
	return findNode(t->root,val);
}

//实现栈数据元素类型Node*
typedef struct Stack{
	Node **data;
	int size;
	int top;
}Stack;
Stack *initStack(int n){
	Stack *s=(Stack *)malloc(sizeof(Stack));
	s->data=(Node **)malloc(sizeof(Node *) * n);
	s->top=-1;
	s->size=n;
	return s;
}
void freeStack(Stack *s) {
	if(!s) {
		return ;
	}
	free(s->data);
	free(s);
	return ;
}
int push(Stack *s,Node *n) {
	if(!s || s->top == s->size-1) {
		return 0;
	}
	s->data[++s->top] = n;
	return 1;
}
int isEmpty(Stack *s) {
	return !(s && s->top!=-1) ;
}
Node *pop(Stack *s){
	return s->data[s->top--];
}
Node *buildTree(char *str){
	Stack *s=initStack(strlen(str)/2);
	Node *root,*n;
	int flag=0;
	int num=0;
	while(*str){
		switch(str[0]){
			case '(':
				push(s,n);
				flag=0;
				break;
			case ',':
				flag=1;
				break;
			case ')':
				root=pop(s);
				break;
			default:
				if(str[0]<'0' || str[0]>'9') {
					break;
				}
				// 计算数字是多少
				num=0;
				while(str[0]>='0' && str[0]<='9'){
					num=num*10+str[0]-'0';
					str++;
				}
				str--;
				n=initNode(num);
				//根据flag插入栈顶
				if(!isEmpty(s)){
					flag?(s->data[s->top]->right = n):(s->data[s->top]->left=n);
				}
		}
		str++;
	}
	freeStack(s);
	return root;
}
int main(){
	Tree *t=initTree();
	char str[100];
	scanf("%s", str);
	t->root=buildTree(str);
	preorderTree(t);
	outputTableTree(t);

	freeTree(t);
	return 0;
}
