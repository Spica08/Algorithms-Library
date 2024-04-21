#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
  int cnt;
  vector<int> par, rank;
  UnionFind(int N) : par(N, -1), rank(N, 0), cnt(N) {}
  int root(int x) {
    if (par[x] < 0) return x;
    return par[x] = root(par[x]);
  }
  void unite(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return;
    cnt--;
    if(rank[x] < rank[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    if (rank[x] == rank[y]) rank[x]++;
  }
  bool same(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -1 * par[root(x)]; }
};

void Verify(){
  /*
    Verify with Library Checker (Unionfind)
      https://judge.yosupo.jp/problem/unionfind
   */

  //Input
  int N,Q;cin>>N>>Q;

  //Solve
  UnionFind uf(N);
  while(Q--){
    int t, u, v; cin >> t >> u >> v;
    if (t) cout << uf.same(u, v) << endl;
    else uf.unite(u, v);
  }
}

int main() {
  Verify();
  return 0;
}