#include<iostream>
#include<queue>
using namespace std;
struct node{
    int x, y;
};
int main(){
    queue<node> que1;
    que1.push((node){5,6});
    que1.push((node){1,8});
    que1.push((node){9,2});
    while(!que1.empty()){
        node temp = que1.front();
        cout<<temp.x<<" "<<temp.y<<endl;
        // cout<<que1.front().x<<" "<<que1.front().y<<endl;
        que1.pop();
    }
    /*
    queue<int> que;
    que.push(5);
    que.push(7);
    que.push(9);
    que.push(22);
    que.push(93);
    cout<<que.size()<<" "<<que.front()<<que.back()<<endl;
    while(!que.empty()){
        cout<<que.front()<<endl;
        que.pop();
    }
    cout<<que.size()<<endl;
    cout<<que.front()<<endl;
    */
    return 0;
}