#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

#include "./util.h"

using namespace std;
using matrix = vector<vector<int>>;
using time_point = chrono::steady_clock::time_point;

void calculate_at_position_thread(matrix *array, int row, int col, matrix a, matrix b, int p, int index) {
	time_point begin = chrono::steady_clock::now();

	int first_row = row, first_col = col;
	int rows = (*array).size(), cols = (*array)[0].size();

	col = col - 1;
	for (size_t j = 0; j < p; j++) {
		col = col + 1;

		if (col == cols) {
			col = 0;
			row = row + 1;
		}

		if (row == rows) break;

		calculate_at_position(array, row, col, a, b);
	}

	time_point end = chrono::steady_clock::now();
  auto duration =
      chrono::duration_cast<chrono::milliseconds>(end - begin).count();

	ostringstream filename;
	filename << "threads-" << (index + 1) << ".txt";

  write_array_piece_to_file(*array, first_row, first_col, p, filename.str(), duration);
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

  vector<time_point> beginnings = vector<time_point>();
  vector<time_point> endings = vector<time_point>();
  vector<thread> threads = vector<thread>();

	int rows = array1.size(), cols = array2[0].size();
  matrix product = matrix();
	initialize_array(&product, rows, cols);

	int index = 0, counter = 1;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
			if (counter == 1) {
      	threads.push_back(thread(calculate_at_position_thread, &product, i, j, array1, array2, p, index++));
				counter = p;
			} else {
				counter--;
			}
    }
  }

  for (auto &th : threads) {
    if (th.joinable()) th.join();
  }

  return 0;
}
