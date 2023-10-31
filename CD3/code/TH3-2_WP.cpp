#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
  int color;
  int idx;
  vector<Node> neighbours;

  bool isAdjacentTo(Node &other) {
    for (auto &neighbour : neighbours) {
      if (neighbour.idx == other.idx) {
        return true;
      }
    }
    return false;
  };
};

int matrix[1255][1255], n, total_color = 0;
vector<Node> graph;

void read_file() {
  ifstream f;
  f.open("../test_cases/color4.txt");
  f >> n;
  for (int i = 1; i <= n; i++) {
    Node node;
    node.color = 0;
    node.idx = i;

    for (int j = 1; j <= n; j++) {
      f >> matrix[i][j];
      if (matrix[i][j] == 1) {
        Node temp;
        temp.color = 0;
        temp.idx = j;
        node.neighbours.push_back(temp);
      }
    }
    graph.push_back(node);
  }
}

void merge(std::vector<Node> &arr, int const left, int const mid,
           int const right) {
  auto const subArrayOne = mid - left + 1;
  auto const subArrayTwo = right - mid;

  std::vector<Node> leftArray(subArrayOne), rightArray(subArrayTwo);

  for (auto i = 0; i < subArrayOne; i++)
    leftArray[i] = arr[left + i];
  for (auto j = 0; j < subArrayTwo; j++)
    rightArray[j] = arr[mid + 1 + j];

  auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
  int indexOfMergedArray = left;

  while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
    if (leftArray[indexOfSubArrayOne].neighbours.size() >
        rightArray[indexOfSubArrayTwo].neighbours.size()) {
      arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
      indexOfSubArrayOne++;
    } else {
      arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
      indexOfSubArrayTwo++;
    }
    indexOfMergedArray++;
  }

  while (indexOfSubArrayOne < subArrayOne) {
    arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
    indexOfSubArrayOne++;
    indexOfMergedArray++;
  }

  while (indexOfSubArrayTwo < subArrayTwo) {
    arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
    indexOfSubArrayTwo++;
    indexOfMergedArray++;
  }
}

void mergeSort(std::vector<Node> &arr, int const begin, int const end) {
  if (begin >= end)
    return;

  auto mid = begin + (end - begin) / 2;
  mergeSort(arr, begin, mid);
  mergeSort(arr, mid + 1, end);
  merge(arr, begin, mid, end);
}

void coloring() {
  for (int i = 0; i < graph.size(); i++) {
    if (graph[i].color == 0) {
      total_color++;
      graph[i].color = total_color;
      for (int j = i + 1; j < graph.size(); j++) {
        if (graph[j].color == 0 && !graph[i].isAdjacentTo(graph[j])) {
          graph[j].color = total_color;
        }
      }
    }
  }
}

int main() {
  read_file();
  mergeSort(graph, 0, graph.size() - 1);
  cout << graph[0].idx << endl;
  coloring();
  cout << total_color << endl;
}
