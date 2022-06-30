#include<iostream>
#include<unordered_set>
using namespace std;

#define BASE 26

struct Node {
    Node() : flag(false), fail(nullptr) {
        for (int i = 0; i < BASE; i++) next[i] = nullptr;
        return ;
    }
    string *s;
    bool flag;
    Node *next[BASE];
    Node *fail;

};

struct Trie {
public:
    Trie() = default;
    void insert(string s) {
        Node *p = &root;
        for(auto x : s) {
            int ind = x - 'a';
            if (p->next[ind] == nullptr) p->next[ind] = new Node();
            p = p->next[ind];
        }
        if(p->flag == false) {
            p->flag = true;
            p->s = new string(s); 
        }
        return ;
    }

    void build_ac() {
        queue<Node *> q;
        for(int i=0;i<BASE;i++){
            if(root.next[i] ==nullptr) {
                continue;
            }
            root.next[i]->fail = &root;
            q.push(root.next[i]);
        }
        while(!q.empty()){
            Node *now = q.front(), *p;
            q.pop();
            for(int i=0;i<BASE;i++){
                if(now->next[i] == nullptr) continue;
                p = now->fail;
                while(p && p->next[i]==nullptr) {
                    p=p->next;
                }
                if(p) p=p->next[i];
                else p=&root;
                now->next[i]->fail=p;
                q.push(now->next[i]);
            }
        }
    }

    unordered_set<string> match(string &s) {
        unordered_set<string> ret;
        for(int i = 0;i < s.size(); i++) {
            Node *p = &root;
            for(int j = i; j < s.size();j++) {
                int ind = s[j] - 'a';
                if(p->next[ind] == nullptr) break;
                p = p->next[ind];
                if(p->flag) ret.insert(*(p->s));
            }
        }
        return ret;
    }
private:
    Node root;
};



int main(){
    int n;
    cin>>n;
    Trie tree;
    string s;
    for(int i = 0; i < n; i++) {
        cin>>s;
        tree.insert(s);
    }
    cin>>s;
    auto ans = tree.match(s);
    for(auto x:ans) cout<<x<<endl;
    cout<<"find: " <<ans.size()<<" item(s) "<<endl; 
    return 0;
}