#include "../../DataStructure/segment_tree.hpp"

void Verify_1(){
  /*
    Verified : Library Checker (Point Set Range Compsite)
      https://judge.yosupo.jp/problem/point_set_range_composite
   */

  //Input
  int N, Q; std::cin >> N >> Q;

  //Build Segment Tree
  using P = std::pair<ll,ll>;
  auto e = [&](){return P(1, 0);};
  auto op = [&](P a, P b) { 
    return P(a.first * b.first % mod, (a.second * b.first + b.second) % mod); 
  };
  auto update = [&](P a, P b) { return b; };
  SegmentTree<P> seg(N, e, op, update);
  for (int i = 0; i < N; i++) {
    ll a, b; std::cin >> a >> b;
    seg.change(i, P(a, b));
  }

  //Solve
  while(Q--){
    int q; std::cin >> q;
    if(q == 0){
      int p; std::cin >> p;
      ll c,d; std::cin >> c >> d;
      seg.change(p, std::pair<ll,ll>(c, d));
    }
    if(q == 1){
      int l,r; std::cin >> l >> r;
      ll x; std::cin >> x;
      std::pair<ll,ll> f = seg.query(l,r);
      std::cout << (f.first * x + f.second) % mod << std::endl;
    }
  }
}

int main(){
  Verify_1();
}