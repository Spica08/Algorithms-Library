#include "../../Math/binomial_coefficient.hpp"

void Verify_1(){
  /*
    Verified : with Library Checker (Binomial Coefficient (Prime Mod))
      https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
   */

  //Input
  ll T, m; std::cin >> T >> m;

  //Pre-Calculation
  BinomialCoefficient bc(m);

  //Solve
  while(T--){
    ll n, k; std::cin >> n >> k;
    std::cout << bc.C(n, k) << std::endl;
  }
}

int main(){
  Verify_1();
  return 0;
}