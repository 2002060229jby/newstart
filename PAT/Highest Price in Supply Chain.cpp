#include<cstdio>
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
#define NUM 100000
int N;
double P,r;
vector<int> v[NUM];
int root;
int depth[NUM];
int maxdepth,res;

void dfs(int cur){
    if(depth[cur]>maxdepth) {
        maxdepth=depth[cur];
        res=1;
    }
    else if(depth[cur]==maxdepth){
        res++;
    }
    for(int each:v[cur]){
        depth[each]=depth[cur]+1;
        dfs(each);
    }
}
int main(){
    int i,j,k;
    cin>>N>>P>>r;
    for(i=0;i<N;i++){
        cin>>j;
        if(j>=0)v[j].push_back(i);
        else root=i;
    }
    dfs(root);

    printf("%.2f %d\n", P*pow(1+r*0.01,maxdepth),res);

    return 0;
}
