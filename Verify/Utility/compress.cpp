#include "../../Utility/compress.hpp"

void Verify_1(){
  /*
    Verified : ABC036-C (座圧)
      https://atcoder.jp/contests/abc036/tasks/abc036_c
   */

  //Input
  int N; std::cin >> N;
  std::vector<int> A(N);
  for (int i = 0; i < N; i++) std::cin >> A[i];
  
  //Build
  Compress<int> comp(A);
  
  //Solve
  for(int i = 0; i < N; i++) std::cout << comp[i] << std::endl;
}

int main() { 
  Verify_1();
  return 0; 
}