#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_array(vector<int> array, int rows, int columns) {
	cout << rows << "x" << columns << endl;
	for (size_t i = 0; i < rows; i++) {
    cout << "[";
    for (size_t j = 0; j < columns; j++) {
      cout << array[i * columns + j];
			if(j != columns -1) cout << ", ";
    }
    cout << "]" << endl;
  }
}

void read_array_from_file(vector<int> *array, int *rows, int *columns, string filename) {
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
          *rows = atoi(substring.c_str());
          line.erase(0, pos + delimiter.length());
        }
        *columns = atoi(line.c_str());

        first_line = false;
        continue;
      }

      pos = line.find(delimiter);
      line.erase(0, pos + 1);

      auto value = atoi(line.c_str());
      (*array).push_back(value);
    }
  }

  file.close();
}

void write_array_to_file(vector<int> array, int rows, int columns,
                         string filename, int duration = -1) {
  ofstream file(filename);

  file << rows << " " << columns << endl;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      file << "c" << (i + 1) << "_" << (j + 1) << " " << array[i * columns + j] << endl;
    }
  }

  if (duration >= 0) {
    file << duration << endl;
  }

  file.close();
}
