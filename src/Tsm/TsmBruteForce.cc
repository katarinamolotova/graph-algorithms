//
// Created by k.molotova on 12/26/22.
//

#include "TsmBruteForce.h"

using namespace s21;

TsmBruteForce::TsmBruteForce(const Matrix<int> &graph) : TsmAbstract(graph) {
  name_ = "Brute force algorithm";
  for (int i = 0; i < size_; i++) vertices_.push_back(i);
}

void TsmBruteForce::AlgorithmExecution_() {
  do {
    int curr_cost = GetCostPath_(vertices_);
    if (curr_cost < result_.distance) {
      result_.distance = curr_cost;
      result_.vertices = GetRightVertices_(vertices_);
    }
  } while (std::next_permutation(vertices_.begin(), vertices_.end()));
}
