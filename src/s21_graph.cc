#include "s21_graph.h"

namespace s21 {

Graph::Graph() {}

Graph::Graph(int size) { graph_.ResizeMatrix(size, size); }

Graph::~Graph() {}

void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (graph_.GetRows() != 0) graph_.DeleteMatrix();
  if (file.is_open()) {
    error_ = false;
    std::string line;
    int size;
    file >> size;
    graph_ = Matrix<int>(size);
    int row = 0;
    while (getline(file, line) && row < graph_.GetRows() && !error_) {
      if (line.length() > 1) {
        int pos = 0;
        for (int col = 0; col < graph_.GetCols(); ++col) {
          if (line[pos] == ' ' || line[pos] == ',') {
            pos++;
            col--;
          } else {
            int num = ParsingValue_(pos, line);
            graph_(row, col) = num;
            pos += (std::to_string(num).length() + 1);
          }
        }
        row++;
      }
    }
    file.close();
  } else {
    error_ = true;
  }
}

int Graph::ParsingValue_(int pos, std::string line) {
  int result = 0;
  try {
    result =
        (pos >= (int)line.length()) ? 0 : std::stoi(&line[pos], nullptr, 10);
  } catch (std::invalid_argument& e) {
    result = 0;
    error_ = true;
  }
  return result;
}

void Graph::ExportGraphToDot(const std::string& filename) {
  std::ofstream file(filename);
  if (file.is_open() && graph_.GetCols() != 0) {
    file << "graph " << filename << " {" << std::endl;

    for (int i = 1; i <= graph_.GetCols(); i++)
      file << std::to_string(i) << ";" << std::endl;

    for (int i = 0; i < graph_.GetCols(); i++) {
      for (int j = i; j < graph_.GetCols(); j++) {
        if (graph_(i, j) != 0 || graph_(j, i) != 0) {
          if (graph_(i, j) == graph_(j, i)) {
            file << std::to_string(i + 1) << " -- " << std::to_string(j + 1)
                 << ";" << std::endl;
          } else {
            file << std::to_string(std::min(i, j) + 1) << " -> "
                 << std::to_string(std::max(i, j) + 1) << ";" << std::endl;
          }
        }
      }
    }
    file << "}";
  } else {
    error_ = true;
  }
}

int& Graph::operator()(int row, int col) {
  if (row >= graph_.GetRows() || col >= graph_.GetCols() || row < 0 || col < 0)
    error_ = true;
  return graph_(row, col);
}

}  // namespace s21
