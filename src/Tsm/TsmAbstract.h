//
// Created by k.molotova on 12/26/22.
//

#ifndef SRC_TSM_TSMABSTRACT_HPP
#define SRC_TSM_TSMABSTRACT_HPP

#include <climits>
#include <map>
#include <vector>

#include "../helpers/matrix.h"

using std::map;
using std::vector;

namespace s21 {
enum GraphError { GRAPH_INCOMPLETE, GRAPH_DIRECT, GRAPH_SMALL, GRAPH_NORMAL };

struct TsmResult {
  std::vector<int> vertices;
  double distance;

  TsmResult() = default;

  TsmResult(std::vector<int> path, double distance) {
    this->distance = distance;
    vertices = path;
  }
};

class TsmAbstract {
 public:
  explicit TsmAbstract(const s21::Matrix<int>& graph) : graph_(graph) {
    result_ = TsmResult({}, INT_MAX);
    size_ = graph.GetRows();
  }

  virtual ~TsmAbstract() = default;

  virtual TsmResult GetTsmResult() {
    GraphError error = CheckGraph();
    if (error == GraphError::GRAPH_NORMAL) AlgorithmExecution_();
    return result_;
  }

  virtual GraphError CheckGraph() {
    if (graph_.GetRows() < 3) return GraphError::GRAPH_SMALL;
    for (auto row = 0; row < graph_.GetRows(); row++) {
      for (auto col = 0; col < graph_.GetCols(); col++) {
        if (row != col && graph_(row, col) == 0)
          return GraphError::GRAPH_INCOMPLETE;
        else if (graph_(row, col) != graph_(col, row))
          return GraphError::GRAPH_DIRECT;
      }
    }
    return GraphError::GRAPH_NORMAL;
  }

  virtual std::string GetName() { return name_; }

 protected:
  std::string name_;
  TsmResult result_;
  s21::Matrix<int> graph_;
  int size_;

  virtual void AlgorithmExecution_() = 0;

  virtual vector<int> GetRightVertices_(vector<int> vertices) {
    for (int& vertex : vertices) vertex++;
    vertices.push_back(vertices.front());
    return vertices;
  }

  virtual int GetCostPath_(const vector<int>& path) {
    int sum = 0, prev_point = path[0];
    for (size_t i = 1; i < path.size(); i++) {
      sum += graph_(prev_point, path[i]);
      prev_point = path[i];
    }
    sum += graph_(path.back(), path.front());
    return sum;
  }
};
}  // namespace s21

#endif  // SRC_TSM_TSMABSTRACT_HPP
