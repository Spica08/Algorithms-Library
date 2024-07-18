#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include "../Utility/templete.hpp"

class UnionFind {
  public:
    UnionFind(int N) : par_(N, -1), rank_(N, 0), group_(N) {}
    int root(int x) {
      if (par_[x] < 0) return x;
      return par_[x] = root(par_[x]);
    }
    void unite(int x, int y) {
      x = root(x); y = root(y);
      if (x == y) return;
      group_--;
      if(rank_[x] < rank_[y]) std::swap(x, y);
      par_[x] += par_[y];
      par_[y] = x;
      if (rank_[x] == rank_[y]) rank_[x]++;
    }
    bool same(int x, int y) { return root(x) == root(y); }
    int size(int x) { return -1 * par_[root(x)]; }
    int num_group() const { return group_;}
  private:
    int group_;
    std::vector<int> par_, rank_;
};

#endif //UNION_FIND_HPP