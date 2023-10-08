#include <fstream>
#include <iostream>

using namespace std;

#define NIL 0
#define INFI 100000

int a[105][105], d[105][105], p[105][105], n, s, e;

void read_file() {
  ifstream fin;
  fin.open("../test_cases/graph2.txt");
  fin >> n >> s >> e;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      fin >> a[i][j];
      if (i == j) {
        d[i][j] = 0;
      } else if (!a[i][j]) {
        d[i][j] = INFI;
        p[i][j] = NIL;
      } else {
        d[i][j] = a[i][j];
        p[i][j] = i;
      }
    }
  }
}

// su dung thuat toan Floyd - Warshall
void solve() {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (d[i][j] > d[i][k] + d[k][j] && i != j) {
          d[i][j] = d[i][k] + d[k][j];
          p[i][j] = p[k][j];
        }
      }
    }
  }
}

int main() {
  read_file();

  solve();

  // khoang canh tu 1 -> 49
  cout << d[s][e];
  // 66

  return 0;
}
