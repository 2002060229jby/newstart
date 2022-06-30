#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

int main(){
    unordered_map<string, int> m;
    m["123456"]=-999;
    m["123"]=99;
    m["asdasdasd"]=123456;
    m["ABCDE"]=999;
    for(auto it=m.begin();it!=m.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }

    
    return 0;
}