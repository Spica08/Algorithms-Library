#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct BinaryIndexedTree {
  int n;
  vector<T> dat;
  function<T()> e;
  function<T(T)> inv;
  function<T(T, T)> op;

  BinaryIndexedTree(int N, function<T()> e, function<T(T)> inv, function<T(T, T)> op) 
    : e(e), inv(inv), op(op), dat(N + 1, e()) { n = N + 1; }
  void add(int i, T x) {
    for (int idx = i; idx < n; idx += (idx & -idx)) dat[idx] = op(dat[idx], x);
  }
  T sum_sub(int i) {
    T res = e();
    for (int idx = i; idx > 0; idx -= (idx & -idx)) res = op(res, dat[idx]);
    return res;
  }
  // sum of [l, r] (1-indexed)
  T sum(int l, int r) { return op(sum_sub(r), inv(sum_sub(l - 1))); }
};

void Verify(){
  /*
    Verify with Library Checker (Point Add Range Sum)
      https://judge.yosupo.jp/problem/point_add_range_sum
   */

  //Input
  int N, Q;cin >> N >> Q;

  //Build Binary Indexed Tree
  auto e = [](){return 0;};
  auto op = [](ll a, ll b) {return a + b;};
  auto inv = [](ll a) { return -a;};
  BinaryIndexedTree<ll> bit(N, e, inv, op);
  for (int i = 0; i < N; i++) {
    ll a;cin>>a;
    bit.add(i + 1, a);
  }

  //Solve
  while(Q--){
    int q;cin>>q;
    if(q == 0){
      int p;cin>>p;
      ll x;cin>>x;
      bit.add(p + 1, x);
    }
    if(q == 1){
      int l,r;cin>>l>>r;
      cout<<bit.sum(l + 1, r)<<endl;
    }
  }
}

int main() {
  Verify();
  return 0;
}