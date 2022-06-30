#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int N,K,start=0,destination;
unordered_map<string, int> M;
string namelist[201];
int happy_of_city[200],cost[200][200];
int mincost[200];
vector<int> path;
vector<int> final_path;
int final_cost, final_happy, final_step;
int num_routes;
vector<int> v[200];

void dfs(int curcity, int curcost,int curhappy,int curstep){
    if(curcost>mincost[curcity]) return ;
    path.emplace_back(curcity);
    if(curcity==destination){
        if(curcost<mincost[curcity]){
            mincost[destination]=curcost;
            final_path = path;
            final_cost=curcost;
            final_happy = curhappy;
            final_step=curstep;
            num_routes=1;
        }else{
            num_routes++;
            if(curhappy > final_happy || curhappy==final_happy && curstep<final_step){
                final_path = path;
                final_happy = curhappy;
                final_step=curstep;
            } 
        }
    }else{
        mincost[curcity]=curcost;
        for(int each:v[curcity]){
            dfs(each,curcost+cost[curcity][each],curhappy+happy_of_city[each],curstep+1);
        }
    }
    path.pop_back();
}
int main(){
    int i,j,k,l;
    cin>>N>>K;
    string startCity;
    cin>>startCity;
    M[startCity]=0;
    namelist[start]=startCity;
    happy_of_city[0]=0;
    for(int i=1;i<N;i++){
        cin>>namelist[i];
        M[namelist[i]]=i;
        cin>>happy_of_city[i];
    } 
    destination=M["ROM"];
    while(K--){
        string city1, city2;
        cin>>city1>>city2>>l;
        i=M[city1];
        j=M[city2];
        v[i].emplace_back(j);
        v[j].emplace_back(i);
        cost[i][j]=cost[j][i]=l;
    }
    for(int i=0;i<N;i++) mincost[i]=100000000;
    dfs(start,0,0,0);
    cout<<num_routes<<" "<<final_cost<<" "<<final_happy<<" "<<final_happy/final_step<<endl;
    cout<<startCity;
    for(int i=1;i<final_path.size();i++){
        cout<<"->"<<namelist[final_path[i]];
    }
    cout<<endl;
    return 0;
}
