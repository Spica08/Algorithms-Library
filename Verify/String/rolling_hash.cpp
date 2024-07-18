#include "../../String/rolling_hash.hpp"

void Verify_1(){
  /*
    Verified : AOJ (String Search)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
   */

  //Input
  std::string T, P; std::cin >> T >> P;
  std::string TP = T + P;
  
  //Build
  RollingHash rh(TP);
  ull p_hash = rh.get(T.size(), TP.size());

  //Solve
  for(int i = 0; i < int(T.size()) - int(P.size()) + 1; i++){
    if(rh.get(i, i + P.size()) == p_hash) std::cout << i << std::endl;
  }
}

void Verify_2(){
  /*
    Verified : AOJ (String Search)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
   */

  //Input
  std::string T, P; std::cin >> T >> P;
  
  //Build
  ull base = GenerateRandInt<ull>(0, mod_hash - 1);
  RollingHash rh_t(T, base), rh_p(P, base);
  ull p_hash = rh_p.get(0, P.size());

  //Solve
  for(int i = 0; i < int(T.size()) - int(P.size()) + 1; i++){
    if(rh_t.get(i, i + P.size()) == p_hash) std::cout << i << std::endl;
  }
}

int main() {
  Verify_1(); // default argument
  Verify_2();  // use common base
  return 0;
}