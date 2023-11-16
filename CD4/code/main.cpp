/*
 * Cau truc thu muc //FIXME:
 * |
 * | code
 *   | main.cpp
 *
 * | test_cases
 *   | tsp1.txt
 *   | tsp2.txt
 *   | tsp3.txt
 *   | tsp4.txt
 *
 * | output
 *   | tsp1.txt
 *   | tsp2.txt
 *   | tsp3.txt
 *   | tsp4.txt
 * */

#include <bits/chrono.h>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

// thay doi thu tu file
#define FILE 4

int n, chi_phi_thap_nhat = 1e7;
int a[1250][1250], s[1250], s_[1250];

void doc_file() {
  string file_name = "../test_cases/tsp" + std::to_string(FILE) + ".txt";
  ifstream f;
  f.open(file_name);
  f >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      f >> a[i][j];
    }
  }
}

void ghi_file() {
  string file_name = "../output/tsp" + std::to_string(FILE) + ".txt";
  ofstream f;
  f.open(file_name, std::ofstream::trunc);
  f << n << " " << chi_phi_thap_nhat << endl;
  for (int i = 1; i <= n; i++) {
    f << s[i] << " ";
  }
  f << endl;
}

void khoi_tao_loi_ban_dau() {
  int count = 1;
  int check[1250] = {0};
  while (count < n + 1) {
    int num = rand() % n + 1;
    if (!check[num]) {
      check[num] = 1;
      s[count] = num;
      count++;
    }
  }
  int start = s[1];
  for (int i = 1; i <= n - 1; i++) {
    chi_phi_thap_nhat += a[s[i]][s[i + 1]];
  }
  chi_phi_thap_nhat += a[s[n]][start];
}

void chien_luoc_dao() {
  int u = rand() % n + 1;
  int v = rand() % n + 1;

  // chuan hoa u < v
  if (u > v) {
    int temp = u;
    u = v;
    v = temp;
  }

  vector<int> temp;
  for (int i = u; i <= v; i++) {
    temp.push_back(s[i]);
  }
  for (int i = 1; i <= u - 1; i++) {
    s_[i] = s[i];
  }
  for (int i = u; i <= v; i++) {
    s_[i] = temp.back();
    temp.pop_back();
  }
  for (int i = v + 1; i <= n; i++) {
    s_[i] = s[i];
  }
}

void thay_the_s() {
  for (int i = 1; i <= n; i++) {
    s[i] = s_[i];
  }
}

int tinh_toan_chi_phi() {
  int start = s_[1];
  int chi_phi = 0;
  for (int i = 1; i <= n - 1; i++) {
    chi_phi = a[s[i]][s[i + 1]];
  }
  chi_phi += a[s[n]][start];
  return chi_phi;
}

void in_s() {
  for (int i = 1; i <= n; i++) {
    cout << s[i] << " ";
  }
  cout << endl;
}

void in_s_() {
  for (int i = 1; i <= n; i++) {
    cout << s_[i] << " ";
  }
  cout << endl;
}

void giai() {
  int dem = 1000000;
  auto bat_dau = std::chrono::steady_clock::now();
  khoi_tao_loi_ban_dau();
  while (dem--) {
    chien_luoc_dao();
    int chi_phi = tinh_toan_chi_phi();
    if (chi_phi < chi_phi_thap_nhat) {
      chi_phi_thap_nhat = chi_phi;
      thay_the_s();
      ghi_file();
      dem++;
    }
  }
  auto ket_thuc = std::chrono::steady_clock::now();
  cout << "Thoi gian chay: "
       << std::chrono::duration_cast<std::chrono::duration<double>>(ket_thuc -
                                                                    bat_dau)
              .count();
}

int main() {
  srand(time(nullptr));
  doc_file();
  giai();
  return 0;
}
