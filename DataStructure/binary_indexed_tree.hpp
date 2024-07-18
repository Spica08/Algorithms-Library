#ifndef BINARY_INDEXED_TREE_HPP
#define BINARY_INDEXED_TREE_HPP

#include "../Utility/templete.hpp"

template <typename T>
class BinaryIndexedTree {
  public:
    BinaryIndexedTree(int N, std::function<T()> e, std::function<T(T)> inv, std::function<T(T, T)> op) 
      : n_(N + 1), e_(e), inv_(inv), op_(op), dat_(N + 1, e()) {}
    void add(int i, T x) {
      for (int idx = i; idx < n_; idx += (idx & -idx)) dat_[idx] = op_(dat_[idx], x);
    }
    // sum of [l, r] (1-indexed)
    T sum(int l, int r) { return op_(sum_sub(r), inv_(sum_sub(l - 1))); }
    // get i-th value (1-indexed)
    T get(int i) {return sum(i, i);}
  private:
    int n_;
    std::vector<T> dat_;
    std::function<T()> e_;
    std::function<T(T)> inv_;
    std::function<T(T, T)> op_;

    T sum_sub(int i) {
      T res = e_();
      for (int idx = i; idx > 0; idx -= (idx & -idx)) res = op_(res, dat_[idx]);
      return res;
    }
};

#endif //BINARY_INDEXED_TREE_HPP