#include <time.h>

#include <iostream>
#include <vector>

#include "./util.h"

using namespace std;
using matrix = vector<vector<int>>;

int get_random_integer() { return rand() % 10 + 1; }

void fill_array_with_random_integers(matrix *array, int n, int m) {
  for (size_t i = 0; i < n; i++) {
    (*array).push_back(vector<int>());

    for (size_t j = 0; j < m; j++) {
      auto random = get_random_integer();
      (*array)[i].push_back(random);
    }
  }
}

int main(int argc, char const *argv[]) {
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

  matrix array1 = matrix();
  fill_array_with_random_integers(&array1, n1, m1);

  matrix array2 = matrix();
  fill_array_with_random_integers(&array2, n2, m2);

  write_array_to_file(&array1, "ma.txt");
  write_array_to_file(&array2, "mb.txt");

  return 0;
}
