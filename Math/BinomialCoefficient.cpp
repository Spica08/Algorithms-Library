#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BinomialCoefficient {
  int N = 10100000; //maxN
  ll m; //prime
  vector<ll> fac, finv, inv;
  BinomialCoefficient(ll m) : m(m), fac(N, 1), finv(N, 1), inv(N, 1) {
    for (int i = 2; i < N; i++) {
      fac[i] = (fac[i - 1] * i) % m;
      inv[i] = (m - (inv[m % i] * (m / i)) % m);
      finv[i] = (finv[i - 1] * inv[i]) % m;
    }
  }
  ll C(int n, int k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % m) % m;
  }
  ll P(int n, int k) {
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * finv[n - k] % m;
  }
};

void Verify(){
  /*
    Verify with Library Checker (Binomial Coefficient (Prime Mod))
      https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
   */

  //Input
  ll T, m;cin>>T>>m;

  //Pre-Calculation
  BinomialCoefficient bc(m);

  //Solve
  while(T--){
    ll n, k;cin >> n >> k;
    cout<<bc.C(n, k)<<endl;
  }
}

int main(){
  Verify();
  return 0;
}