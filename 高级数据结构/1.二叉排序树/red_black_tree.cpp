#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int key, color;  // color = 0 red, 1 black, 2 double black
  Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor)) void init_NIL() {//在main函数之前就执行了
  NIL->key = 0;
  NIL->color = 1;
  NIL->lchild = NIL->rchild = NIL;
  return;
}

Node *getNewNode(int key) {
  Node *p = (Node *)malloc(sizeof(Node));
  p->key = key;
  p->lchild = p->rchild = NIL;
  p->color = 0;  //新插入节点默认颜色为红色
  return p;
}

int has_red_child(Node *root) {
  return root->lchild->color == 0 || root->rchild->color == 0;
}

Node *left_rotate(Node *root) {
  printf("left rotate : %d\n", root->key);
  Node *new_root = root->rchild;
  root->rchild = new_root->lchild;
  new_root->lchild = root;
  return new_root;
}

Node *right_rotate(Node *root) {
  printf("right rotate : %d\n", root->key);
  Node *new_root = root->lchild;
  root->lchild = new_root->rchild;
  new_root->rchild = root;
  return new_root;
}

const char *insert_maintain_type[] = {
    "1 : change color", "2 : LL", "2 : LR", "2 : RR", "2 : RL",
};

Node *insert_maintain(Node *root) {
  if (!has_red_child(root)) return root;
  if (!(root->lchild->color == 0 && has_red_child(root->lchild)) &&
      !(root->rchild->color == 0 && has_red_child(root->rchild)))
    return root;
  // rotate
  int type = 0;
  if (root->rchild->color == 1) {  //叔叔节点是黑色,且叔叔节点在右边
    if (root->lchild->rchild->color == 0) {  // LR类型
      root->lchild = left_rotate(root->lchild);
      type += 1;
    }
    type += 1;
    root = right_rotate(root);
  } else if (root->lchild->color == 1) {  //叔叔节点在左边
    type = 2;
    if (root->rchild->lchild->color == 0) { 
      root->rchild = right_rotate(root->rchild);
      type += 1;
    }
    type += 1;
    root = left_rotate(root);
  }
  printf("insert maintain type = %s\n", insert_maintain_type[type]);
  root->color = 0;
  root->lchild->color = root->rchild->color = 1;
  return root;
}

Node *__insert(Node *root, int key) {
  if (root == NIL)
    return getNewNode(key);  //往一颗空树中插入，根节点应该是黑色。需要再封装一层。
  if (root->key == key) return root;
  if (root->key > key)
    root->lchild = __insert(root->lchild, key);
  else
    root->rchild = __insert(root->rchild, key);
  return insert_maintain(root);
}

Node *insert(Node *root, int key) {
  root = __insert(root, key);
  root->color = 1;
  return root;
}

const char *erase_maintain_type[] = {
    "red 1(right): change color",
    "red 2(left): change color",
    "black 1: no red child",
    "black 2: LL",
    "black 2: LR",
    "black 2: RR",
    "black 2: RL",
};

Node *erase_maintain(Node *root) {
  if (root->lchild->color != 2 && root->rchild->color != 2) return root;
  int type = 0;
  if (has_red_child(root)) {  //兄弟节点是红色。转换成为兄弟节点是黑色的情况。通过旋转，把黑色直接下沉。
    root->color = 0;
    if (root->lchild->color == 0)
      root = right_rotate(root);
    else
      root = left_rotate(root), type = 1;
    root->color = 1;
    if (type)
      root->lchild = erase_maintain(root->lchild);
    else
      root->rchild = erase_maintain(root->rchild);
    printf("brother is %s\n", erase_maintain_type[type]);
    return root;
  }
  //   do {
  //     if (root->rchild->color == 1) {  //情况一
  //       if (!has_red_child(root->rchild)) {
  //         root->lchild -= 1;
  //         root->rchild -= 1;
  //         root->color += 1;
  //         break;
  //       }
  //     } else {
  //       if (!has_red_child(root->lchild)) {
  //         root->lchild -= 1;
  //         root->rchild -= 1;
  //         root->color += 1;
  //         break;
  //       }
  //     }
  //   } while (0);  //编程技巧：循环内可以break
  if ((root->lchild->color == 1 && !has_red_child(root->lchild)) ||
      (root->rchild->color == 1 && !has_red_child(root->rchild))) {
    type = 2;
    root->lchild->color -= 1;
    root->rchild->color -= 1;
    root->color += 1;
    printf("brother is %s\n", erase_maintain_type[type]);
    return root;
  }
  type = 2;
  if (root->lchild->color == 1) {
    if (root->lchild->lchild->color != 0) {
      type += 1;
      root->lchild = left_rotate(root->lchild);
    }
    type += 1;
    root->lchild->color = root->color;  //新根节点颜色改成原根节点颜色
    root = right_rotate(root);
  } else {
    type = 3;

    if (root->rchild->rchild->color != 0) {
      type += 1;
      root->rchild = right_rotate(root->rchild);
    }
    type += 1;

    root->rchild->color = root->color;  //新根节点颜色改成原根节点颜色
    root = left_rotate(root);
  }
  root->lchild->color = root->rchild->color = 1;
  printf("brother is %s\n", erase_maintain_type[type]);
  return root;
}

Node *__erase(Node *root, int key) {
  if (root == NIL) return root;
  if (root->key > key)
    root->lchild = __erase(root->lchild, key);
  else if (root->key < key)
    root->rchild = __erase(root->rchild, key);
  else {
    if (root->lchild == NIL || root->rchild == NIL) {
      Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
      temp->color += root->color;  //度为0的情况也能兼容，加0等于没加
      free(root);
      return temp;
    } else {
      Node *temp = root->lchild;
      while (temp->rchild != NIL) temp = temp->rchild;
      root->key = temp->key;
      root->lchild = __erase(root->lchild, temp->key);
    }
  }
  return erase_maintain(root);
}

Node *erase(Node *root, int key) {
  root = __erase(root, key);
  root->color = 1;
  return root;
}

void clear(Node *root) {
  if (root == NIL) return;
  clear(root->lchild);
  clear(root->rchild);
  free(root);
  return;
}

void print_node(Node *root) {
  printf("( %d(%d) | %d, %d )\n", root->key, root->color, root->lchild->key,
         root->rchild->key);
  return;
}

void output(Node *root) {
  if (root == NIL) return;
  print_node(root);
  output(root->lchild);
  output(root->rchild);
  return;
}

int main() {
  Node *root = NIL;
  int key;
  // insert
  while (~scanf("%d", &key)) {
    if (key == -1) break;
    printf("\n===insert %d to red black tree===\n", key);
    root = insert(root, key);
    output(root);
  }
  // erase
  while (~scanf("%d", &key)) {
    if (key == -1) break;
    printf("\n===erase %d from red black tree===\n", key);
    root = erase(root, key);
    output(root);
  }
  clear(root);
  return 0;
}

//测试数据：1 4 9 5 7 8 6 3 2
//测试数据二：78 65 45 36 56 72 90 100 32 7 4 15 17 -1
// 90 36 45 56 4 15 7 32 -1