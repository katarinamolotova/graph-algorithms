//
// Created by Rebbecca Gormond on 12/20/22.
//

#include "Interface.h"

s21::Interface::Interface() { graph_ = Graph(); }

void s21::Interface::Start() {
  Message_(MAIN_MENU);
  int menu_options = INT_MAX;

  while (menu_options) {
    if (!InputOptions_(menu_options) || menu_options == CLOSE_APP) {
    } else if (menu_options != LOAD_GRAPH && !graph_.GetSize()) {
      Message_(BROKEN_GRAPH);
    } else if (menu_options == LOAD_GRAPH && ReadGraphFromFile_(graph_)) {
    } else if (menu_options == WRITE_GRAPH && WriteGraphToFile_(graph_)) {
    } else if (menu_options == DFS_OPTION && FirstSearch_(graph_, true)) {
    } else if (menu_options == BFS_OPTION && FirstSearch_(graph_, false)) {
    } else if (menu_options == SPB_TWO_V &&
               GetShortestPathBetweenVertices_(graph_)) {
    } else if (menu_options == SPB_ALL_V &&
               GetShortestPathsBetweenAllVertices_(graph_)) {
    } else if (menu_options == FLS_TREE && GetLeastSpanningTree_(graph_)) {
    } else if (menu_options == SOLVE_TSM && GetSolveTsm_(graph_)) {
    } else if (menu_options == DIFF_TSM_ALGO &&
               ShowDiffBetweenTsmAlgorithm_(graph_)) {
    } else {
      Message_(ERROR_MESSAGE);
    }
  }
  Message_(FINAL_PHRASE);
}

bool s21::Interface::WriteGraphToFile_(Graph &graph_) {
  Message_(ADDRESS);
  std::string address;
  std::cin >> address;
  graph_.ExportGraphToDot(address);
  if (!graph_.GetError()) Message_(SUCCESS);
  return !graph_.GetError();
}

bool s21::Interface::ReadGraphFromFile_(Graph &graph_) {
  Message_(ADDRESS);
  std::string address;
  std::cin >> address;
  graph_.LoadGraphFromFile(address);
  if (!graph_.GetError()) Message_(SUCCESS);
  return !graph_.GetError();
}

bool s21::Interface::InputOptions_(int &options, int min, int max) {
  bool status = false;
  std::string input_sample;
  std::cin >> input_sample;
  if (!input_sample.empty() && ThisStringIsDigit(input_sample)) {
    options = std::stoi(input_sample);
    if (options >= min && options <= max) {
      status = true;
    }
  }
  if (!status) {
    Message_(ERROR_MESSAGE);
  }
  return status;
}

void s21::Interface::PrintResulVector_(std::vector<int> &result) {
  Message_(ANSWER);
  for (auto it : result) {
    if (it != INT_MAX) {
      std::cout << it << " ";
    } else {
      std::cout << "INF ";
    }
  }
  Message_(CHOSE_NEXT_OPTIONS);
}

void s21::Interface::PrintResulMatrix_(s21::Matrix<int> &result) {
  Message_(ANSWER);
  for (auto i = 0; i < result.GetRows(); i++) {
    for (auto j = 0; j < result.GetCols(); j++) {
      std::cout << " ";
      if (result(i, j) != INT_MAX) {
        std::cout << result(i, j);
      } else {
        std::cout << "INF";
      }
    }
    std::cout << std::endl;
  }
  Message_(CHOSE_NEXT_OPTIONS);
}

void s21::Interface::PrintResulInt_(int &result) {
  Message_(ANSWER);
  Message_((result == INT_MAX) ? "INF" : std::to_string(result));
  Message_(CHOSE_NEXT_OPTIONS);
}

void s21::Interface::Message_(const std::string &message) {
  std::cout << message;
  if (message == CHOSE_NEXT_OPTIONS) {
    Message_(MAIN_MENU);
  }
}

