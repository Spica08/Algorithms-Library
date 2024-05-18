#include <bits/stdc++.h>
using namespace std;

// int or long long
template <typename T>
struct Compress{
  vector<T> A;
  vector<T> reconstruct;

  Compress(vector<T> C) : A(C), reconstruct(C.size()+10){
    vector<T> vals = A;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < A.size(); i++) {
      T b = A[i];
      A[i] = lower_bound(vals.begin(), vals.end(), A[i]) - vals.begin();
      reconstruct[A[i]] = b;
    }
  };

  const T& operator[](int i)const{return reconstruct[i];};
};

void Verify(){
  /*
    Verify with ABC036-C (座圧)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
   */

  //Input
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  
  //Build
  Compress<int> comp(A);
  
  //Solve
  for(auto a : comp.A) cout << a << endl;
}

int main() { 
  Verify();
  return 0; 
}