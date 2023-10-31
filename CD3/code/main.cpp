#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int id;
  int h;
};

struct Vertex {
  Node start;
  Node end;
  int length;
};

int s, e, n_vertex, n_edge, open[1255], close[1255];
vector<Vertex> vertices;
vector<Node> nodes;

void read_file() {
  ifstream f;
  f.open("../test_cases/graph1.txt");
  f >> n_edge >> n_vertex >> s >> e;
  for (int i = 0; i < n_vertex; i++) {
    int a, b, c;
    f >> a >> b >> c;

    Node n1, n2;
    n1.id = a;
    n2.id = b;

    Vertex v;
    v.start = n1;
    v.end = n2;
    v.length = c;

    vertices.push_back(v);
  }

  for (int i = 1; i <= n_edge; i++) {
    int a;
    f >> a;

    for (auto &v : vertices) {
      if (v.start.id == i) {
        v.start.h = a;
      }
      if (v.end.id == i) {
        v.end.h = a;
      }
    }
    close[i] = 0;
    open[i] = 0;
  }
}

bool check_null_open() {
  for (int i = 1; i <= n_edge; i++) {
    if (open[i]) {
      return false;
    }
  }
  return true;
}

int find_best_vertex() {

  int max_f = 0;
  int flag = 0;
  for (int i = 1; i <= n_edge; i++) {
    if (open[i] > max_f && open[i] != -1) {
      max_f = open[i];
      flag = i;
    }
  }
}

void solve() {
  open[s] = -1;
  close[s] = 1;
  int max_length = 0;
  while (!check_null_open()) {
    int max_f = -1;
    for (auto v : vertices) {
      if (v.start.id == s) {
        int f = v.length + v.end.h;
        open[v.end.id] = f;
      }
    }
    s = find_best_vertex();
    open[s] = -1;
  }
}

int main() {
  read_file();
  solve();
  return 0;
}
