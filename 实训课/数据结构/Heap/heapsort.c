/*************************************************************************
	> File Name: heapsort.c
	> Author: Baiying
	> Mail: 
	> Created Time: Sun 26 Jun 2022 11:44:54 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define swap(a,b) {\
	__typeof(a) __tmp=a;\
	a=b;b=__tmp;\
}
void downAdj(int *arr,int idx,int len){
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
		swap(arr[idx],arr[tmp]);
		idx=tmp;
	}
	return ;
}
void heap_sort(int *arr, int len) {
	int i;
	for(i=(len-2)/2;i>=0;i--){
		downAdj(arr,i,len);
	}
	for(i=len-1;i>0;i--){
		swap(arr[0],arr[i]);
		downAdj(arr,0,i);
	}
}
void showArr(int *arr, int len) {
	printf("arr:[");
	int i;
	for(i=0;i<len;i++){
		i && printf(",");
		printf("%d", arr[i]);
	}
	printf("]\n");
}
int main(){
	srand(time(0));
	#define ARRLEN 10
	int arr[ARRLEN];
	int i;
	for(i=0;i<ARRLEN;i++){
		arr[i]=rand()%100;
	}
	showArr(arr, ARRLEN);

	heap_sort(arr,ARRLEN);
	showArr(arr, ARRLEN);
	#undef ARRLEN
	return 0;
}