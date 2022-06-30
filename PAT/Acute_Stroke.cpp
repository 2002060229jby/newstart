#include <iostream>
#include <queue>
using namespace std;
struct node {
  int z, x, y;
};

queue<node> que;
int M, N, L, T, ans, count;
int mmap[62][1288][130];
int mark[62][1288][130];
int dir[6][3] = {
    1, 0, 0, 0, 1, 0, 0, 0, 1, -1, 0, 0, 0, -1, 0, 0, 0, -1,
};

void dfs(int z, int x, int y) {
  mark[z][x][y] = 1;
  count++;
  for (int i = 0; i < 6; i++) {
    int xx = x + dir[i][0];
    int yy = y + dir[i][1];
    int zz = z + dir[i][2];
    if (mmap[zz][xx][yy] == 1 && mark[zz][xx][yy] == 0) {
      dfs(zz, xx, yy);
    }
  }
}

int main() {
  cin >> M >> N >> L >> T;
  for (int i = 1; i <= L; i++) {
    for (int j = 1; j <= M; j++) {
      for (int k = 1; k <= N; k++) {
        cin >> mmap[i][j][k];
        if (mmap[i][j][k] == 1) {
          que.push((node){i, j, k});
        }
      }
    }
  }
  while (!que.empty()) {
    node tmp = que.front();
    que.pop();
    if (mark[tmp.z][tmp.x][tmp.y] == 0) {
      count = 0;
      dfs(tmp.z, tmp.x, tmp.y);
      if (count >= T) {
        ans += count;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
// 3 4 5 2
// 1 1 1 1
// 1 1 1 1
// 1 1 1 1
// 0 0 1 1
// 0 0 1 1
// 0 0 1 1
// 1 0 1 1
// 0 1 0 0
// 0 0 0 0
// 1 0 1 1
// 0 0 0 0
// 0 0 0 0
// 0 0 0 1
// 0 0 0 1
// 1 0 0 0