#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename S, typename T>
struct LazySegmentTree {
  vector<S> dat;
  vector<T> lazy;
  int n, layer;
  function<S()> es;
  function<T()> et;
  function<S(S, S)> op;
  function<S(T, S)> mapping;
  function<T(T, T)> composition;

  LazySegmentTree(int N, function<S()> es, function<T()> et, 
                  function<S(S, S)> op, function<S(T, S)> mapping, function<T(T,T)> composition) 
      :es(es), et(et), op(op), mapping(mapping), composition(composition){
    n = 1;
    while (N > n) n <<= 1;
    dat.assign(2 * n - 1, es());
    lazy.assign(2 * n - 1, et());
  }
  void eval(int k) {
    if (lazy[k] == et()) return;
    if (k < n - 1) {
      lazy[2 * k + 1] = composition(lazy[2 * k + 1],lazy[k]);
      lazy[2 * k + 2] = composition(lazy[2 * k + 2],lazy[k]);
    }
    dat[k] = mapping(lazy[k], dat[k]);
    lazy[k] = et();
  }
  void set(int i, S x){
    i += n - 1;
    int j = i;
    stack<int> P;
    while(j){
      P.push(j);
      j = ((j - 1) >> 1);
    }
    while(!P.empty()) eval(P.top()), P.pop();
    dat[i] = x;
    while(i){
      i = ((i - 1) >> 1);
      dat[i] = op(dat[2 * i + 1], dat[2 * i + 2]);
    }
  }
  S get(int i){
    i += n - 1;
    int j = i;
    stack<int> P;
    while(j){
      P.push(j);
      j = ((j - 1) >> 1);
    }
    while(!P.empty()) eval(P.top()), P.pop();
    return dat[i];
  }
  void update(int a, int b, T x) { return update_sub(a, b, x, 0, 0, n); }
  void update_sub(int a, int b, T x, int k, int l, int r) {
    eval(k);
    if (a <= l && r <= b) {
      lazy[k] = composition(lazy[k], x);
      eval(k);
    } else if (a < r && l < b) {
      update_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
      update_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
      dat[k] = op(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }
  S query(int a, int b) { return query_sub(a, b, 0, 0, n); }
  S query_sub(int a, int b, int k, int l, int r) {
    eval(k);
    if (r <= a || l >= b) {
      return es();
    } else if (a <= l && r <= b) {
      return dat[k];
    } else {
      S vl = query_sub(a, b, 2 * k + 1, l, (l + r) / 2);
      S vr = query_sub(a, b, 2 * k + 2, (l + r) / 2, r);
      return op(vl, vr);
    }
  }
};

void Verify_1(){
  /*
    Verify with ABC340-E (Mancala 2)
      https://atcoder.jp/contests/abc340/tasks/abc340_e
   */

  //Input
  int N,M;cin>>N>>M;

  //Build Lazy Segment Tree
  struct S {
    ll v, s;
    S(ll v, ll s):v(v), s(s){};
  };
  auto es = [](){return S(0, 1);};
  auto et = [](){return 0;};
  auto op = [](S a, S b){return S(a.v + b.v, a.s + b.s);};
  auto mapping = [](ll b, S a){return S(a.v + b * a.s, a.s);};
  auto composition = [](ll a, ll b){return a + b;};
  LazySegmentTree<S, ll> lazy(N, es, et, op, mapping, composition);
  for (int i = 0; i < N; i++) {
    ll a;cin>>a;
    lazy.set(i, S(a, 1));
  }

  //Solve
  while(M--){
    int b;cin>>b;
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
    cout<<lazy.get(i).v<<" \n"[i==N-1];
  }
}

void Verify_2(){
  /*
    Verify with Library Checker (Range Affine Range Sum)
      https://judge.yosupo.jp/problem/range_affine_range_sum
   */
  const ll mod = 998244353;

  //Input
  int N,Q;cin>>N>>Q;
  struct S{
    ll v,s;
    S(ll v, ll s):v(v), s(s){};
  };
  using P = pair<ll,ll>;
  auto es = [](){return S(0,0);};
  auto et = [](){return P(1,0);};
  auto op = [](S a, S b){return S{(a.v + b.v) % mod, a.s + b.s};};
  auto mapping = [](P b, S a){
    return S{((a.v * b.first) + (a.s * b.second)) % mod, a.s};
  };
  auto composition = [](P a, P b){
    return P{a.first * b.first % mod, (a.second * b.first + b.second ) % mod};
  };
  LazySegmentTree<S, P> lazy(N, es, et, op, mapping, composition);
  for (int i = 0; i < N; i++) {
    int a;cin>>a;
    lazy.set(i,S(a, 1));
  }
  for (int i = 0; i < Q; i++) {
    int q;cin>>q;
    if(q == 0){
      int l, r; cin >> l >> r;
      ll b, c; cin >> b >> c;
      lazy.update(l, r, P(b,c));
    }
    if(q == 1){
      int l, r; cin >> l >> r;
      cout << lazy.query(l, r).v << endl;
    }
  }
}

int main(){
  Verify_1(); //Range Add
  Verify_2(); //Range Affine Range Sum
  return 0;
}