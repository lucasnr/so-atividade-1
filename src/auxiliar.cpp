#include <time.h>

#include <iostream>
#include <vector>

#include "./util.h"

using namespace std;

int get_random_integer() { return rand() % 10 + 1; }

void fill_array_with_random_integers(vector<int> *array, int rows, int columns) {
	int limit = rows * columns;
  for (size_t i = 0; i < limit; i++) {
    int random = get_random_integer();
    (*array).push_back(random);
  }
}

int main(int argc, char const *argv[]) {
  if (argc < 5) {
    cout << "Not enough arguments" << endl;
    exit(1);
  }

  int rows1 = atoi(argv[1]), columns1 = atoi(argv[2]);
  int rows2 = atoi(argv[3]), columns2 = atoi(argv[4]);

  if (columns1 != rows2) {
    cout << "Invalid arguments. Cannot multiply" << endl;
    exit(1);
  }

  srand(time(NULL));

  vector<int> array1 = vector<int>();
  fill_array_with_random_integers(&array1, rows1, columns1);

  vector<int> array2 = vector<int>();
  fill_array_with_random_integers(&array2, rows2, columns2);

  write_array_to_file(array1, rows1, columns1, "m1.txt");
  write_array_to_file(array2, rows2, columns2, "m2.txt");

  return 0;
}
