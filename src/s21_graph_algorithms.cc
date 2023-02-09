//
// Created by Rebbecca Gormond on 11/16/22.
//

#include "s21_graph_algorithms.h"

namespace s21 {

bool s21_graph_algorithms::CheckData_(Graph &graph, int position) {
  return !(position < 1 || position > graph.GetSize() || graph.GraphIsEmpty_());
}

std::vector<int> s21_graph_algorithms::depthFirstSearch(Graph &graph,
                                                        int startVertex) {
  if (!CheckData_(graph, startVertex)) {
    std::vector<int> result = {-1};
    return result;
  }

  s21::Stack<int> stack;
  stack.push(startVertex);
  std::vector<int> result;

  while (!stack.empty()) {
    if (!std::count(result.begin(), result.end(), stack.top()))
      result.push_back(stack.top());

    int index = stack.top();
    stack.pop();

    for (int i = 0; i < graph.GetSize(); i++)
      if (graph(index - 1, i) != 0 &&
          !std::count(result.begin(), result.end(), i + 1))
        stack.push(i + 1);
  }

  return result;
}

std::vector<int> s21_graph_algorithms::breadthFirstSearch(Graph &graph,
                                                          int startVertex) {
  if (!CheckData_(graph, startVertex)) {
    std::vector<int> result = {-1};
    return result;
  }

  s21::Queue<int> queue;
  queue.push(startVertex);
  std::vector<int> result;

  while (!queue.empty()) {
    if (!std::count(result.begin(), result.end(), queue.front()))
      result.push_back(queue.front());

    int index = queue.front();
    queue.pop();

    for (int i = 0; i < graph.GetSize(); i++)
      if (graph(index - 1, i) != 0 &&
          !std::count(result.begin(), result.end(), i + 1))
        queue.push(i + 1);
  }

  return result;
}

int s21_graph_algorithms::getShortestPathBetweenVertices(Graph &graph,
                                                         int vertex1,
                                                         int vertex2) {
  if (!CheckData_(graph, vertex1) || !CheckData_(graph, vertex2)) {
    return -1;
  }

  s21::Queue<int> queue;
  queue.push(vertex1);

  std::vector<int> vertex_weight(graph.GetSize(), INT_MAX);
  vertex_weight[queue.front() - 1] = 0;

  while (!queue.empty()) {
    int index = queue.front();
    queue.pop();

    for (int i = 0; i < graph.GetSize(); i++)
      if (graph(index - 1, i) != 0 &&
          vertex_weight[i] > vertex_weight[index - 1] + graph(index - 1, i)) {
        vertex_weight[i] = vertex_weight[index - 1] + graph(index - 1, i);
        queue.push(i + 1);
      }
  }

  return vertex_weight[vertex2 - 1];
}

Matrix<int> s21_graph_algorithms::getShortestPathsBetweenAllVertices(
    Graph &graph) {
  Matrix<int> result(graph.GetSize(), graph.GetSize());
  for (int i = 0; i < graph.GetSize(); i++)
    for (int j = 0; j < graph.GetSize(); j++)
      result(i, j) = getShortestPathBetweenVertices(graph, i + 1, j + 1);

  return result;
}

Matrix<int> s21_graph_algorithms::getLeastSpanningTree(Graph &graph) {
  int size = graph.GetSize();
  if (size < 2) {
    return {1};
  }

  Matrix<int> result_matrix(size, size),
      tmp_matrix = reinterpret_cast<const Matrix<int> &>(graph);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (tmp_matrix(i, j) == 0) tmp_matrix(i, j) = INT_MAX;
      result_matrix(i, j) = 0;
    }
  }

  std::vector<bool> visited(size);
  visited[0] = true;
  for (int h = 1; h < size; ++h) {
    int min_weight = INT_MAX;
    std::pair<int, int> adding_edge;
    for (int i = 0; i < size; ++i) {
      if (visited[i])
        for (int j = 0; j < size; ++j) {
          if (!visited[j] && !result_matrix(i, j) &&
              tmp_matrix(i, j) < min_weight) {
            min_weight = tmp_matrix(i, j);
            adding_edge.first = i;
            adding_edge.second = j;
          }
        }
    }
    visited[adding_edge.second] = true;
    result_matrix(adding_edge.first, adding_edge.second) = min_weight;
    result_matrix(adding_edge.second, adding_edge.first) = min_weight;
  }
  return result_matrix;
}

TsmResult s21_graph_algorithms::solveTravelingSalesmanProblem(Graph &graph) {
  TsmAntAlgorithm solver(graph.GetMatrix());
  return solver.GetTsmResult();
}

TsmResult s21_graph_algorithms::solveTsmBruteForce(Graph &graph) {
  TsmBruteForce solver(graph.GetMatrix());
  return solver.GetTsmResult();
}

TsmResult s21_graph_algorithms::solveTsmBranchAndBound(Graph &graph) {
  TsmBranchAndBound solver(graph.GetMatrix());
  return solver.GetTsmResult();
}
}  // namespace s21
