#include "../../Graph/strongly_connected_components.hpp"

void Verify_1(){
  /*
    Verified : AOJ (Strongly Connected Components)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C
   */

  //Input
  int V, E; std::cin >> V >> E;
  UnweightedGraph G(V);
  for(int i = 0; i < E; i++) G.read_edge(1, 1);

  //SCC 
  UnweightedGraph reG(0);
  std::vector<int> sz;
  StrongConnectedComponents scc(G);
  scc.rebuild(reG, sz);

  //Solve
  int Q; std::cin >> Q;
  while(Q--){
    int u, v; std::cin >> u >> v;
    std::cout << scc.IsSame(u, v) << std::endl;
  }
}

int main() {
  Verify_1();
  return 0;
}