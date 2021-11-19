#include <chrono>
#include <iostream>
#include <vector>

#include "./util.h"

using namespace std;

int main(int argc, char **argv) {
  if (argc < 3) {
    cout << "Not enough arguments" << endl;
    exit(1);
  }

  auto filename1 = argv[1];
  auto filename2 = argv[2];

  int rows1, columns1;
  vector<int> array1 = vector<int>();
  int rows2, columns2;
  vector<int> array2 = vector<int>();

  read_array_from_file(&array1, &rows1, &columns1, filename1);
  read_array_from_file(&array2, &rows2, &columns2, filename2);

  vector<int> product = vector<int>();

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  for (size_t i = 0; i < rows1; i++) {
    for (size_t j = 0; j < columns2; j++) {
      int result = 0;

      for (size_t k = 0; k < columns1; k++) {
        int a = array1[i * columns1 + k];
        int b = array2[(k * columns2) + j];
        result += a * b;
      }

      product.push_back(result);
    }
  }
  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  auto duration =
      chrono::duration_cast<chrono::milliseconds>(end - begin).count();
  write_array_to_file(product, rows1, columns2, "sequencial.txt", duration);

  return 0;
}
