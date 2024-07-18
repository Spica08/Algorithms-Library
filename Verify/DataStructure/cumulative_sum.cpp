#include "../../DataStructure/cumulative_sum.hpp"

void Verify_1(){
  /*
    Verified : Library Checker (Static Range Sum)
      https://judge.yosupo.jp/problem/static_range_sum
   */

  //Input
  int N,Q; std::cin >> N >> Q;
  std::vector<ll> A(N);
  for (int i = 0; i < N; i++) std::cin >> A[i];

  //Solve
  CumulativeSum<ll> S(A);
  while(Q--){
    int l, r; std::cin >> l >> r;
    std::cout << S.sum(l, r) << std::endl;
  }
}

int main() {
  Verify_1();
  return 0;
}