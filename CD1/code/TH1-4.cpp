#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

#define MAX 51        // Số đỉnh tối đa
int n;                // Số đỉnh
int graph[MAX][MAX];  // Ma trận kề của đồ thị
int color[MAX];       // Mảng lưu màu của các đỉnh
int min_colors = MAX; // Số màu tối thiểu cần tô

void read_file() {
  ifstream fin;
  fin.open("../test_case/color_50vertex.txt");

  fin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> graph[i][j];
    }
  }
}

// Hàm kiểm tra xem có thể tô màu cho đỉnh v với màu c hay không
bool isSafe(int v, int c) {
  for (int i = 0; i < n; i++) {
    if (graph[v][i] && color[i] == c) {
      return false;
    }
  }
  return true;
}

// Hàm đệ quy để tô màu đồ thị
bool graphColoringUtil(int v) {
  if (v == n) {
    // Nếu đã tô màu cho tất cả các đỉnh
    int num_colors = 0;
    for (int i = 0; i < n; i++) {
      if (color[i] > num_colors) {
        num_colors = color[i];
      }
    }
    if (num_colors < min_colors) {
      min_colors = num_colors;
    }
    return true;
  }

  for (int c = 1; c <= n; c++) {
    if (isSafe(v, c)) {
      color[v] = c;
      if (graphColoringUtil(v + 1)) {
        return true;
      }
      color[v] = 0;
    }
  }
  return false;
}

// Hàm chính để tô màu đồ thị
void graphColoring() {
  for (int i = 0; i < n; i++) {
    color[i] = 0;
  }

  if (graphColoringUtil(0)) {
    cout << "So mau: " << min_colors << endl;
  }
}

int main() {
  auto start_count = chrono::high_resolution_clock::now();
  read_file();
  graphColoring();
  auto end_count = chrono::high_resolution_clock::now();
  cout << "Time: "
       << chrono::duration_cast<chrono::microseconds>(end_count - start_count)
                  .count() /
              1000000.0
       << endl;
  return 0;
}
