#include<iostream>
#include<deque>
using namespace std;
struct node{
    int x, y;
};
int main(){
    // 双端队列
    // 他维护了一个内存表，所以内存空间不是连续的，但还支持连续访问
    deque<int> que;
    que.push_back(5);
    que.push_back(8);
    que.push_front(9);
    que.push_front(2);
    for(int i=0;i<que.size();i++){
        cout<<que[i]<<" ";
    }
    cout<<endl;
    while(!que.empty()){
        cout<<que.front()<<" "<<que.back()<<endl;
        if(que.size() % 2==0){
            que.pop_back();
        }else{
            que.pop_front();
        }
    }
    
    return 0;
}