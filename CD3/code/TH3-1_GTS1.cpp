#include <fstream>
#include <iostream>
using namespace std;

int matrix[1230][1230], completed[1230], tour[1230], cost = 0, n, s;

void read_file() {
  ifstream f;
  f.open("../test_cases/GTS1c.txt");
  f >> n >> s;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      f >> matrix[i][j];
      completed[j] = 0;
      tour[j] = 0;
    }
  }

  completed[s] = 1;
  tour[s] = 1;
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
  travel(s);
  cout << cost;
  return 0;
}
