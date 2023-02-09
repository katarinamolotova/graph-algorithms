//
// Created by k.molotova on 12/26/22.
//

#include "TsmAntAlgorithm.h"

using namespace s21;

TsmAntAlgorithm::TsmAntAlgorithm(const s21::Matrix<int>& graph)
    : TsmAbstract(graph) {
  name_ = "Ant algorithm";
  pheromones_ = pheromones_delta_ = Matrix<double>(size_);
}

void TsmAntAlgorithm::AlgorithmExecution_() {
  SetStartingValueForPheromones_();
  for (int i = 0; i < 50; i++) {
    if (i > 0) UpdatePheromones_();
    for (auto ant = 0; ant < size_; ant++) {
      int position = 0;
      vector<int> visited;
      map<int, double> available_v_and_probability = GetAvailableVertices_();
      while (!available_v_and_probability.empty()) {
        visited.push_back(position);
        available_v_and_probability.erase(position);
        TransitionProbabilityCalculation_(available_v_and_probability,
                                          position);
        position = GetNextPosition_(available_v_and_probability);
      }
      IncreaseDelta_(visited);
      if (result_.distance > GetCostPath_(visited)) {
        result_.distance = GetCostPath_(visited);
        result_.vertices = GetRightVertices_(visited);
      }
    }
  }
}

void TsmAntAlgorithm::SetStartingValueForPheromones_() {
  for (auto i = 0; i < size_; i++)
    for (auto j = 0; j < size_; j++)
      if (graph_(i, j) != 0) pheromones_(i, j) = 0.2;
}

map<int, double> TsmAntAlgorithm::GetAvailableVertices_() {
  map<int, double> result;
  for (auto i = 0; i < size_; i++) result.insert({i, 0});
  return result;
}

void TsmAntAlgorithm::TransitionProbabilityCalculation_(
    map<int, double>& probability, int position) {
  double sum = 0;
  for (std::pair<int, double> i : probability) {
    sum += pheromones_(position, i.first) * graph_(position, i.first);
  }
  for (std::pair<int, double> i : probability) {
    probability[i.first] =
        pheromones_(position, i.first) * graph_(position, i.first) / sum;
  }
}

int TsmAntAlgorithm::GetNextPosition_(map<int, double>& probability) {
  double point = rand() % 100 / 100.0, sum = 0;
  int position = -1;
  for (std::pair<int, double> i : probability) {
    sum += i.second;
    if (point <= sum) {
      position = i.first;
      break;
    }
  }
  return position;
}

void TsmAntAlgorithm::IncreaseDelta_(const vector<int>& visited) {
  const double q = 10.0;
  int prev_point = visited[0], sum = GetCostPath_(visited);
  for (unsigned long i = 1; i < visited.size(); i++) {
    pheromones_delta_(prev_point, visited[i]) += q / (double)sum;
  }
}

void TsmAntAlgorithm::UpdatePheromones_() {
  for (auto row = 0; row < size_; row++) {
    for (auto col = 0; col < size_; col++) {
      pheromones_(row, col) =
          pheromones_(row, col) * 0.64 + pheromones_delta_(row, col);
    }
  }
  pheromones_delta_.FillMatrix(0.0);
}