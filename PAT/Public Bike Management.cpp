#include<vector>
#include<iostream>
using namespace std;
int Cmax,N,Sp,M;
int bike[501];
int dis[501][501];
vector<int>v[501];
int mindis[501];

vector<int> path;
vector<int> final_ans;
int final_dis=9999999,final_send,final_take;

void dfs(int curstation,int curdis,int cursend,int curtake){
    if(curdis>mindis[curstation]) return ;
    if(curstation==Sp){//if to,then compare
        if(curdis<final_dis || curdis==final_dis && cursend<final_send || \
           curdis==final_dis && cursend==final_send && curtake<final_take){

            final_ans=path;
            final_dis=curdis;
            final_send=cursend;
            final_take=curtake;   
        }
    }else{
        if(curdis<mindis[curstation]) mindis[curstation]=curdis;
        for(int i:v[curstation]){
            path.emplace_back(i);
            if(curtake+bike[i]<Cmax/2){
                dfs(i,curdis+dis[curstation][i],cursend+Cmax/2-curtake-bike[i],0);
            }else{
                dfs(i,curdis+dis[curstation][i],cursend,curtake+bike[i]-Cmax/2);
            }
            path.pop_back();
        }
    }
    

}
int main(){
    int i,j;
    cin>>Cmax>>N>>Sp>>M;
    for(i=1;i<=N;i++){
        cin>>bike[i];
    }
    for(i=1;i<=M;i++){
        int a,b,c;
        cin>>a>>b>>c;
        dis[a][b]=dis[b][a]=c;
        v[a].emplace_back(b);
        v[b].emplace_back(a);
    }
    for(i=1;i<=N;i++) mindis[i]=9999999;
    path.emplace_back(0);
    dfs(0,0,0,0);
    cout<<final_send<<" "<<final_ans[0];
    for(i=1;i<final_ans.size();++i){
        cout<<"->"<<final_ans[i];
    }
    cout<<" "<<final_take<<endl;
    return 0;
}
