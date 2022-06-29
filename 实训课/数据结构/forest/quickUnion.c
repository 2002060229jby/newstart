/*************************************************************************
	> File Name: quickUnion.c
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
	int *father;
	int size;
}UnionSet;

UnionSet *initSet(int n) {
	UnionSet *u=(UnionSet *)malloc(sizeof(UnionSet));
	u->father=(int *)malloc(sizeof(int)*(n+1));
	u->size=n+1;
	int i;
	for(i=0;i<u->size;i++){
		u->father[i]=i;
	}
	return u;
}

void freeSet(UnionSet *u){
	if(!u) {
		return ;
	}
	free(u->father);
	free(u);
	return ;
}

int find(UnionSet *u,int idx){
	return u->father[idx] = u->father[idx]==idx?idx:find(u,u->father[idx]);
}

int merge(UnionSet *u, int a,int b) {
	int fa=find(u,a),fb=find(u,b);
	if(fa==fb){
		return 0;
	}
	u->father[fa]=fb;
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