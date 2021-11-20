#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using matrix = vector<vector<int>>;

void calculate_at_position(matrix *array, int row, int col, matrix a, matrix b) {
	int value = 0;

	for (size_t i = 0; i < a[row].size(); i++) {
		value += a[row][i] * b[i][col];
	}

	(*array)[row][col] = value;
}

void initialize_array(matrix *array, int rows, int cols) {
  for (size_t i = 0; i < rows; i++) {
    (*array).push_back(vector<int>());
    for (size_t j = 0; j < cols; j++) {
      (*array)[i].push_back(0);
    }
  }
}

void print_array(matrix array) {
  int rows = array.size(), cols = array[0].size();

  cout << rows << "x" << cols << endl;
  for (size_t i = 0; i < rows; i++) {
    cout << "[";
    for (size_t j = 0; j < cols; j++) {
      cout << array[i][j];
      if (j != cols - 1) cout << ", ";
    }
    cout << "]" << endl;
  }
}

void read_array_from_file(matrix *array, string filename) {
  int n, m;
  vector<int> values = vector<int>();

  ifstream file(filename);

  if (file.is_open()) {
    bool first_line = true;

    string line;
    while (getline(file, line)) {
      size_t pos = 0;
      string delimiter = " ";

      if (first_line) {
        string substring;
        while ((pos = line.find(delimiter)) != string::npos) {
          substring = line.substr(0, pos);
          n = atoi(substring.c_str());
          line.erase(0, pos + delimiter.length());
        }
        m = atoi(line.c_str());

        first_line = false;
        continue;
      }

      pos = line.find(delimiter);
      line.erase(0, pos + 1);

      auto value = atoi(line.c_str());
      values.push_back(value);
    }
  }

  file.close();

  int k = 0;
  for (size_t i = 0; i < n; i++) {
    (*array).push_back(vector<int>());

    for (size_t j = 0; j < m; j++) {
      auto value = values[k++];
      (*array)[i].push_back(value);
    }
  }
}

void write_array_to_file(matrix array, string filename, int duration = -1) {
  ofstream file(filename);

  file << array.size() << " " << array[0].size() << endl;
  for (size_t i = 0; i < array.size(); i++) {
    for (size_t j = 0; j < array[i].size(); j++) {
      file << "c" << (i + 1) << "_" << (j + 1) << " " << array[i][j] << endl;
    }
  }

  if (duration >= 0) {
    file << duration << endl;
  }

  file.close();
}
