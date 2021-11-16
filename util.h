#include <stdlib.h>

#include <iostream>
#include <vector>

using namespace std;

int get_random_integer() { return rand() % 5 + 1; }

void fill_array_with_random_integers(vector<vector<int>> *array, int n, int m) {
  for (size_t i = 0; i < n; i++) {
    (*array).push_back(vector<int>());
    for (size_t j = 0; j < m; j++) {
      (*array)[i].push_back(get_random_integer());
    }
  }
}

void print_array(vector<vector<int>> array) {
  for (size_t i = 0; i < array.size(); i++) {
    cout << "[";
    for (size_t j = 0; j < array[i].size(); j++) {
      cout << array[i][j];
      if (j != array[i].size() - 1) {
        cout << ", ";
      }
    }
    cout << "]" << endl;
  }
}
