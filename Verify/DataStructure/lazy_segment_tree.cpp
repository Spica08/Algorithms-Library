#include "../../DataStructure/lazy_segment_tree.hpp"

void Verify_1(){
  /*
    Verified : ABC340-E (Mancala 2)
      https://atcoder.jp/contests/abc340/tasks/abc340_e
   */

  //Input
  int N,M; std::cin >> N >> M;

  //Build Lazy Segment Tree
  struct S {
    ll v, s;
    S(ll v, ll s) : v(v), s(s){};
  };
  auto es = [](){return S(0, 1);};
  auto et = [](){return 0;};
  auto op = [](S a, S b){return S(a.v + b.v, a.s + b.s);};
  auto mapping = [](ll b, S a){return S(a.v + b * a.s, a.s);};
  auto composition = [](ll a, ll b){return a + b;};
  LazySegmentTree<S, ll> lazy(N, es, et, op, mapping, composition);
  for (int i = 0; i < N; i++) {
    ll a; std::cin >> a;
    lazy.set(i, S(a, 1));
  }

  //Solve
  while(M--){
    int b; std::cin >> b;
    ll n = lazy.get(b).v;
    lazy.set(b, S(0, 1));
    if (n >= N) lazy.update(0, N, n/N);
    n %= N;
    int c = b + n;
    if (c < N){
      lazy.update(b + 1, c + 1, 1);
    }else{
      c -= N;
      lazy.update(b + 1, N, 1);
      lazy.update(0, c + 1, 1);
    }
  }
  for (int i = 0; i < N; i++) {
    std::cout << lazy.get(i).v << " \n"[i==N-1];
  }
}

void Verify_2(){
  /*
    Verified : Library Checker (Range Affine Range Sum)
      https://judge.yosupo.jp/problem/range_affine_range_sum
   */

  //Input
  int N,Q; std::cin >> N >> Q;
  struct S{
    ll v, s;
    S(ll v, ll s) : v(v), s(s){};
  };
  using P = std::pair<ll,ll>;
  auto es = [](){return S(0, 0);};
  auto et = [](){return P(1, 0);};
  auto op = [](S a, S b){return S{(a.v + b.v) % mod, a.s + b.s};};
  auto mapping = [](P b, S a){
    return S{((a.v * b.first) + (a.s * b.second)) % mod, a.s};
  };
  auto composition = [](P a, P b){
    return P{a.first * b.first % mod, (a.second * b.first + b.second ) % mod};
  };
  LazySegmentTree<S, P> lazy(N, es, et, op, mapping, composition);
  for (int i = 0; i < N; i++) {
    int a; std::cin >> a;
    lazy.set(i,S(a, 1));
  }
  for (int i = 0; i < Q; i++) {
    int q; std::cin >> q;
    if(q == 0){
      int l, r; std::cin >> l >> r;
      ll b, c; std::cin >> b >> c;
      lazy.update(l, r, P(b,c));
    }
    if(q == 1){
      int l, r; std::cin >> l >> r;
      std::cout << lazy.query(l, r).v << std::endl;
    }
  }
}

int main(){
  Verify_1(); //Range Add
  Verify_2(); //Range Affine Range Sum
  return 0;
}