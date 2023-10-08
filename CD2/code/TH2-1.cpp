#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, a[105][105], check[105];

struct Edge {
  int u, v, w;
  Edge(int u, int v, int w) : u(u), v(v), w(w){};
};

struct DisjointSet {
  vector<int> parent;
  vector<int> rank;
  int n;

  DisjointSet(int n) {
    this->n = n;
    parent.resize(n);
    rank.resize(n);

    for (int i = 0; i < n; i++) {
      parent[i] = i;
      rank[i] = 0;
    }
  }

  int check_cycle(int x) {
    if (parent[x] != x) {
      parent[x] = check_cycle(parent[x]);
    }
    return parent[x];
  }

  bool add_frame_tree(int x, int y) {
    int xroot = check_cycle(x);
    int yroot = check_cycle(y);

    if (xroot == yroot)
      return false;

    if (rank[xroot] < rank[yroot]) {
      parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
      parent[yroot] = xroot;
    } else {
      parent[yroot] = xroot;
      rank[xroot]++;
    }

    return true;
  }
};

void read_file() {
  ifstream fin;
  // file input
  fin.open("../test_cases/graph1.txt");

  fin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> a[i][j];
    }
    check[i] = 0;
  }
}

vector<Edge> input_egdes() {
  vector<Edge> edges;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (a[i][j])
        edges.push_back(Edge(i + 1, j + 1, a[i][j]));
    }
  }

  return edges;
}

void sort_edges(vector<Edge> &edges) {
  for (int i = 0; i < edges.size(); i++) {
    for (int j = i + 1; j < edges.size(); j++) {
      if (edges[i].w > edges[j].w) {
        swap(edges[i], edges[j]);
      }
    }
  }
}

void solve(vector<Edge> edges) {
  sort_edges(edges);
  vector<Edge> result;

  DisjointSet ds(n);

  int min_weight = 0;

  for (Edge e : edges) {
    if (ds.add_frame_tree(e.u, e.v)) {
      min_weight += e.w;
    }
  }

  cout << "Value: " << min_weight << endl;
  // 1269
}

int main() {

  read_file();

  vector<Edge> edges = input_egdes();

  solve(edges);
  return 0;
}
