#include<iostream>
#include<set>
using namespace std;
struct node{
    int x,y;
    bool operator< (const node &b) const {
        return this->x<b.x;
    } 
};

int main(){
    set<node> s;
    s.insert((node){4,5});
    s.insert((node){3,9});
    s.insert((node){2,8});
    s.insert((node){4,5});
    for(auto it=s.begin();it!=s.end();it++){
        cout<<it->x<<" "<<it->y<<endl;
    }
    for(auto it=s.rbegin();it!=s.rend();it++){ //反向迭代器
        cout<<it->x<<" "<<it->y<<endl;
    }
    /*
    set<int> s;
    s.insert(5);
    s.insert(6);
    s.insert(5);
    s.insert(9);
    s.insert(2);
    s.insert(3);
    cout<<s.size()<<endl;
    if(s.count(2)==1){
        cout<<"yes"<<endl;
    }
    if(s.count(1)==0){
        cout<<"no"<<endl;
    }
    s.erase(2);
    if(s.count(2)==0){
        cout<<"no"<<endl;
    }else{
        cout<<"yes"<<endl;
    }
    for(auto it=s.begin();it!=s.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    */
    return 0;
}