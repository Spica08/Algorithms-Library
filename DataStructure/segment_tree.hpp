#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include "../Utility/templete.hpp"

template <typename T>
class SegmentTree {
  public:
    SegmentTree(int N, std::function<T()> e, std::function<T(T, T)> op, std::function<T(T, T)> update)
        : e_(e), op_(op), update_(update) {
      n_ = 1;
      while (N > n_) n_ *= 2;
      dat_.assign(2 * n_ - 1, e_());
    }
    // update i-th value
    void change(int i, T x) {
      i += n_ - 1;
      dat_[i] = update_(dat_[i], x);
      while (i > 0) {
        i = (i - 1) / 2;
        dat_[i] = op_(dat_[2 * i + 1], dat_[2 * i + 2]);
      }
    }
    // query for [a, b)
    T query(int a, int b) { return query_sub(a, b, 0, 0, n_); }
    // get i-th value
    T get(int i) { return dat_[i + n_ - 1]; }
  private:
    std::vector<T> dat_;
    int n_;
    std::function<T()> e_;
    std::function<T(T, T)> op_, update_;

    T query_sub(int a, int b, int k, int l, int r) {
      if (r <= a || l >= b) {
        return e_();
      } else if (a <= l && r <= b) {
        return dat_[k];
      } else {
        T vl = query_sub(a, b, 2 * k + 1, l, (l + r) / 2);
        T vr = query_sub(a, b, 2 * k + 2, (l + r) / 2, r);
        return op_(vl, vr);
      }
    }
};

#endif //SEGMENT_TREE_HPP