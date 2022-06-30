#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct record {
  int hh, mm, ss, totalss;
  string tag;
};
int N, K;
unordered_map<string, vector<record>> M;
unordered_map<string, int> M2;

char c;
int in_school[86400] = {0};
int out_school[86400] = {0};
bool cmp(record x, record y) { return x.totalss < y.totalss; }
int main() {
  int i, j, k, l;
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    string car;
    record r;
    cin >> car >> r.hh >> c >> r.mm >> c >> r.ss >> r.tag;
    r.totalss = r.hh * 3600 + r.mm * 60 + r.ss;
    M[car].push_back(r);
  }

  for (auto it : M) {
    auto A = it.second;
    sort(A.begin(), A.end(), cmp);
    for (i = 0; i < A.size();) {
      if (A[i].tag == "in") {
        if (i + 1 < A.size() && A[i + 1].tag == "out") {
          in_school[A[i].totalss]++;
          out_school[A[i + 1].totalss]++;
          M2[it.first] += A[i + 1].totalss - A[i].totalss;
          i += 2;
        } else {
          i++;  //直接作废
        }
      } else {
        i++;
      }
    }
  }
  int car_num[86400] = {0};
  for (i = 0, j = 0; i < 86400; i++) {
    j += in_school[i];
    j -= out_school[i];
    car_num[i] = j;
  }
  for (i = 0; i < K; i++) {
    int hh, mm, ss;
    cin >> hh >> c >> mm >> c >> ss;
    int totalss = hh * 3600 + mm * 60 + ss;
    cout << car_num[totalss] << endl;
  }
  int maxtime = 0;
  vector<string> maxcars;
  for (auto it : M2) {
    if (it.second > maxtime) {
      maxtime = it.second;
      maxcars = {it.first};
    } else if (it.second == maxtime) {
      maxcars.push_back(it.first);
    }
  }
  sort(maxcars.begin(), maxcars.end());
  for (string each : maxcars) {
    cout << each << " ";
  }
  printf("%02d:%02d:%02d", maxtime / 3600, maxtime / 60 % 60, maxtime % 60);

  return 0;
}