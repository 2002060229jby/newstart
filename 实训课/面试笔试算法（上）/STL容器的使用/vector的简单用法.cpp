#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    //是一片连续的内存空间

    vector<vector<int> > v(5,vector<int>(6,9)); //留一个空格是好习惯
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++){
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }

    //扩容规则
    /*
    vector<int> v;
    int temp=-1;
    for(int i=0;i<1000000;i++){//2倍的规则扩容，取决于编译器。
        if(temp!=v.capacity()){
            temp=v.capacity();
            cout<<temp<<endl;
        }
        v.push_back(i);
    }
    cout<<v.capacity()<<endl;
    */


    //初始化
    /*
    vector<int> v(9,-1); 
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    */

    // 压入元素
    /*
    for(int i=3;i<6;i++){
        v.push_back(i);
    }
    cout<<v.size()<<endl;
    for(int i=9;i>5;i--){
        v.push_back(i);
    }
    cout<<v.size()<<endl;
    v[0]=999;
    v[2]=777;
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    cout<<v[-999999]<<endl;//不会检查边界，需要注意
    */
   
    return 0;
}