bool s21::Interface::FirstSearch_(Graph &graph_, bool options) {
  int start_vertice = INT_MAX;
  bool status = false;

  while (!status) {
    Message_(START_VER);
    status = InputOptions_(start_vertice, 1, graph_.GetSize());
  }

  status = false;
  if (CheckGraph_(graph_)) {
    std::vector<int> result;
    if (options)
      result =
          s21::s21_graph_algorithms::depthFirstSearch(graph_, start_vertice);
    else
      result = s21_graph_algorithms::breadthFirstSearch(graph_, start_vertice);
    PrintResulVector_(result);
    status = true;
  }
  return status;
}

bool s21::Interface::GetShortestPathBetweenVertices_(Graph &graph_) {
  int start_vertice = INT_MAX, finish_vertice = graph_.GetSize();
  std::pair<bool, bool> status = {false, false};

  while (!(status.first && status.second)) {
    Message_(START_VER);
    status.first = InputOptions_(start_vertice, 1, graph_.GetSize());
    Message_(FINISH_VER);
    status.second = InputOptions_(finish_vertice, 1, graph_.GetSize());
  }

  status.first = false;
  if (CheckGraph_(graph_)) {
    int result = s21_graph_algorithms::getShortestPathBetweenVertices(
        graph_, start_vertice, finish_vertice);
    PrintResulInt_(result);
    status.first = true;
  }
  return status.first;
}

bool s21::Interface::GetShortestPathsBetweenAllVertices_(Graph &graph_) {
  bool status = CheckGraph_(graph_);
  Matrix<int> result =
      s21_graph_algorithms::getShortestPathsBetweenAllVertices(graph_);
  PrintResulMatrix_(result);
  return status;
}

bool s21::Interface::GetLeastSpanningTree_(Graph &graph_) {
  bool status = CheckGraph_(graph_);
  Matrix<int> result = s21_graph_algorithms::getLeastSpanningTree(graph_);
  PrintResulMatrix_(result);
  return status;
}

bool s21::Interface::CheckGraph_(Graph &graph_) {
  bool status = (graph_.GetSize() > 0);
  if (!status) {
    Message_(BROKEN_GRAPH);
  }
  return status;
}

bool s21::Interface::ThisStringIsDigit(const std::string &example) {
  bool status = true;
  for (char i : example)
    if (!isdigit(i)) {
      status = false;
      break;
    }
  return status;
}

bool s21::Interface::GetSolveTsm_(s21::Graph &graph_) {
  TsmResult res = s21_graph_algorithms::solveTravelingSalesmanProblem(graph_);
  bool status = true;
  if (res.distance == INT_MAX) {
    Message_("Graph direct or incomplete\n");
    status = false;
  } else {
    Message_(ANSWER);
    std::cout << "Path: ";
    for (int i : res.vertices) std::cout << i << " ";
    std::cout << std::endl << "Path cost: " << res.distance << std::endl;
    Message_(CHOSE_NEXT_OPTIONS);
  }
  return status;
}

bool s21::Interface::ShowDiffBetweenTsmAlgorithm_(Graph &graph_) {
  int amount = 0;
  Message_("Enter the number of repetitions: ");
  std::cin >> amount;

  s21::TsmAbstract *algorithms[3];
  algorithms[0] = new s21::TsmAntAlgorithm(graph_.GetMatrix());
  algorithms[1] = new s21::TsmBranchAndBound(graph_.GetMatrix());
  algorithms[2] = new s21::TsmBruteForce(graph_.GetMatrix());

  bool status = (algorithms[0]->CheckGraph() == s21::GraphError::GRAPH_NORMAL);

  if (status) {
    Message_("Time execution:\n");
    for (auto &algorithm : algorithms) {
      std::cout << algorithm->GetName() << ": ";
      std::cout << GetTimeExecutionTsmAlgorithm_(algorithm, amount) << " ms.\n";
    }
    Message_(CHOSE_NEXT_OPTIONS);
  }

  for (auto &algorithm : algorithms) delete algorithm;
  return status;
}

unsigned s21::Interface::GetTimeExecutionTsmAlgorithm_(s21::TsmAbstract *solver,
                                                       int amount) {
  unsigned start_time = clock();
  for (int i = 0; i < amount; i++) solver->GetTsmResult();
  unsigned end_time = clock();
  return (end_time - start_time);
}
