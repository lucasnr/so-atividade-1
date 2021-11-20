#include <chrono>
#include <iostream>
#include <vector>

#include "./util.h"

using namespace std;
using matrix = vector<vector<int>>;

int main(int argc, char **argv) {
  if (argc < 3) {
    cout << "Not enough arguments" << endl;
    exit(1);
  }

  auto filename1 = argv[1];
  auto filename2 = argv[2];

  matrix array1 = matrix();
  matrix array2 = matrix();

  read_array_from_file(&array1, filename1);
  read_array_from_file(&array2, filename2);

  matrix product = matrix();
	int rows = array1.size(), cols = array2[0].size();
	initialize_array(&product, rows, cols);

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      calculate_at_position(&product, i, j, &array1, &array2);
    }
  }
  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  auto duration =
      chrono::duration_cast<chrono::milliseconds>(end - begin).count();
  write_array_to_file(&product, "sequencial.txt", duration);

  return 0;
}
