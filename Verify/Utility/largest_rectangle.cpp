#include "../../Utility/largest_rectangle.hpp"

void Verify_1(){
  /*
    Verified : AOJ (Largest Rectangle in a Histogram)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C
   */

  //Input
  int N; std::cin >> N;
  std::vector<ll> H(N);
  for(int i = 0; i < N; i++) std::cin >> H[i];

  //Solve
  std::cout << LargestRectangle<ll>(H) << std::endl;
}

int main(){
  Verify_1();
  return 0;
}