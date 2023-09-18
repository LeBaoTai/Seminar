#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

#define INF 1e9
#define ll long long

ll n;
ll dist[25][25];
ll dp[25][1 << 25];

void read_file() {
  ifstream fin;
  fin.open("../test_case/tsp_20vertex.txt");

  fin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> dist[i][j];
    }
  }
}

ll tsp(int i, int mask) {
  if (mask == (1 << n) - 1)
    return dist[i][0]; // return trip to starting city
  if (dp[i][mask] != -1)
    return dp[i][mask];

  ll ans = INF;
  for (int j = 0; j < n; j++) {
    if (i != j && !(mask & (1 << j))) {
      ans = min(ans, dist[i][j] + tsp(j, mask | (1 << j)));
    }
  }
  return dp[i][mask] = ans;
}

int main() {
  auto start_count = chrono::high_resolution_clock::now();
  read_file();
  // Initialization
  memset(dp, -1, sizeof dp);

  // Input graph

  cout << "Cost: " << tsp(0, 1) << "\n";
  auto end_count = chrono::high_resolution_clock::now();
  cout << "Time: "
       << chrono::duration_cast<chrono::microseconds>(end_count - start_count)
                  .count() /
              1000000.0;

  return 0;
}
