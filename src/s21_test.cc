#include <gtest/gtest.h>

#include "Tsm/TsmAbstract.h"
#include "s21_graph_algorithms.h"

TEST(PartOneTests, DFS1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/DFS1.txt");
  std::vector<int> result =
      s21::s21_graph_algorithms::depthFirstSearch(graph, 1);
  int expected_values[] = {1, 4, 3, 5, 2};

  for (int i = 0; i < 5; i++) EXPECT_EQ(result[i], expected_values[i]);
}

TEST(PartOneTests, DFS2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/DFS2.txt");
  std::vector<int> result =
      s21::s21_graph_algorithms::depthFirstSearch(graph, 3);
  int expected_values2[] = {3, 4, 1, 2};

  for (int i = 0; i < 4; i++) EXPECT_EQ(result[i], expected_values2[i]);
}

TEST(PartOneTests, DFS3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/TreeGraph.txt");
  std::vector<int> result =
      s21::s21_graph_algorithms::depthFirstSearch(graph, 1);
  int expected_values3[] = {1, 4, 8, 7, 12, 11, 3, 2, 6, 5, 10, 9};

  for (int i = 0; i < 12; i++) EXPECT_EQ(result[i], expected_values3[i]);
}

TEST(PartOneTests, DFSWrongVertex) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/DFS1.txt");
  std::vector<int> result =
      s21::s21_graph_algorithms::depthFirstSearch(graph, 999);
  EXPECT_EQ(result.at(0), -1);
}

TEST(PartOneTests, DFSEmptyGraph) {
  s21::Graph empty_graph;
  std::vector<int> result =
      s21::s21_graph_algorithms::depthFirstSearch(empty_graph, 2);
  EXPECT_EQ(result.at(0), -1);
}

TEST(PartOneTests, BFS) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/TreeGraph.txt");
  std::vector<int> result =
      s21::s21_graph_algorithms::breadthFirstSearch(graph, 1);
  int expected_values3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  for (int i = 0; i < 12; i++) EXPECT_EQ(result[i], expected_values3[i]);
}

TEST(PartOneTests, exportGraphToDot) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/example.txt");
  graph.ExportGraphToDot("../datasets/aboba.dot");
  std::ifstream file("../datasets/aboba.dot");
  char c;
  if (!file.is_open() || !(file >> c)) {
    file.close();
    FAIL();
  }
  file.close();
}

TEST(PartTwoTests, GetShortestPathBetweenVertices) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/example.txt");
  EXPECT_EQ(
      s21::s21_graph_algorithms::getShortestPathBetweenVertices(graph, 1, 4),
      20);
  EXPECT_EQ(
      s21::s21_graph_algorithms::getShortestPathBetweenVertices(graph, 3, 8),
      9);
  EXPECT_EQ(
      s21::s21_graph_algorithms::getShortestPathBetweenVertices(graph, 11, 2),
      12);
  EXPECT_EQ(
      s21::s21_graph_algorithms::getShortestPathBetweenVertices(graph, 4, 10),
      13);
  EXPECT_EQ(
      s21::s21_graph_algorithms::getShortestPathBetweenVertices(graph, 13, 14),
      -1);
}

TEST(PartTwoTests, GetShortestPathsBetweenAllVertices1) {
  s21::Graph graph, graph2, graph3;
  graph.LoadGraphFromFile("../datasets/example2.txt");
  s21::Matrix<int> tmp_matrix =
      s21::s21_graph_algorithms::getShortestPathsBetweenAllVertices(graph);
  s21::Matrix<int> pattern_1 = {0, 1, 1, 1, 1, 0, 1, 2, 1, 1, 0, 2, 1, 2, 2, 0};

  for (int i = 0; i < tmp_matrix.GetRows(); i++) {
    for (int j = 0; j < tmp_matrix.GetCols(); j++) {
      EXPECT_EQ(tmp_matrix(i, j), pattern_1(i, j));
    }
  }
}

TEST(PartTwoTests, GetShortestPathsBetweenAllVertices2) {
  s21::Graph graph2;
  graph2.LoadGraphFromFile("../datasets/example3.txt");
  s21::Matrix<int> tmp_matrix =
      s21::s21_graph_algorithms::getShortestPathsBetweenAllVertices(graph2);
  s21::Matrix<int> pattern_2 = {0, 1, 2, 2, 1, 0, 1, 1, 2, 1, 0, 2, 2, 1, 2, 0};

  for (int i = 0; i < tmp_matrix.GetRows(); i++) {
    for (int j = 0; j < tmp_matrix.GetCols(); j++) {
      EXPECT_EQ(tmp_matrix(i, j), pattern_2(i, j));
    }
  }
}

