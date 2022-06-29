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
int main(){
	srand(time(0));
	Tree *t=initTree();
	int cnt=10;
	int want=0;
	while(cnt--) {
		int val=rand()%100;
		insertTree(t,val);
		if(cnt==9){
			want=val;
		}
	}
	preorderTree(t);
	inorderTree(t);
	postorderTree(t);
	outputTableTree(t);

	Node *find = findTree(t,want);
	find?printf("find %d at %#x,val=%d\n",want,find,find->val):printf("%d not found~\n",want);

	freeTree(t);
	return 0;
}