#include "../../Math/eratosthenes.hpp"

void Verify_1(){
  /*
    Verified : ABC084-D (2017-like Number)
      https://atcoder.jp/contests/abc084/tasks/abc084_d
   */

  //Input
  ll Q; std::cin >> Q;

  //Build
  const int N = 100100;
  Eratosthenes sieve(N);
  std::vector<int> A(N), S(N + 1);
  for(int i = 0; i < N; i++){
    if((i & 1) && sieve.IsPrime(i) && sieve.IsPrime((i + 1) / 2)) A[i] = 1;
    S[i + 1] = S[i] + A[i];
  }

  //Solve
  while(Q--){
    int l, r; std::cin >> l >> r;
    l++; r++;
    std::cout << S[r] - S[l - 1] << std::endl;
  }
}

int main(){
  Verify_1();
  return 0;
}