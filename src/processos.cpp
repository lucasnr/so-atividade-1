#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
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

  int rows = array1.size(), cols = array2[0].size();
  matrix product = matrix();
  initialize_array(&product, rows, cols);

  int index = 0, counter = 1;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (counter == 1) {
        pid_t pid = fork();
        if (pid == 0) {
          // child
          calculate_array_piece(&product, i, j, array1, array2, p, "procesos", index);
					exit(EXIT_SUCCESS); // prevent child from doing anything else
        }

				index++;
        counter = p;
      } else {
        counter--;
      }
    }
  }

  return 0;
}
