#include "../../Math/big_integer.hpp"

void Verify_1(){
  /*
    Verified : Library Checker (Addition of Big Integers)
      https://judge.yosupo.jp/problem/addition_of_big_integers
   */

  //Input
  int T; std::cin >> T;

  //Solve
  while(T--){
    std::string A, B; std::cin>> A >> B;
    BigInteger a(A), b(B);
    (a + b).print_val();
  }
}

void Verify_2(){
  /*
    Verified : AOJ (Multiplication of Big Integers)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_2_C
   */

  //Input and Solve
  std::string A, B; std::cin>> A >> B;
  BigInteger a(A), b(B);
  (a * b).print_val();
}

int main(){
  Verify_1(); //Addition
  Verify_2(); //Multiplication (O(N^2))
  return 0;
}