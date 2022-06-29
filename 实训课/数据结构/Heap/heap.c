/*************************************************************************
	> File Name: heap.c
	> Author: Baiying
	> Mail: 
	> Created Time: Sun 26 Jun 2022 11:24:06 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

typedef struct Heap{
	int *data;
	int size;
	int len;
}Heap;

Heap *initHeap(int n){
	Heap *h=(Heap *)malloc(sizeof(Heap));
	h->data=(int *)malloc(sizeof(int)*n);
	h->size = n;
	h->len=0;
	return h;
}
void freeHeap(Heap *h) {
	if(!h){
		return ;
	}
	free(h->data);
	free(h);
	return ;
}
#define swap(a,b) {\
	__typeof(a) __tmp=a;\
	a=b;b=__tmp;\
}
int push(Heap *h, int val) {
	if(!h) {
		return 0;
	}
	if(h->size == h->len){
		return 0;
	}
	h->data[h->len] = val;

	int idx=h->len;
	while(idx>0 && h->data[idx]>h->data[(idx-1)/2]){
		swap(h->data[idx],h->data[(idx-1)/2]);
	}
	h->len++;
	return 1;
}
void downAdj(int *arr,int idx,int len) {
	while(idx*2+1<len){
		int tmp=idx,l=idx*2+1,r=idx*2+2;
		if(arr[l]>arr[tmp]){
			tmp=l;
		}
		if(r<len && arr[r]>arr[tmp]){
			tmp=r;
		}
		if(tmp==idx){
			break;
		}
		swap(arr[tmp],arr[idx]);
		idx=tmp;
	}
	return ;
}
int isEmpty(Heap *h) {
	return !h || !h->len;
}
int pop(Heap *h) {
	int ret=h->data[0];
	h->data[0]=h->data[h->len-1];
	h->len--;
	downAdj(h->data,0,h->len);
	return ret;
}
void showHeap(Heap *h) {
	printf("Heap:[");
	int i;
	for(i=0;i<h->len;i++){
		i && printf(",");
		printf("%d",h->data[i]);
	}
	printf("]\n");
	return ;
}
int main(){
	srand(time(0));
	#define HEAPLEN 10
	Heap *h=initHeap(HEAPLEN);
	int cnt=HEAPLEN;
	while(cnt--) {
		int val=rand()%100;
		push(h,val);
	}
	showHeap(h);

	printf("pop: [");
	while(!isEmpty(h)){
		printf("%d ", pop(h));
	}
	printf("]\n");

	freeHeap(h);
	#undef HEAPLEN
	return 0;
}