/*************************************************************************
	> File Name: search.c
	> Author: Baiying
	> Mail: 
	> Created Time: Sun 26 Jun 2022 10:01:31 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

int binary_search(int *arr,int n,int x){
	int head=0,tail=n-1,mid;
	while(head<=tail){
		mid=(head+tail)>>1;
		if(arr[mid]==x){
			return mid;
		}
		arr[mid]>x?(tail=mid-1):(head=mid+1);
	}
	return -1;
}

// 00000000011111111111
int binary_search_first1(int *arr,int n){
	int head=0,tail=n-1,mid;
	while(head<tail){
		mid=(head+tail)>>1;
		if(arr[mid]==1){
			tail=mid;
		}else{
			head=mid+1;
		}
	}
	return head;
}
void insert_sort(int *arr,int n) {
	int i,j;
	for(i=1;i<n;i++){
		for(j=i;j>0 && arr[j]<arr[j-1];j--){
			arr[j]=arr[j]+arr[j-1];
			arr[j-1]=arr[j]-arr[j-1];
			arr[j]=arr[j]-arr[j-1];
		}
	}
	return ;
}
void showArr(int *arr,int n) {
	printf("arr:[");
	int i;
	for(i=0;i<n;i++){
		i && printf(",");
		printf("%d", arr[i]);
	}
	printf("]\n");
	return ;
}
int main(){
	srand(time(0));
	#define N 10
	int arr[N];
	int i;
	for(i=0;i<N;i++){
		arr[i]=rand()%2;
	}
	showArr(arr,N);
	insert_sort(arr,N);
	showArr(arr,N);

	printf("search first 1 at idx=%d\n",binary_search_first1(arr,N));


	#undef N
	return 0;
}