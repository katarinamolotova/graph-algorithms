#ifndef SRC_INTERFACE_INTERFACE_H
#define SRC_INTERFACE_INTERFACE_H

#include <iostream>

#include "../Tsm/TsmAbstract.h"
#include "../s21_graph_algorithms.h"

#define ERROR_MESSAGE "Something wrong, try again\n"
#define START_VER "Set start vertice \n"
#define FINISH_VER "Set finish vertice \n"
#define FINAL_PHRASE "See you late\n"
#define SUCCESS "Success\n"
#define ANSWER "Answer for you\n"
#define ADDRESS "Address to file\n"
#define CHOSE_NEXT_OPTIONS "\nChose another options\n"
#define BROKEN_GRAPH "Error your Graph is broken\n"
#define MAIN_MENU                                                            \
  "This application can: \n"                                                 \
  " 1. Load graph from a file. \n"                                           \
  " 2. Save graph to the file. \n"                                           \
  " 3. Traversal of a graph in depth. \n"                                    \
  " 4. Traversal of a graph in breadth. \n"                                  \
  " 5. Get shortest path between two vertices. \n"                           \
  " 6. Get shortest path between all vertices. \n"                           \
  " 7. Get least spanning tree. \n"                                          \
  " 8. Solve traveling salesman problem. \n"                                 \
  " 9. Comparison of methods for solving the traveling salesman problem. \n" \
  " 0. Exit from application. \n"

namespace s21 {
class Interface {
 public:
  Interface();
  void Start();

 private:
  Graph graph_;

  static bool InputOptions_(int &options, int min = 0, int max = 9);
  static bool ReadGraphFromFile_(Graph &graph_);
  static bool WriteGraphToFile_(Graph &graph_);

  static bool FirstSearch_(Graph &graph_, bool options);
  static bool GetShortestPathBetweenVertices_(Graph &graph_);
  static bool GetShortestPathsBetweenAllVertices_(Graph &graph_);
  static bool GetLeastSpanningTree_(Graph &graph_);
  static bool GetSolveTsm_(Graph &graph_);
  static bool ShowDiffBetweenTsmAlgorithm_(Graph &graph_);

  static bool CheckGraph_(Graph &graph_);
  static void PrintResulVector_(std::vector<int> &result);
  static void PrintResulMatrix_(Matrix<int> &result);
  static void PrintResulInt_(int &result);
  static void Message_(const std::string &message);
  static bool ThisStringIsDigit(const std::string &example);
  static unsigned GetTimeExecutionTsmAlgorithm_(TsmAbstract *solver,
                                                int amount);

  enum Options_in_menu {
    CLOSE_APP = 0,
    LOAD_GRAPH = 1,
    WRITE_GRAPH = 2,
    DFS_OPTION = 3,
    BFS_OPTION = 4,
    SPB_TWO_V = 5,
    SPB_ALL_V = 6,
    FLS_TREE = 7,
    SOLVE_TSM = 8,
    DIFF_TSM_ALGO = 9
  };
};
}  // namespace s21

#endif  // SRC_INTERFACE_INTERFACE_H
