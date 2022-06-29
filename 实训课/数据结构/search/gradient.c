/*************************************************************************
	> File Name: gradient.c
	> Author: Baiying
	> Mail: 
	> Created Time: Mon 27 Jun 2022 09:22:27 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
// 计算f(x)=ax^2+bx+c的极值
double gradientDesc(double a,double b,double c,int cnt){
	double l=0.1;
	double x=rand()/(double)RAND_MAX*20-10;
	int i;
	for(i=0;i<cnt;i++){
		double gradient=2*a*x+b;
		if(a>0)
			x=x-gradient*l;
		else 
			x=x+gradient*l;
		double fx=a*x*x+b*x+c;
		printf("i=%d x=%lf fx=%lf gradient=%lf\n",i,x,fx,gradient);
	}
	return x;
}
int main(){
	srand(time(0));
	int a=rand()%20-10;
	int b=rand()%20-10;
	int c=rand()%20-10;
	a=a==0?1:a;
	printf("f(x)=%dx^2+%dx+%d\n",a,b,c);
	gradientDesc(a,b,c,100);
	return 0;
}