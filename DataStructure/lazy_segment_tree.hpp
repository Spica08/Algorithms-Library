#ifndef LAZY_SEGMENT_TREE_HPP
#define LAZY_SEGMENT_TREE_HPP

#include "../Utility/templete.hpp"

template <typename S, typename T>
class LazySegmentTree {
  public:
    LazySegmentTree(int N, std::function<S()> es, std::function<T()> et, 
                    std::function<S(S, S)> op, std::function<S(T, S)> mapping, std::function<T(T,T)> composition) 
        :es_(es), et_(et), op_(op), mapping_(mapping), composition_(composition){
      n_ = 1;
      while (N > n_) n_ <<= 1;
      dat_.assign(2 * n_ - 1, es_());
      lazy_.assign(2 * n_ - 1, et_());
    }
    void set(int i, S x){
      i += n_ - 1;
      int j = i;
      std::stack<int> P;
      while(j){
        P.push(j);
        j = ((j - 1) >> 1);
      }
      while(!P.empty()) eval(P.top()), P.pop();
      dat_[i] = x;
      while(i){
        i = ((i - 1) >> 1);
        dat_[i] = op_(dat_[2 * i + 1], dat_[2 * i + 2]);
      }
    }
    S get(int i){
      i += n_ - 1;
      int j = i;
      std::stack<int> P;
      while(j){
        P.push(j);
        j = ((j - 1) >> 1);
      }
      while(!P.empty()) eval(P.top()), P.pop();
      return dat_[i];
    }
    void update(int a, int b, T x) { return update_sub(a, b, x, 0, 0, n_); }
    S query(int a, int b) { return query_sub(a, b, 0, 0, n_); }
  private:
    std::vector<S> dat_;
    std::vector<T> lazy_;
    int n_;
    std::function<S()> es_;
    std::function<T()> et_;
    std::function<S(S, S)> op_;
    std::function<S(T, S)> mapping_;
    std::function<T(T, T)> composition_;

    void eval(int k) {
      if (lazy_[k] == et_()) return;
      if (k < n_ - 1) {
        lazy_[2 * k + 1] = composition_(lazy_[2 * k + 1], lazy_[k]);
        lazy_[2 * k + 2] = composition_(lazy_[2 * k + 2], lazy_[k]);
      }
      dat_[k] = mapping_(lazy_[k], dat_[k]);
      lazy_[k] = et_();
    }

    void update_sub(int a, int b, T x, int k, int l, int r) {
      eval(k);
      if (a <= l && r <= b) {
        lazy_[k] = composition_(lazy_[k], x);
        eval(k);
      } else if (a < r && l < b) {
        update_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
        update_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
        dat_[k] = op_(dat_[2 * k + 1], dat_[2 * k + 2]);
      }
    }

    S query_sub(int a, int b, int k, int l, int r) {
      eval(k);
      if (r <= a || l >= b) {
        return es_();
      } else if (a <= l && r <= b) {
        return dat_[k];
      } else {
        S vl = query_sub(a, b, 2 * k + 1, l, (l + r) / 2);
        S vr = query_sub(a, b, 2 * k + 2, (l + r) / 2, r);
        return op_(vl, vr);
      }
    }
};

#endif //LAZY_SEGMENT_TREE_HPP