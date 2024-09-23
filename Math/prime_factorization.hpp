#ifndef FACTORIZATION_HPP
#define FACTORIZATION_HPP

#include "../Utility/templete.hpp"

// factorize number O(sqrt(N)))
std::map<ll, ll> prime_factorization(ll N){
  std::map<ll, ll> res;
  for(ll i = 2; i * i <= N; i++){
    while(N % i == 0){
      res[i]++;
      N /= i;
    }
  }
  if(N != 1) res[N]++;
  return res;
}

#endif //FACTORIZATION_HPP