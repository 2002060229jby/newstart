#include<iostream>
#include<queue>
using namespace std;
struct node{
    int x, y;
    bool operator< (const node &b)const {
        return this->x<b.x;
    }
};
struct cmp{ //仿函数
    bool operator() (const node &a, const node &b) {
        return a.x < b.x;
    }
};
int main(){
    // 优先队列
    priority_queue<node ,vector<node>, cmp> que;
    // priority_queue<node> que;
    que.push((node){5,6});
    que.push((node){2,9});
    que.push((node){7,5});
    while(!que.empty()){
        cout<<que.top().x<<" "<<que.top().y<<endl;
        que.pop();
    }
    /*
    priority_queue<int, vector<int>, greater<int>> que;//小顶堆，否则默认是less<int>大顶堆 
    que.push(6);
    que.push(2);
    que.push(5);
    que.push(9);
    que.push(8);
    cout<<que.size()<<endl;
    while(!que.empty()){
        cout<<que.top()<<endl;
        que.pop();
    }
    */
    return 0;
}