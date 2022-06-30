#include<iostream>
#include<stack>
using namespace std;
int main(){
    stack<int> sta;
    sta.push(7);
    sta.push(10);
    sta.push(2);
    sta.push(6);
    cout<<sta.size()<<endl;
    cout<<sta.top()<<endl;
    while(!sta.empty()){
        cout<<sta.top()<<endl;
        sta.pop();
    }
    cout<<sta.size()<<endl; 
    cout<<sta.top()<<endl;  // 会段错误
    return 0;
}