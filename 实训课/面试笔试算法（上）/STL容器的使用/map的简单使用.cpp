#include<iostream>
#include<map>
#include<utility>
#include<string>
// multimap
// multiset
using namespace std;

int main(){
    map<string,int> m;
    m["123"]=123;
    m["rty"]=9898989;
    m["qwerty"]=123456;
    m["qwe"]=99999999;
    for(auto it=m.begin();it!=m.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }
    /*
    map<char, int> m;
    m.insert(make_pair('B',12));
    m['Z']=9;
    m['x']=22;
    m['.']=1;
    m['>']=99;
    if(m.count('.')==1){
        cout<<m['.']<<endl;
    }
    m.erase('.');
    if(m.count('.')==0){
        cout<<"no"<<endl;
    }
    if(m['.']==0){ //如果没有元素就会插入这个元素。默认值为0
        cout<<"no"<<endl; 
    }// 不建议使用
    for(auto it=m.begin();it!=m.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }
    */
    return 0;
}