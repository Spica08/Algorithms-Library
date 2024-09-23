#ifndef ERATOSTHENES_HPP
#define ERATOSTHENES_HPP

#include "../Utility/templete.hpp"

class Eratosthenes{
  public:
    Eratosthenes(int N) : n_(N), min_f_(N, inf){
      build();
    }

    bool IsPrime(int x){
      assert(x >= 0 && x < n_);
      return min_f_[x] == inf;
    }

    int min_factor(int x){
      assert(x >= 0 && x < n_);
      return min_f_[x];
    }
  private:
    int n_; // maxN
    std::vector<int> min_f_;
    std::vector<int> prime_;

    void build(){
      min_f_[0] = 1;
      min_f_[1] = 1;
      for (int i = 2; i < n_; i++) {
        for (int j = 2; i * j < n_; j++) {
          min_f_[i * j] = i;
        }
      }
    }
};

#endif //ERATOSTHENES_HPP