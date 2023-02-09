//
// Created by k.molotova on 12/26/22.
//

#ifndef SRC_TSM_TSMANTALGORITHM_H
#define SRC_TSM_TSMANTALGORITHM_H

#include "TsmAbstract.h"

namespace s21 {

class TsmAntAlgorithm : public TsmAbstract {
 public:
  explicit TsmAntAlgorithm(const s21::Matrix<int>& graph);
  ~TsmAntAlgorithm() = default;

 private:
  Matrix<double> pheromones_;
  Matrix<double> pheromones_delta_;

  void AlgorithmExecution_() override;

  void SetStartingValueForPheromones_();
  void TransitionProbabilityCalculation_(map<int, double>& probability,
                                         int position);
  int GetNextPosition_(map<int, double>& probability);
  void IncreaseDelta_(const vector<int>& visited);
  void UpdatePheromones_();
  map<int, double> GetAvailableVertices_();
};

}  // namespace s21

#endif  // SRC_TSM_TSMANTALGORITHM_H
