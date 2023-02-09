//
// Created by k.molotova on 12/26/22.
//

#ifndef SRC_TSM_TSMBRANCHANDBOUND_H
#define SRC_TSM_TSMBRANCHANDBOUND_H

#include <cmath>

#include "TsmAbstract.h"

namespace s21 {

class TsmBranchAndBound : public TsmAbstract {
 public:
  explicit TsmBranchAndBound(const Matrix<int>& graph);
  ~TsmBranchAndBound() = default;

 private:
  vector<bool> visited_;

  void AlgorithmExecution_() override;

  int GetStartingLowerBound_();
  void UpdateLowerBound_(int& bound, int level, vector<int> path, int i);
  void ResetVisited_(int level, vector<int> path);
  int GetFirstMinValueInRow_(int row);
  int GetSecondMinValueInRow_(int row);
  void RecursivePart_(int bound, int cost, int level, vector<int> path);
  void CheckResult_(int level, int cost, vector<int> path);
};

}  // namespace s21

#endif  // CLIONPROJECTS_TSMBRANCHANDBOUND_H
