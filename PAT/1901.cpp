
#include <iostream>
#include <stack>
using namespace std;

int M, N, L, T, ans;
int a[60][1286][128];
int b[60][1286][128];

struct three {
  int i, j, k;
  three(int _i, int _j, int _k) {
    i = _i;
    j = _j;
    k = _k;
  }
};

int main() {
  cin >> M >> N >> L >> T;
  int i, j, k, l;
  for (int i = 0; i < L; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < N; k++) {
        cin >> a[i][j][k];
      }
    }
  }
  for (int i = 0; i < L; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < N; k++) {
        if (a[i][j][k] == 1 && b[i][j][k] == 0) {
          int count = 0;
          stack<three> S;
          S.push(three(i, j, k));
          b[i][j][k] = 1;
          while (S.size()) {
            three t = S.top();
            S.pop();
            int i, j, k;
            i = t.i, j = t.j, k = t.k;
            count++;
            if (i - 1 >= 0 && a[i - 1][j][k] == 1 && !b[i - 1][j][k]) {
              S.push(three(i - 1, j, k));
              b[i - 1][j][k] = 1;
            }
            if (i + 1 >= 0 && a[i + 1][j][k] == 1 && !b[i + 1][j][k]) {
              S.push(three(i + 1, j, k));
              b[i + 1][j][k] = 1;
            }
            if (j - 1 >= 0 && a[i][j - 1][k] == 1 && !b[i][j - 1][k]) {
              S.push(three(i, j - 1, k));
              b[i][j - 1][k] = 1;
            }
            if (j + 1 >= 0 && a[i][j + 1][k] == 1 && !b[i][j + 1][k]) {
              S.push(three(i, j + 1, k));
              b[i][j + 1][k] = 1;
            }
            if (k - 1 >= 0 && a[i][j][k - 1] == 1 && !b[i][j][k - 1]) {
              S.push(three(i, j, k - 1));
              b[i][j][k - 1] = 1;
            }
            if (k + 1 >= 0 && a[i][j][k + 1] == 1 && !b[i][j][k + 1]) {
              S.push(three(i, j, k + 1));
              b[i][j][k + 1] = 1;
            }
          }
          if (count >= T) {
            ans += count;
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}