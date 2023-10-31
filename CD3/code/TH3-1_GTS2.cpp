#include <fstream>
#include <iostream>
using namespace std;

int matrix[1230][1230], completed[1230], tour[1230], s[31], cost = 0, n, n_city;

void read_file() {
  ifstream f;
  f.open("../test_cases/GTS2c.txt");
  f >> n >> n_city;
  for (int i = 1; i <= n_city; i++) {
    f >> s[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      f >> matrix[i][j];
      completed[j] = 0;
      tour[j] = 0;
    }
  }
}

void reset() {
  cost = 0;
  for (int i = 1; i <= n; i++) {
    completed[i] = 0;
    tour[i] = 0;
  }
}

void travel(int start) {
  int tempStart = start;
  int city = 2;
  int tempFlag;
  int tempCost;
  while (city <= n) {
    tempCost = 10000000;
    for (int i = 1; i <= n; i++) {
      if (tempCost > matrix[start][i] && matrix[start][i] != 0 &&
          completed[i] == 0) {
        tempCost = matrix[start][i];
        tempFlag = i;
      }
    }

    tour[city] = tempFlag;
    completed[tempFlag] = 1;

    city++;
    cost += tempCost;
    start = tempFlag;
  }
  cost += matrix[tempFlag][tempStart];
}

int main() {
  read_file();
  int min_cost = 1e6;
  for (int i = 1; i <= n_city; i++) {
    reset();
    completed[s[i]] = 1;
    tour[s[i]] = 1;

    travel(s[i]);
    if (cost < min_cost) {
      min_cost = cost;
    }
  }

  cout << min_cost;

  return 0;
}
