#include <bits/stdc++.h>
using namespace std;

// string or vector
template<typename T>
struct Zalgorithm{
  T S;
  vector<int> Z;

  Zalgorithm(T S) : S(S){
    int N = S.size();
    Z.assign(N, 0);
    Z[0] = S.size();
    int from = 0, last = 0;
    for (int i = 1; i < N; i++) {
      int d = (last < i ? 0 : min(Z[i - from], last - i));
      while (i + d < N && S[d] == S[i + d]) d++;
      Z[i] = d;
      if (last < i + d) {
        from = i;
        last = i + d;
      }
    }
  }
};

void Verify_1(){
  /*
    Verify with Library Checker (Z Algorithm)
      https://judge.yosupo.jp/problem/zalgorithm
   */

  //Input
  string S; cin >> S;

  //Build
  Zalgorithm<string> zalgo(S);

  //Solve
  for (int i = 0; i < zalgo.Z.size(); i++) {
    cout << zalgo.Z[i] << " \n"[i == zalgo.Z.size() - 1];
  }
}

void Verify_2(){
  /*
    Verify with AOJ (String Search)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
   */

  //Input
  string T, P; cin >> T >> P;

  //Build
  string M = P + '.' + T;
  Zalgorithm<string> zalgo(M);

  //Solve
  for (int i = 0; i < T.size(); i++) {
    if(zalgo.Z[i + P.size() + 1] >= P.size()){
      cout << i << endl;
    }
  }
}

int main() {
  Verify_1();
  Verify_2();
  return 0;
}