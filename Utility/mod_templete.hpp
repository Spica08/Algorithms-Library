#ifndef MOD_TEMPLETE_HPP
#define MOD_TEMPLETE_HPP

#include "../Utility/templete.hpp"

ll minv(ll a, ll m) {
  ll b = m, x = 1, y = 0;
  while(b > 0){
    ll t = a / b;
    a -= t * b; std::swap(a, b);
		x -= t * y; std::swap(x, y);
  }
  x %= m;
  if (x < 0) x += m;
  return x;
}

ll mpow(ll a, ll n, ll m) {
  if (n == 0) return 1;
  if (n == 1) return a % m;
  if (n % 2 == 0) {
    ll t = mpow(a, n / 2, m);
    return (t * t) % m;
  } else {
    return mpow(a, n - 1, m) * a % m;
  }
}

#endif //MOD_TEMPLETE_HPP