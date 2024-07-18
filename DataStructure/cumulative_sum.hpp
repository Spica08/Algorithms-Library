#ifndef CUMULATIVE_SUM_HPP
#define CUMULATIVE_SUM_HPP

#include "../Utility/templete.hpp"

// int or long long
template <typename T>
class CumulativeSum {
  public:
    CumulativeSum(std::vector<T> &A) {
      int N = A.size();
      S_.assign(N + 1, 0);
      for (int i = 0; i < N; i++) S_[i + 1] = S_[i] + A[i];
    }
    //sum of [l, r) (0-indexed)
    T sum(int l, int r) { return S_[r] - S_[l]; }
  private:
    std::vector<T> S_;
};

#endif //CUMULATIVE_SUM_HPP