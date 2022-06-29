#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main(){
    string str;
    str="abc";
    str+="12345";
    cout<<str<<endl;
    for(int i=0;i<str.size();i++){
        cout<<str[i];
    }
    cout<<endl<<str.length()<<endl;
    if(str.find("c12")!=string::npos){ //没找到string::npos 值是-1，size_t 类型
        cout<<"yes"<<str.find("c12")<<endl;
    }
    if(str.find("c12",4)==string::npos){ 
        cout<<"no"<<endl;
    }
    str.insert(5,"xyz");
    cout<<str<<endl;
    string temp=str.substr(3,2);
    cout<<temp<<endl;
    
    temp=str.substr(3);
    cout<<temp<<endl;

    str.replace(2,2,"999");
    cout<<str<<endl;

    reverse(str.begin(),str.end());
    cout<<str<<endl;
    return 0;
}