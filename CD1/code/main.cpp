#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int a[50][50], c[50][50], n, start = 0;
vector<int> vec;

void read_file() {
  ifstream fin;
  fin.open("../test_case/tsp_4vertex.txt");

  if (!fin.is_open()) {
    cout << "khong co file";
    return;
  };

  fin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      fin >> a[i][j];
    }
    if (i != 1)
      vec.push_back(i);
  }
}

int solve(int i, vector<int> vec) {
  if (vec.empty()) {
    return a[i][1];
  }

  int res = 10e6;
  for (int j = 1; j <= n; j++) {
    if (i != j && j != 1) {
      auto it = std::find(vec.begin(), vec.end(), j);
      vec.erase(it);
      res = min(res, solve(j, vec) + a[i][j]);
    }
  }
  return res;
}

int main() {
  read_file();
  cout << "Min cost: " << solve(1, vec) << endl;
  return 0;
}
