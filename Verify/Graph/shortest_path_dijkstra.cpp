#include "../../Graph/shortest_path_dijkstra.hpp"

void Verify_1(){
  /*
    Verify with Library Checker (Shortest Path)
      https://judge.yosupo.jp/problem/shortest_path
   */

  //Input
  int N, M; std::cin >> N >> M;
  int s, t; std::cin >> s >> t;
  WeightedGraph<ll> G(N);
  for (int i = 0; i < M; i++) {
    int a, b; std::cin >> a >> b;
    ll c; std::cin >> c;
    G.add_edge(a, b, i, c, 1, 1);
  }

  //Solve
  ll nan = INF;
  auto d = [](ll a, ll b){return a + b;};
  Dijkstra<ll,ll> dijk(G, s, nan, d);
  if(dijk.dist[t] == nan) std::cout << -1 << std::endl;
  else{
    std::vector<int> ans = dijk.Reconstruct(t);
    std::cout << dijk.dist[t] << " " << ans.size() - 1 << std::endl;
    for (int i = 0; i < ans.size() - 1; i++) {
      std::cout << ans[i] << " " << ans[i+1] << std::endl;
    }
  }
}

void Verify_2(){
  /*
    Verify with ABC192-E (Train)
      https://atcoder.jp/contests/abc192/tasks/abc192_e
   */

  //Input
  int N, M, X, Y;
  std::cin >> N >> M >> X >> Y;
  X--; Y--;
  struct Cost{
    ll t, k;
    Cost(ll t, ll k) : t(t), k(k){}
  };
  WeightedGraph<Cost> G(N);
  for (int i = 0; i < M; i++) {
    ll u, v, t, k;
    std::cin >> u >> v >> t >> k;
    G.add_edge(u, v, i, Cost(t,k), 0, 0);
  }
  
  //Solve
  ll nan = INF;
  auto d = [](ll a, Cost b){return (a + b.k - 1) / b.k * b.k + b.t;};
  Dijkstra<ll, Cost> dijk(G, X, nan, d);
  if (dijk.dist[Y] == nan) std::cout << -1 << std::endl;
  else std::cout << dijk.dist[Y] << std::endl;
}

int main(){
  Verify_1(); // Shortest Path
  Verify_2(); // Shortest Path with irregular cost
  return 0;
}