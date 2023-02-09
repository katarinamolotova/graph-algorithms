//
// Created by k.molotova on 12/26/22.
//

#ifndef SRC_TSM_TSMBRUTEFORCE_H
#define SRC_TSM_TSMBRUTEFORCE_H

#include <algorithm>

#include "TsmAbstract.h"

namespace s21 {

class TsmBruteForce : public TsmAbstract {
 public:
  explicit TsmBruteForce(const Matrix<int>& graph);
  ~TsmBruteForce() = default;

 private:
  vector<int> vertices_;
  void AlgorithmExecution_() override;
};

}  // namespace s21

#endif  // SRC_TSM_TSMBRUTEFORCE_H
