#include<stdio.h>
#include<stdlib.h>

#define KEY(n) (n ? n->key : 0)
#define CNT(n) (n ? n->cnt : 0)

#define TEST(func) {\
    while(~scanf("%d", &key)){\
        if(key==-1) break;\
        root=func(root,key);\
        printf("\n===%s %d to BTS===\n", #func, key);\
        output(root);\
        inorder_output(root), printf("\n");\
    }\
}

typedef struct Node{
    int key;
    int cnt;
    Node *lchild, *rchild;
}Node;

Node *getNewNode(int key){
    Node *p = (Node *)malloc(sizeof(Node));
    p->key=key;
    p->cnt=1;
    p->lchild = p->rchild = NULL;
    return p;
}
void update(Node *root){
    root->cnt=CNT(root->lchild) + CNT(root->rchild) + 1;
    return ;
}
Node *insert(Node *root, int key) {
    if(root==NULL) return getNewNode(key);
    if(root->key == key) return root;
    else if(root->key < key) root->rchild = insert(root->rchild, key);
    else root->lchild = insert(root->lchild, key);
    update_cnt(root);
    return root;
}
Node *predecessor(Node *root) {
    Node *tmp=root->lchild;
    while(tmp->rchild) tmp=tmp->rchild;
    return tmp;
}
Node *erase(Node *root, int key) {
    if(!root) return root;
    if(root->key > key) root->lchild = erase(root->lchild, key);
    else if(root->key < key) root->rchild = erase(root->rchild, key);
    else{
        if(root->lchild == NULL || root->rchild == NULL) {
            Node *tmp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return tmp;
        }else{
            Node *tmp = predecessor(root);
            root->key=tmp->key;
            root->lchild = erase(root->lchild, tmp->key);
        }
    }
    update_cnt(root);
    return root;
}
void clear(Node *root) { //后序遍历删除节点
    if(!root) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}
void print_node(Node *root) {
    printf("( %3d | %3d %3d )\n",
        KEY(root),
        KEY(root->lchild), KEY(root->rchild)
    );
    return ;
}
Node *search(Node *root, int key) {
    if(root==NULL) return NULL;
    if(root->key == key) return root;
    if(root->key > key) return search(root->lchild, key);
    return search(root->rchild, key);
}

Node *__find_k(Node *root, int k) {
    if(CNT(root->lchild) > k) return __find_k(root->lchild, k);
    if(CNT(root->lchild)+1 == k) return root;
    return __find_k(root->rchild, k-CNT(root->lchild)-1);
}
Node *find_k(Node *root, int k){
    if(k<=0 || k>CNT(root)) return NULL;
    return __find_k(root, k);
}
void output_range(Node *root, int l,int r){
    if(root==NULL) return ;
    output_range(root->lchild,l,r);
    if(root->key<=r && root->key >=l) printf("%d ",root->key);
    output_range(root->rchild,l,r);
    return ;
}
void output(Node *root){ //先序遍历
    if(!root) return ;
    print_node(root);
    output(root->lchild);
    output(root->rchild);
    return;
}
void inorder_output(Node *root) {
    if(!root) return ;
    inorder_output(root->lchild);
    printf("%d ", root->key);
    inorder_output(root->rchild);
    return ;
}
int main(){
    Node *root=NULL;
    int key;
    //insert operator
    TEST(insert);
    int l,r;
    while(~scanf("%d%d", &l,&r)){
        if(l==-1) break;
        printf("find range")
    }
    //erase operator
    TEST(erase);
    clear(root);
    return  0;
}