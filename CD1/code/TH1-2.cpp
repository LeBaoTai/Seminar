#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

#define MAX 51

/*
 * a: doc vao mang tu file
 * b: mang luu mau cac dinh
 * c: luu mau da duoc dung
 * */
int a[MAX][MAX], b[MAX], c[MAX], n;

void read_file() {
  ifstream fin;
  fin.open("../test_case/color_50vertex.txt");

  fin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> a[i][j];
    }
    b[i] = -1;
  }
}

int coloring() {
  b[0] = 0; // Gán màu 0 cho đỉnh đầu tiên

  for (int i = 1; i < n; i++) {
    for (int temp = 0; temp < n; temp++) {
      c[temp] = 0;
    }
    for (int j = 0; j < n; j++) {
      if (a[i][j] && b[j] != -1) {
        c[b[j]] = 1;
      }
    }

    // Tìm màu chưa được sử dụng (đánh số thấp nhất)
    int m = 0;
    while (c[m]) {
      m++;
    }

    b[i] = m; // Gán màu cho đỉnh u
  }

  // Tính số màu khác nhau đã sử dụng
  int max_color = -1;
  for (int i = 0; i < n; i++) {
    if (max_color < b[i]) {
      max_color = b[i];
    }
  }

  return max_color;
}

int main() {
  auto start_count = chrono::high_resolution_clock::now();
  read_file();
  cout << "So mau: " << coloring() + 1 << endl;
  auto end_count = chrono::high_resolution_clock::now();
  cout << "Time: "
       << chrono::duration_cast<chrono::milliseconds>(end_count - start_count)
                  .count() /
              1000000.0
       << endl;
  return 0;
}
