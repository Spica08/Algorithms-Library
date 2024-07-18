#include "../../Graph/graph_templete.hpp"

void Verify_1(){
  /*
    Verified : ABC276-B (Adjacency List)
      https://atcoder.jp/contests/abc276/tasks/abc276_b
   */

  //Input
  int N, M; std::cin >> N >> M;
  UnweightedGraph G(N);
  for (int i = 0; i < M; i++) {
    G.read_edge(0, 0);
  }

  //Solve
  for(int i = 0; i < N; i++){
    std::vector<int> t = G[i];
    sort(t.begin(), t.end());
    std::cout << t.size() << " ";
    for(int n : t){
      std::cout << n + 1 << " ";
    }
    std::cout << std::endl;
  }
}

void Verify_2(){
  /*
    Verified : ABC276-B (Adjacency List)
      https://atcoder.jp/contests/abc276/tasks/abc276_b
   */

  //Input
  int N, M; std::cin >> N >> M;
  WeightedGraph<ll> G(N);
  for (int i = 0; i < M; i++) {
    int a, b; std::cin >> a >> b;
    G.add_edge(a, b, i, 1, 0, 0);
  }

  //Solve
  for(int i = 0; i < N; i++){
    std::vector<int> t;
    for(auto n : G[i]) t.push_back(n.to);
    sort(t.begin(), t.end());
    std::cout << t.size() << " ";
    for(int n : t){
      std::cout << n + 1 << " ";
    }
    std::cout << std::endl;
  }
}

int main(){
  Verify_1(); //UnweghtedGraph
  Verify_2(); //WeghtedGraph
}