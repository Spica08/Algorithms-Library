#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP

#include "../Utility/templete.hpp"

struct BigInteger{
  public:
    BigInteger(std::string x = std::to_string(0)){
      value_ = (x[0] == '-' ? to_bigint(x.substr(1)) : to_bigint(x));
      sign_ = !(x[0] == '-');
    };
    BigInteger(std::vector<int> value, bool sign) : value_(value), sign_(sign){};

    std::vector<int> to_bigint(std::string S){
      int N = S.size();
      std::vector<int> res(N);
      for (int i = 0; i < N; i++) res[i] = S[N - i - 1] - '0';
      return res;
    }

    void print_val(){
      std::string res = "";
      for(int n : value_) res += char(n + '0');
      if(!sign_) res += '-';
      reverse(res.begin(), res.end());
      for(char c:res){
        std::cout << c;
      }
      std::cout << std::endl;
    }

    BigInteger operator-() const {
      return BigInteger(value_, 1 ^ sign_);
    }

    bool operator<(const BigInteger& o) const {
      if(sign_ != o.sign_) return o.sign_;
      if(sign_) return abs_comparison(value_, o.value_);
      else return abs_comparison(o.value_, value_);
    }
    bool operator>(const BigInteger& o) const {return o < *this;}
    bool operator<=(const BigInteger& o) const { return !(o < *this);}
    bool operator>=(const BigInteger& o) const { return o <= *this; }
    bool operator==(const BigInteger& o) const { return *this <= o && o >= *this; }
    bool operator!=(const BigInteger& o) const { return !(*this == o); }

    BigInteger& operator+=(const BigInteger& a) {
      if(sign_ ^ a.sign_){
        if(sign_){
          if(abs_comparison(value_, a.value_)){
            value_ = subtraction(a.value_, value_);
            sign_ = 0;
          }else{
            value_ = subtraction(value_, a.value_);
          }
        }else{
          if(!abs_comparison(a.value_, value_)){
            value_ = subtraction(a.value_, value_);
            sign_ = 1;
          }else{
            value_ = subtraction(value_, a.value_);
          }
        }
      }else{
        value_ = addition(value_, a.value_);
      }
      return *this;
    }

    BigInteger& operator-=(const BigInteger& a) {
      *this += (-a);
      return *this;
    }

    BigInteger& operator*=(const BigInteger& a) {
      if(sign_ ^ a.sign_){
        value_ = multiplication(value_, a.value_);
        sign_ = (value_.size() == 1 && value_[0] == 0);
      }else{
        value_ = multiplication(value_, a.value_);
        sign_ = 1;
      }
      return *this;
    }

    BigInteger operator+(const BigInteger& a) const {
      BigInteger res(*this);
      return res+=a;
    }

    BigInteger operator-(const BigInteger& a) const {
      BigInteger res(*this);
      return res-=a;
    }

    BigInteger operator*(const BigInteger& a) const {
      BigInteger res(*this);
      return res*=a;
    }
  private:
    std::vector<int> value_;
    bool sign_;

    void carry_and_fix(std::vector<int> &d) const {
      int N = d.size();
      for(int i = 0; i < N - 1; ++i) {
        // carry
        if(d[i] >= 10) {
          d[i + 1] += d[i] / 10;
          d[i] %= 10;
        }
        // borrow
        if(d[i] < 0) {
          int K = (-d[i] - 1) / 10 + 1;
          d[i] += K * 10;
          d[i + 1] -= K;
        }
      }
      // carry
      while(d.back() >= 10) {
        int K = d.back() / 10;
        d.back() -= K * 10;
        d.push_back(K);
      }
      // borrow (erase leading zero)
      while(d.size() >= 2 && d.back() == 0) {
        d.pop_back();
      }
    }

    std::vector<int> addition(const std::vector<int> &a, const std::vector<int> &b) const {
      int N = std::max(a.size(), b.size());
      std::vector<int> res(N);
      for(int i = 0; i < N; i++) {
        res[i] = (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
      }
      carry_and_fix(res);
      return res;
    }

    std::vector<int> subtraction(const std::vector<int> &a, const std::vector<int> &b) const {
      int N = std::max(a.size(), b.size());
      std::vector<int> res(N);
      for(int i = 0; i < N; i++) {
        res[i] = (i < a.size() ? a[i] : 0) - (i < b.size() ? b[i] : 0);
      }
      carry_and_fix(res);
      return res;
    }

    //O(N^2)
    std::vector<int> multiplication(const std::vector<int> &a, const std::vector<int> &b) const {
      int NA = a.size();
      int NB = b.size();
      std::vector<int> res(NA + NB - 1);
      for (int i = 0; i < NA; i++) for (int j = 0; j < NB; j++) {
        res[i + j] += a[i] * b[j];
      }
      carry_and_fix(res);
      return res;
    }

    // comparison with abs, return true if a < b
    bool abs_comparison(const std::vector<int> &a, const std::vector<int> &b) const {
      // if num of digits are same
      if(a.size() != b.size()) return a.size() < b.size();
      // if num of digits are not same
      int sz = a.size();
      for (int i = 0; i < sz; i++) {
        if(a[sz - i - 1] != b[sz - i - 1]) return a[sz - i - 1] < b[sz - i - 1];
      }
      return false;
    }
};

#endif //BIG_INTEGER_HPP