#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ifstream fin;
  fin.open("input.txt");

  int n;
  fin >> n;
  cout << n << endl;
  return 0;
}
