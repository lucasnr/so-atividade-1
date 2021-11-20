#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
using matrix = vector<vector<int>>;
using time_point = chrono::steady_clock::time_point;

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

	int rows = array.size(), cols = array[0].size();

  file << rows << " " << cols << endl;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      file << "c" << (i + 1) << "_" << (j + 1) << " " << array[i][j] << endl;
    }
  }

  if (duration >= 0) {
    file << duration << endl;
  }

  file.close();
}

void write_array_piece_to_file(matrix array, int first_row, int first_col, int p, string filename, int duration = -1) {
  ofstream file(filename);

	int rows = array.size(), cols = array[0].size();
  file << rows << " " << cols << endl;

	int row = first_row;
	int col = first_col - 1;
	for (size_t j = 0; j < p; j++) {
		col = col + 1;

		if (col == cols) {
			col = 0;
			row = row + 1;
		}

		if (row == rows) break;

		file << "c" << (row + 1) << "_" << (col + 1) << " " << array[row][col] << endl;
	}

  if (duration >= 0) {
    file << duration << endl;
  }

  file.close();
}

void calculate_array_piece(matrix *array, int row, int col, matrix a, matrix b, int p, string filename_preffix, int index) {
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
	filename << filename_preffix << (index + 1) << ".txt";

  write_array_piece_to_file(*array, first_row, first_col, p, filename.str(), duration);
}
