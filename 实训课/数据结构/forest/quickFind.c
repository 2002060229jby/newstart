/*************************************************************************
	> File Name: quickFind.c
	> Author: Baiying
	> Mail: 
	> Created Time: Mon 27 Jun 2022 10:15:39 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
typedef struct UnionSet{
	int *color;
	int size;
}UnionSet;
UnionSet *initSet(int n) {
	UnionSet *u=(UnionSet *)malloc(sizeof(UnionSet));
	u->color=(int *)malloc(sizeof(int)*(n+1));
	u->size=n+1;
	int i;
	for(i=0;i<u->size;i++){
		u->color[i]=i;
	}
	return u;
}
void freeSet(UnionSet *u){
	if(!u) {
		return ;
	}
	free(u->color);
	free(u);
	return ;
}
int find(UnionSet *u,int idx){
	return u->color[idx];
}
int merge(UnionSet *u, int a,int b) {
	if(find(u,a)==find(u,b)){
		return 0;
	}
	int acolor=find(u,a);
	int i;
	for(i=0;i<u->size;i++){
		if(find(u,i)==acolor){
			u->color[i]=u->color[b];
		}
	}
	return 1;
}
int main(){
	int n,m,i;
	scanf("%d%d",&n,&m);
	UnionSet *u=initSet(n);
	for(i=0;i<m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		switch(a){
			case 1:
				merge(u,b,c);
				break;
			case 2:
				printf("%s\n",find(u,b)==find(u,c)?"Yes":"No");
				break;
		}
	}
	freeSet(u);
	return 0;
}