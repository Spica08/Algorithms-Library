#include "../../Graph/minimum_spanning_tree_kruskal.hpp"

void Verify_1(){
  /*
    Verify : Library Checker (Minimum Spanning Tree)
      https://judge.yosupo.jp/problem/minimum_spanning_tree
   */

  //Input
  int N, M; std::cin >> N >> M;
  
  //Build
  MinimumSpanningTree<ll> mst(N);
  for (int i = 0; i < M; i++) {
    int a, b; std::cin >> a >> b;
    ll c; std::cin >> c;
    mst.add_edge(a, b, i, c, 1);
  }
  
  //Solve
  mst.build();
  std::cout << mst.cost << std::endl;
  for(auto e : mst.mst_edges){
    std::cout << e.id << " ";
  }
  std::cout << std::endl;
}

int main(){
  Verify_1();
  return 0;
}