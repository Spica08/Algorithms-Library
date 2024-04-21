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

struct Eratosthenes{
  int N;
  vector<int> min_f;
  vector<int> prime;
  
  Eratosthenes(int N) : N(N){min_f.assign(N, 1000000000);}

  void build(){
    min_f[0] = 1;
    min_f[1] = 1;
    for (int i = 2; i < N; i++) {
      for (int j = 2; i * j < N; j++) {
        min_f[i * j] = min(i, min_f[i * j]);
      }
    }
    for (int i = 0; i < N; i++) {
      if (min_f[i] != inf) continue;
      prime.push_back(i);
    }
  }
};

int main(){
  Eratosthenes e(100);
  e.build();
  for(auto v:e.prime)cout<<v<<endl;
  return 0;
}