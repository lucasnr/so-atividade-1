#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "./util.h"

using namespace std;
using matrix = vector<vector<int>>;

void calculate_at_position_thread(matrix *array, int row, int col, matrix a, matrix b, int p) {
	int rows = (*array).size(), cols = (*array)[0].size();

	col = col - 1;
	for (size_t j = 0; j < p; j++) {
		col = col + 1;

		if (col == cols) {
			col = 0;
			row = row + 1;
		}

		if (row == rows) return;

		calculate_at_position(array, row, col, a, b);
	}
}

int main(int argc, char **argv) {
  if (argc < 4) {
    cout << "Not enough arguments" << endl;
    exit(1);
  }

  auto filename1 = argv[1];
  auto filename2 = argv[2];
  int p = atoi(argv[3]);

  matrix array1 = matrix();
  matrix array2 = matrix();

  read_array_from_file(&array1, filename1);
  read_array_from_file(&array2, filename2);

  vector<thread> threads = vector<thread>();

	int rows = array1.size(), cols = array2[0].size();
  matrix product = matrix();
	initialize_array(&product, rows, cols);

	int counter = 1;
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
			if (counter != 1) {
				counter--;
			} else {
      	threads.push_back(thread(calculate_at_position_thread, &product, i, j, array1, array2, p));
				counter = p;
			}
    }
  }

  for (auto &th : threads) {
    if (th.joinable()) th.join();
  }
  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  auto duration =
      chrono::duration_cast<chrono::milliseconds>(end - begin).count();
  write_array_to_file(product, "threads.txt", duration);

  return 0;
}
