#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 998244353;

//@@
template <typename T>
struct SegmentTree {
  vector<T> dat;
  int n;
  function<T()> e;
  function<T(T, T)> op, update;
  SegmentTree(int N, function<T()> e, function<T(T, T)> op, function<T(T, T)> update)
      : e(e), op(op), update(update) {
    n = 1;
    while (N > n) n *= 2;
    dat.assign(2 * n - 1, e());
  }
  // update i-th value
  void change(int i, T x) {
    i += n - 1;
    dat[i] = update(dat[i], x);
    while (i > 0) {
      i = (i - 1) / 2;
      dat[i] = op(dat[2 * i + 1], dat[2 * i + 2]);
    }
  }
  // query for [a, b)
  T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
  T query_sub(int a, int b, int k, int l, int r) {
    if (r <= a || l >= b) {
      return e();
    } else if (a <= l && r <= b) {
      return dat[k];
    } else {
      T vl = query_sub(a, b, 2 * k + 1, l, (l + r) / 2);
      T vr = query_sub(a, b, 2 * k + 2, (l + r) / 2, r);
      return op(vl, vr);
    }
  }
  // get i-th value
  T get(int i) { return dat[i + n - 1]; }
};
//@@

void Verify(){
  /*
    Verify with Library Checker (Point Set Range Compsite)
      https://judge.yosupo.jp/problem/point_set_range_composite
   */

  //Input
  int N, Q;cin>>N>>Q;

  //Build Segment Tree
  using P = pair<ll,ll>;
  auto e = [&](){return P(1, 0);};
  auto op = [&](P a, P b) { 
    return P(a.first * b.first % mod, (a.second * b.first + b.second) % mod); 
  };
  auto update = [&](P a, P b) { return b; };
  SegmentTree<P> seg(N, e, op, update);
  for (int i = 0; i < N; i++) {
    ll a, b;cin>>a>>b;
    seg.change(i, P(a, b));
  }

  //Solve
  while(Q--){
    int q;cin>>q;
    if(q == 0){
      int p;cin>>p;
      ll c,d;cin>>c>>d;
      seg.change(p, pair<ll,ll>(c, d));
    }
    if(q == 1){
      int l,r;cin>>l>>r;
      ll x;cin>>x;
      pair<ll,ll> f = seg.query(l,r);
      cout<<(f.first * x + f.second) % mod<<endl;
    }
  }
}

int main() {
  Verify();
  return 0;
}