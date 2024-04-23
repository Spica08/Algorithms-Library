#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// int or long long
template <typename T>
struct CumulativeSum {
  vector<T> S;
  CumulativeSum(vector<T> A) {
    int N = A.size();
    S.assign(N + 1, 0);
    for (int i = 0; i < N; i++) S[i + 1] = S[i] + A[i];
  }
  //sum of [l, r) (0-indexed)
  T sum(int l, int r) { return S[r] - S[l]; }
};

void Verify(){
  /*
    Verify with Library Checker (Static Range Sum)
      https://judge.yosupo.jp/problem/static_range_sum
   */

  //Input
  int N,Q;cin>>N>>Q;
  vector<ll> A(N);
  for (int i = 0; i < N; i++) cin>>A[i];

  //Solve
  CumulativeSum<ll> S(A);
  while(Q--){
    int l, r; cin >> l >> r;
    cout<<S.sum(l, r)<<endl;
  }
}

int main() {
  Verify();
  return 0;
}