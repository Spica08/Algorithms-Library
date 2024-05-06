#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

//Kruskal
struct MinimumSpanningTree{
  using E = pair<ll, tuple<int, int, int>>; //from, to, id
  int N;
  UnionFind uf;
  ll cost = 0;
  vector<tuple<int,int,int>> edges;
  priority_queue<E, vector<E>, greater<E>> pq;

  MinimumSpanningTree(int N) : N(N), uf(N){};

  void add_edge(int u, int v, ll c, int id){
    assert(u >= 0 && u < N);
    assert(v >= 0 && v < N);
    pq.push({c, {u, v, id}});
  }

  //build MST (Kruskal)
  void build(){
    while(!pq.empty()){
      E now = pq.top(); pq.pop();
      if (!uf.same(get<0>(now.second), get<1>(now.second))){
        uf.unite(get<0>(now.second), get<1>(now.second));
        edges.push_back(now.second);
        cost += now.first;
      }
    }
  }
};

void Verify(){
  /*
    Verify with Library Checker (Minimum Spanning Tree)
      https://judge.yosupo.jp/problem/minimum_spanning_tree
   */

  //Input
  int N, M; cin >> N >> M;
  
  //Build
  MinimumSpanningTree mst(N);
  for (int i = 0; i < M; i++) {
    int a, b; cin >> a >> b;
    ll c; cin >> c;
    mst.add_edge(a, b, c, i);
  }
  
  //Solve
  mst.build();
  cout << mst.cost << endl;
  for (int i = 0; i < mst.edges.size(); i++) {
    cout << get<2>(mst.edges[i]) << " \n"[i == mst.edges.size() - 1];
  }
}

int main(){
  Verify();
  return 0;
}