#include "../../Graph/tree_diameter.hpp"

void Verify_1(){
  /*
    Verified : AOJ (Diameter of a Tree)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A
   */

  //Input
  int n; std::cin >> n;
  WeightedGraph<ll> G(n);
  for(int i = 0; i < n - 1; i++) {
    int s, t; std::cin >> s >> t;
    ll w; std::cin >> w;
    G.add_edge(s, t, i, w, 1, 0);
  }

  //Solve
  TreeDiameter<WeightedGraph<ll>, ll> td(G);
  std::cout << td.diameter << std::endl;
}

void Verify_2(){
  /*
    Verified : AOJ (Tree Diameter)
      https://judge.yosupo.jp/problem/tree_diameter
   */

  //Input
  int n; std::cin >> n;
  WeightedGraph<ll> G(n);
  for(int i = 0; i < n - 1; i++) {
    int s, t; std::cin >> s >> t;
    ll w; std::cin >> w;
    G.add_edge(s, t, i, w, 1, 0);
  }

  //Solve
  TreeDiameter<WeightedGraph<ll>, ll> td(G);
  std::cout << td.diameter << " " << td.path.size() << std::endl;
  for(auto p : td.path) std::cout << p << " ";
  std::cout << std::endl;
}

int main() {
  Verify_1(); //diameter
  Verify_2(); //diameter and path
  return 0;
}