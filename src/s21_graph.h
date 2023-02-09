#ifndef SRC_S21_GRAPH_H
#define SRC_S21_GRAPH_H

#include <cmath>
#include <fstream>
#include <string>

#include "helpers/matrix.h"

namespace s21 {
class Graph {
 public:
  Graph();
  Graph(int size);
  ~Graph();
  void LoadGraphFromFile(const std::string &filename);
  void ExportGraphToDot(const std::string &filename);

  bool GetError() { return error_; }
  int GetSize() { return graph_.GetRows(); }
  Matrix<int> GetMatrix() { return graph_; }
  bool GraphIsEmpty_() { return graph_.IsMatrixEmpty(); }

  int &operator()(int row, int col);
  Matrix<int> &operator=(const Graph &) { return graph_; }

 private:
  int ParsingValue_(int pos, std::string line);
  Matrix<int> graph_;
  bool error_{false};
};
}  // namespace s21
#endif  // SRC_S21_GRAPH_H