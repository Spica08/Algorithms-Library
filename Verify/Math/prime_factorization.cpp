#include "../../Math/prime_factorization.hpp"

void Verify_1(){
  /*
    Verified : AOJ (Prime Factorize)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A
   */

  //Input
  ll N; std::cin >> N;

  //Solve
  std::map<ll, ll> pf = prime_factorization(N);
  std::cout << N << ":";
  for(auto p : pf) {
    for(int i = 0; i < p.second; i++) {
      std::cout << " " << p.first;
    }
  }
  std::cout << std::endl;
}

int main(){
  Verify_1();
  return 0;
}