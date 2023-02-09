//
// Created by Rebbecca Gormond on 11/16/22.
//

#ifndef SRC_S21_GRAPH_ALGORITHMS_H
#define SRC_S21_GRAPH_ALGORITHMS_H

#include <algorithm>
#include <climits>
#include <vector>

#include "Tsm/TsmAbstract.h"
#include "Tsm/TsmAntAlgorithm.h"
#include "Tsm/TsmBranchAndBound.h"
#include "Tsm/TsmBruteForce.h"
#include "helpers/matrix.h"
#include "helpers/s21_queue.h"
#include "helpers/s21_stack.h"
#include "s21_graph.h"

namespace s21 {
class s21_graph_algorithms {
 private:
  static bool CheckData_(Graph &graph, int position);

 public:
  static std::vector<int> depthFirstSearch(Graph &graph, int startVertex);
  static std::vector<int> breadthFirstSearch(Graph &graph, int startVertex);
  static int getShortestPathBetweenVertices(Graph &graph, int vertex1,
                                            int vertex2);
  static Matrix<int> getShortestPathsBetweenAllVertices(Graph &graph);
  static Matrix<int> getLeastSpanningTree(Graph &graph);
  static TsmResult solveTravelingSalesmanProblem(Graph &graph);
  static TsmResult solveTsmBruteForce(Graph &graph);
  static TsmResult solveTsmBranchAndBound(Graph &graph);
};
}  // namespace s21

#endif  // SRC_S21_GRAPH_ALGORITHMS_H