TEST(PartTwoTests, GetShortestPathsBetweenAllVertices3) {
  s21::Graph graph3;
  graph3.LoadGraphFromFile("../datasets/example1.txt");
  s21::Matrix<int> tmp_matrix =
      s21::s21_graph_algorithms::getShortestPathsBetweenAllVertices(graph3);
  s21::Matrix<int> pattern_3 = {
      0,  29, 20,  20, 16, 31, 100, 12, 4,  31, 18,  29, 0,  15, 29,  28,
      40, 72, 21,  29, 41, 12, 20,  15, 0,  15, 14,  25, 81, 9,  23,  27,
      13, 20, 29,  15, 0,  4,  12,  92, 12, 24, 13,  25, 16, 28, 14,  4,
      0,  16, 94,  9,  20, 16, 22,  31, 40, 25, 12,  16, 0,  95, 24,  35,
      3,  37, 100, 72, 81, 92, 94,  95, 0,  90, 101, 98, 84, 12, 21,  9,
      12, 9,  24,  90, 0,  15, 25,  13, 4,  29, 23,  24, 20, 35, 101, 15,
      0,  35, 18,  31, 41, 27, 13,  16, 3,  98, 25,  35, 0,  38, 18,  12,
      13, 25, 22,  37, 84, 13, 18,  38, 0};

  for (int i = 0; i < tmp_matrix.GetRows(); i++) {
    for (int j = 0; j < tmp_matrix.GetCols(); j++) {
      EXPECT_EQ(tmp_matrix(i, j), pattern_3(i, j));
    }
  }
}

TEST(PartThreeTests, GetLeastSpanningTree1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/example4.txt");

  s21::Matrix<int> pattern_1 = {INT_MAX, 0, 0, 0, 0, 0, 0, 0,
                                0,       0, 0, 0, 0, 0, 0, 0};
  s21::Matrix<int> tmp_matrix(
      s21::s21_graph_algorithms::getLeastSpanningTree(graph));

  for (int i = 0; i < tmp_matrix.GetRows(); i++) {
    for (int j = 0; j < tmp_matrix.GetCols(); j++) {
      EXPECT_EQ(tmp_matrix(i, j), pattern_1(i, j));
    }
  }
}

TEST(PartThreeTests, GetLeastSpanningTree2) {
  s21::Graph graph2;
  s21::Matrix<int> pattern_2 = {0, 0, 1, 0, 0, 0, 0, 0, 5, 0, 3, 0,
                                1, 5, 0, 0, 0, 4, 0, 0, 0, 0, 0, 2,
                                0, 3, 0, 0, 0, 0, 0, 0, 4, 2, 0, 0};
  s21::Matrix<int> tmp_matrix(
      s21::s21_graph_algorithms::getLeastSpanningTree(graph2));

  graph2.LoadGraphFromFile("../datasets/example5.txt");
  tmp_matrix = s21::s21_graph_algorithms::getLeastSpanningTree(graph2);

  for (int i = 0; i < tmp_matrix.GetRows(); i++) {
    for (int j = 0; j < tmp_matrix.GetCols(); j++) {
      EXPECT_EQ(tmp_matrix(i, j), pattern_2(i, j));
    }
  }
}

TEST(TSMTest, AntAlgorithms4x4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/TSM4x4.txt");
  s21::TsmAntAlgorithm solver(graph.GetMatrix());
  s21::TsmResult result = solver.GetTsmResult();
  int expected_vertices[] = {1, 3, 4, 2, 1};

  EXPECT_EQ(result.distance, 80);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(expected_vertices[i], result.vertices[i]);
  }
}

TEST(TSMTest, AntAlgorithmsError) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/TSM6x6.txt");
  s21::TsmAntAlgorithm solver(graph.GetMatrix());
  EXPECT_EQ(solver.CheckGraph(), s21::GraphError::GRAPH_DIRECT);
}

TEST(TSMTest, BruteForceAlgorithms4x4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/TSM4x4.txt");
  s21::TsmBruteForce solver(graph.GetMatrix());
  s21::TsmResult result = solver.GetTsmResult();
  int expected_vertices[] = {1, 2, 4, 3, 1};

  EXPECT_EQ(result.distance, 80);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(expected_vertices[i], result.vertices[i]);
  }
}

TEST(TSMTest, BranchAndBoundAlgorithms4x4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("../datasets/TSM4x4.txt");
  s21::TsmBranchAndBound solver(graph.GetMatrix());
  s21::TsmResult result = solver.GetTsmResult();
  int expected_vertices[] = {1, 2, 4, 3, 1};

  EXPECT_EQ(result.distance, 80);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(expected_vertices[i], result.vertices[i]);
  }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
