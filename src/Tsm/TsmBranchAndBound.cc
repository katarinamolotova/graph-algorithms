//
// Created by k.molotova on 12/26/22.
//

#include "TsmBranchAndBound.h"

using namespace s21;

TsmBranchAndBound::TsmBranchAndBound(const Matrix<int> &graph)
    : TsmAbstract(graph) {
  name_ = "Branch and bound algorithm";
  visited_ = vector<bool>(size_, false);
  result_.distance = INT_MAX;
}

void TsmBranchAndBound::AlgorithmExecution_() {
  visited_[0] = true;
  vector<int> path = vector<int>(size_, 0);
  RecursivePart_(GetStartingLowerBound_(), 0, 1, path);
}

int TsmBranchAndBound::GetStartingLowerBound_() {
  int bound = 0;
  for (int i = 0; i < size_; i++)
    bound += GetFirstMinValueInRow_(i) + GetSecondMinValueInRow_(i);
  bound = round(bound / 2.0);
  return bound;
}

void TsmBranchAndBound::RecursivePart_(int bound, int cost, int level,
                                       vector<int> path) {
  if (level == size_) {
    CheckResult_(level, cost, path);
  } else {
    for (int i = 0; i < size_; i++) {
      if (graph_(path[level - 1], i) != 0 && !visited_[i]) {
        int temp_bound = bound;
        cost += graph_(path[level - 1], i);
        UpdateLowerBound_(bound, level, path, i);

        if (bound + cost < result_.distance) {
          path[level] = i;
          visited_[i] = true;
          RecursivePart_(bound, cost, level + 1, path);
        }

        cost -= graph_(path[level - 1], i);
        bound = temp_bound;
        ResetVisited_(level, path);
      }
    }
  }
}

void TsmBranchAndBound::UpdateLowerBound_(int &bound, int level,
                                          vector<int> path, int i) {
  int first_value = (level == 1) ? GetFirstMinValueInRow_(path[level - 1])
                                 : GetSecondMinValueInRow_(path[level - 1]);
  bound -= (first_value + GetFirstMinValueInRow_(i)) / 2;
}

void TsmBranchAndBound::ResetVisited_(int level, vector<int> path) {
  visited_ = vector<bool>(size_, false);
  for (int j = 0; j < level; j++) visited_[path[j]] = true;
}

void TsmBranchAndBound::CheckResult_(int level, int cost, vector<int> path) {
  if (graph_(path[level - 1], path[0]) != 0) {
    int temp_cost = graph_(path[level - 1], path[0]) + cost;
    if (temp_cost < result_.distance) {
      result_.distance = temp_cost;
      result_.vertices = GetRightVertices_(path);
    }
  }
}

int TsmBranchAndBound::GetFirstMinValueInRow_(int row) {
  int min = INT_MAX;
  for (int col = 0; col < graph_.GetCols(); col++)
    if (graph_(row, col) < min && row != col) min = graph_(row, col);
  return min;
}

int TsmBranchAndBound::GetSecondMinValueInRow_(int row) {
  int first_min = INT_MAX, second_min = INT_MAX;
  for (int col = 0; col < graph_.GetCols(); col++) {
    if (row == col) continue;
    if (graph_(row, col) <= first_min) {
      first_min = graph_(row, col);
      second_min = first_min;
    } else if (graph_(row, col) < second_min && graph_(row, col) != first_min) {
      second_min = graph_(row, col);
    }
  }
  return second_min;
}
