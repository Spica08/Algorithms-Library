#include "../../DataStructure/binary_indexed_tree.hpp"

void Verify_1(){
  /*
    Verify : Library Checker (Point Add Range Sum)
      https://judge.yosupo.jp/problem/point_add_range_sum
   */

  //Input
  int N, Q; std::cin >> N >> Q;

  //Build Binary Indexed Tree
  auto e = [](){return 0;};
  auto op = [](ll a, ll b) {return a + b;};
  auto inv = [](ll a) { return -a;};
  BinaryIndexedTree<ll> bit(N, e, inv, op);
  for (int i = 0; i < N; i++) {
    ll a; std::cin>>a;
    bit.add(i + 1, a);
  }

  //Solve
  while(Q--){
    int q; std::cin >> q;
    if(q == 0){
      int p; std::cin >> p;
      ll x; std::cin >> x;
      bit.add(p + 1, x);
    }
    if(q == 1){
      int l,r; std::cin >> l >> r;
      std::cout << bit.sum(l + 1, r) << std::endl;
    }
  }
}

int main() {
  Verify_1();
  return 0;
}