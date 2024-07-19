#ifndef BINOMIAL_COEFFICIENT_HPP
#define BINOMIAL_COEFFICIENT_HPP

#include "../Utility/templete.hpp"

class BinomialCoefficient {
  public:
    BinomialCoefficient(ll m) : m_(m), fac_(n_, 1), finv_(n_, 1), inv_(n_, 1) {
      for (int i = 2; i < n_; i++) {
        fac_[i] = (fac_[i - 1] * i) % m_;
        inv_[i] = (m_ - (inv_[m_ % i] * (m_ / i)) % m_);
        finv_[i] = (finv_[i - 1] * inv_[i]) % m_;
      }
    }
    ll C(int n, int k) {
      if (n < k) return 0;
      if (n < 0 || k < 0) return 0;
      return fac_[n] * (finv_[k] * finv_[n - k] % m_) % m_;
    }
    ll P(int n, int k) {
      if (n < k) return 0;
      if (n < 0 || k < 0) return 0;
      return fac_[n] * finv_[n - k] % m_;
    }
  private:
    int n_ = 10100000; //maxN
    ll m_; //prime
    std::vector<ll> fac_, finv_, inv_;
};

#endif //BINOMIAL_COEFFICIENT_HPP