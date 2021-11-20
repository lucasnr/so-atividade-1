#include <iostream>
#include <thread>
#include <vector>

#include "./util.h"

using namespace std;
using matrix = vector<vector<int>>;

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

	int index = 0, counter = 1;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
			if (counter == 1) {
				thread th = thread(calculate_array_piece, &product, i, j, &array1, &array2, p, "threads", index++);
      	threads.push_back(move(th));
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
