#include <time.h>

#include <chrono>
#include <iostream>
#include <vector>

#include "./util.h"

using namespace std;
using namespace chrono;

int main(int argc, char **argv) {
  if (argc < 5) {
    cout << "Not enough arguments" << endl;
    exit(1);
  }

  int n1 = atoi(argv[1]), m1 = atoi(argv[2]);
  int n2 = atoi(argv[3]), m2 = atoi(argv[4]);

  if (m1 != n2) {
    cout << "Invalid arguments. Cannot multiply" << endl;
    exit(1);
  }

  srand(time(NULL));

  vector<vector<int>> array1 = vector<vector<int>>();
  fill_array_with_random_integers(&array1, n1, m1);

  vector<vector<int>> array2 = vector<vector<int>>();
  fill_array_with_random_integers(&array2, n2, m2);

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  vector<vector<int>> product = vector<vector<int>>();
  for (size_t i = 0; i < n1; i++) {
    product.push_back(vector<int>());

    for (size_t j = 0; j < m2; j++) {
      int result = 0;

      for (size_t k = 0; k < m1; k++) {
        result += array1[i][k] * array2[k][j];
      }

      product[i].push_back(result);
    }
  }
  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  cout << "Tempo = "
       << chrono::duration_cast<chrono::milliseconds>(end - begin).count()
       << " [ms]" << endl;

  return 0;
}
