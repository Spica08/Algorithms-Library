#include "../../Utility/mod_templete.hpp"

void Verify_1(){
  /*
    Verified : Simple Test
   */

  for(int i = 0; i < 13; i++) std::cout << i << "'s inv(mod 13): " << minv(i, 13) << std::endl;

  std::cout << 12345678900000 << "'s inv(mod 998244353): " << minv(12345678900000, mod) << std::endl;
  std::cout  << "12345678900000 / 100000 (mod 998244353): " << 12345678900000 % mod * minv(100000, mod) % mod<< std::endl;
}

void Verify_2(){
  /*
    Verified : JSC2021-D (Nowhere P)
      https://atcoder.jp/contests/jsc2021/tasks/jsc2021_d
   */

  //Input
  ll N, P; std::cin >> N >> P;
  
  //Solve
  std::cout << (P - 1) * mpow(P - 2, N - 1, 1000000007) % 1000000007 << std::endl;
}

int main() { 
  Verify_1(); //minv
  Verify_2(); //mpow
  return 0; 
}