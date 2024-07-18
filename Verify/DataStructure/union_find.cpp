#include "../../DataStructure/union_find.hpp"

void Verify_1(){
  /*
    Verified : Library Checker (Unionfind)
      https://judge.yosupo.jp/problem/unionfind
   */

  //Input
  int N,Q; std::cin >> N >> Q;

  //Solve
  UnionFind uf(N);
  while(Q--){
    int t, u, v; std::cin >> t >> u >> v;
    if (t) std::cout << uf.same(u, v) << std::endl;
    else uf.unite(u, v);
  }
}

int main() {
  Verify_1();
  return 0;
}