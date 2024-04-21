#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using Matrix = vector<vector<ll>>;
const int inf = 1000000000;
const ll INF = 1000000000000000000;
const ll mod = 998244353;
const ull mod_hash = (1UL << 61) - 1;
const vector<int> dx = {0, 1, 0, -1, 1, 1, -1, -1};
const vector<int> dy = {1, 0, -1, 0, 1, -1, 1, -1};

struct BigInteger{
  vector<int> value;
  bool sign;
  BigInteger(string x = to_string(0)){
    if(x[0] == '-'){
      value = to_bigint(x.substr(1));
      sign = false;
    }else{
      value = to_bigint(x);
      sign = true;
    }
  };
  BigInteger(vector<int> v, bool sign) : value(v), sign(sign){};

  vector<int> to_bigint(string S){
    int N = S.size();
    vector<int> res(N);
    for (int i = 0; i < N; i++) res[i] = S[N - i - 1] - '0';
    return res;
  }

  void print_val(){
    string res = "";
    for(int n:value) res += char(n + '0');
    if(!sign) res += '-';
    reverse(res.begin(), res.end());
    for(char c:res){
      cout<<c;
    }
    cout<<endl;
  }

  void carry_and_fix(vector<int> &d) const {
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

  vector<int> addition(const vector<int> &a, const vector<int> &b) const {
    int N = max(a.size(), b.size());
    vector<int> res(N);
    for(int i = 0; i < N; i++) {
      res[i] = (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
    }
    carry_and_fix(res);
    return res;
  }

  vector<int> subtraction(const vector<int> &a, const vector<int> &b) const {
    int N = max(a.size(), b.size());
    vector<int> res(N);
    for(int i = 0; i < N; i++) {
      res[i] = (i < a.size() ? a[i] : 0) - (i < b.size() ? b[i] : 0);
    }
    carry_and_fix(res);
    return res;
  }

  // comparison with abs, return true if a < b
  bool abs_comparison(const vector<int> &a, const vector<int> &b) const {
    // if num of digits are same
    if(a.size() != b.size()) return a.size() < b.size();
    // if num of digits are not same
    int sz = a.size();
    for (int i = 0; i < sz; i++) {
      if(a[sz - i - 1] != b[sz - i - 1]) return a[sz - i - 1] < b[sz - i - 1];
    }
    return false;
  }

  BigInteger operator-() const {
    return BigInteger(value, 1 ^ sign);
  }

  bool operator<(const BigInteger& o) const {
    if(sign != o.sign) return o.sign;
    if(sign) return abs_comparison(value, o.value);
    else return abs_comparison(o.value, value);
  }
  bool operator>(const BigInteger& o) const {return o < *this;}
  bool operator<=(const BigInteger& o) const { return !(o < *this);}
  bool operator>=(const BigInteger& o) const { return o <= *this; }
  bool operator==(const BigInteger& o) const { return *this <= o && o >= *this; }
  bool operator!=(const BigInteger& o) const { return !(*this == o); }

  BigInteger& operator+=(const BigInteger& a) {
    if(sign ^ a.sign){
      if(sign){
        if(abs_comparison(value, a.value)){
          value = subtraction(a.value, value);
          sign = 0;
        }else{
          value = subtraction(value, a.value);
        }
      }else{
        if(!abs_comparison(a.value, value)){
          value = subtraction(a.value, value);
          sign = 1;
        }else{
          value = subtraction(value, a.value);
        }
      }
    }else{
      value = addition(value, a.value);
    }
    return *this;
  }

  BigInteger& operator-=(const BigInteger& a) {
    *this += (-a);
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
};

void Verify(){
  /*
    Verify with Library Checker (Addition of Big Integers)
      https://judge.yosupo.jp/problem/addition_of_big_integers
   */

  //Input
  int T; cin >> T;

  //Solve
  while(T--){
    string A, B; cin>> A >> B;
    BigInteger a(A);
    a += BigInteger(B);
    a.print_val();
  }
}

int main(){
  //Verify(); //Addition
  string x = "100";
  string y = "48";
  BigInteger X(x), Y(y);
  (X+Y).print_val();
  (X-Y).print_val();
  return 0;
}