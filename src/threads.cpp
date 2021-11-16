#include <time.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "./util.h"

using namespace std;
using namespace chrono;

int main(int argc, char **argv) {
  if (argc < 3) {
    cout << "Not enough arguments" << endl;
    exit(1);
  }

  auto filename1 = argv[1];
  auto filename2 = argv[2];

  vector<vector<int>> array1 = vector<vector<int>>();
  vector<vector<int>> array2 = vector<vector<int>>();

  read_array_from_file(&array1, filename1);
  read_array_from_file(&array2, filename2);

  vector<vector<int>> product = vector<vector<int>>();
  vector<thread> threads = vector<thread>();

  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  for (size_t i = 0; i < array1.size(); i++) {
    product.push_back(vector<int>());

    for (size_t j = 0; j < array2[0].size(); j++) {
      auto multiply = [i, j, array1, array2, &product]() {
        int result = 0;

        for (size_t k = 0; k < array1[0].size(); k++) {
          result += array1[i][k] * array2[k][j];
        }

        product[i].push_back(result);
      };

      threads.push_back(thread(multiply));
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
