#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include "../Utility/templete.hpp"

// int or long long
template <typename T>
class Compress{
  public:
    Compress(std::vector<T> A) : A_(A), reconstruct_(A.size()+10){
      std::vector<T> vals = A_;
      std::sort(vals.begin(), vals.end());
      vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
      for (int i = 0; i < A_.size(); i++) {
        T b = A_[i];
        A_[i] = lower_bound(vals.begin(), vals.end(), b) - vals.begin();
        reconstruct_[A_[i]] = b;
      }
    };

    const T& operator[](int i)const{return A_[i];};
    const T& rev(int i)const{return reconstruct_[i];};

  private:
    std::vector<T> A_;
    std::vector<T> reconstruct_;
};

#endif //COMPRESS_HPP