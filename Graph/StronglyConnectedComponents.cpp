#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct UnweightedGraph{
  int N;
  vector<vector<int>> G;
  UnweightedGraph(int N): N(N), G(N){}
  void read_edge(int zero_indexed = 0, int directed = 0){
    int u, v; cin >> u >> v; 
    add_edge(u, v, zero_indexed, directed);
  }
  void add_edge(int u, int v, int zero_indexed = 0, int directed = 0){
    if (!zero_indexed) {u--; v--;}
    G[u].push_back(v);
    if(!directed)G[v].push_back(u);
  }
  int size()const{return G.size();};
  const vector<int>& operator[](int i)const{return G[i];};
};

//@@
struct StrongConnectedComponents {
  int n;
  UnweightedGraph G, rG;
  vector<int> order, component, seen;

  StrongConnectedComponents(UnweightedGraph &g) : 
    n(g.size()), G(n), rG(n), component(n, -1), seen(n){
    for(int i = 0; i < n; i++){
      for(auto e : g[i]){
        G.add_edge(i, e, 1, 1);
        rG.add_edge(e, i, 1, 1);
      }
    }
    for (int i = 0; i < n; i++) {
      if (seen[i])continue;
      dfs(i);
    }
    reverse(order.begin(), order.end());
    int cnt = 0;
    for (int i : order) {
      if (component[i] != -1)continue;
      rdfs(i, cnt);
      cnt++;
    }
  }

  void dfs(int n){
    seen[n] = 1;
    for(auto e : G[n]){
      if(seen[e]) continue;
      dfs(e);
    }
    order.push_back(n);
  }

  void rdfs(int n, int cnt){
    component[n] = cnt;
    for(auto e : rG[n]){
      if(component[e] != -1) continue;
      rdfs(e, cnt);
    }
  }

  // SCC後のグラフ再構築
  void rebuild(UnweightedGraph &nG, vector<int> &s){
    int N = 0;
    for (int c : component) N = max(N, c + 1);
    nG = UnweightedGraph(N);
    s.assign(N, 0);
    set<pair<int,int>> connected; //多重辺を管理
    //グラフ再構築
    for (int u = 0; u < n; u++) {
      for (auto v : G[u]) {
        int x = component[u];
        int y = component[v];
        if(x == y)continue;
        if(connected.count({x, y}))continue;
        connected.emplace(x, y);
        nG.add_edge(x, y, 1, 1);
      }
    }
    //各強連結成分のサイズ
    for (auto x : component) s[x]++;
  }
};
//@@

void Verify(){
  /*
    Verify with AOJ (Strongly Connected Components)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C
   */

  //Input
  int V, E; cin >> V >> E;
  UnweightedGraph G(V);
  for(int i = 0; i < E; i++) G.read_edge(1, 1);

  //SCC 
  UnweightedGraph reG(0);
  vector<int> sz;
  StrongConnectedComponents scc(G);
  scc.rebuild(reG, sz);

  //Solve
  int Q; cin >> Q;
  while(Q--){
    int u, v; cin >> u >> v;
    cout << (scc.component[u] == scc.component[v]) << endl;
  }
}

int main() {
  Verify();
  return 0;
}