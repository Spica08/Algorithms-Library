#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> // int or long long 
struct RangeSet{
  const T INF = numeric_limits<T>::max();
  T sum = 0;
  set<pair<T,T>> s;
  RangeSet(){
    s.emplace(INF, INF);
    s.emplace(-INF, -INF);
  }
  //[l, r] covered ?
  bool covered(T l, T r){
    assert(l<=r);
    auto itr = prev(s.lower_bound({l+1, l+1}));
    return (itr->first<=l) && (r<=itr->second);
  }
  //insert [l, r]
  T insert(T l, T r){
    assert(l<=r);
    auto itr = prev(s.lower_bound({l+1, l+1}));
    if((itr->first<=l) && (r<=itr->second)) return T(0);
    T sum_erased = 0;
    if((itr->first<=l) && (l<=itr->second+1)){
      l = itr->first;
      sum_erased += itr->second - itr->first + 1;
      itr = s.erase(itr);
    }else{
      itr = next(itr);
    }
    while(r > itr->second){
      sum_erased += itr->second - itr->first + 1;
      itr = s.erase(itr);
    }
    if((itr->first-1<=r) && (r<=itr->second)){
      r = itr->second;
      sum_erased += itr->second - itr->first + 1;
      itr = s.erase(itr);
    }
    s.insert({l, r});
    return r - l + 1 - sum_erased;
  }
  //erase [l, r]
  T erase(T l, T r){
    assert(l<=r);
    auto itr = prev(s.lower_bound({l+1, l+1}));
    if((itr->first<=l) && (r<=itr->second)){
      T nl = itr->first;
      T nr = itr->second;
      s.erase(itr);
      if (nl<=l-1) s.insert({nl, l-1});
      if (r+1<=nr) s.insert({r+1, nr});
      return (r - l + 1);
    }
    T ret = 0;
    if((itr->first<=l) && (l<=itr->second)){
      ret += itr->second - l + 1;
      if (itr->first<=l-1) s.insert({itr->first, l-1});
      itr = s.erase(itr);
    }else{
      itr = next(itr);
    }
    while(r <= itr->second){
      ret += itr->second - itr->first + 1;
      itr = s.erase(itr);
    }
    if((itr->first<=r) && (r<=itr->second)){
      ret += r - itr->first + 1;
      if (r+1<=itr->second) s.insert({r+1, itr->second});
      itr = s.erase(itr);
    }
    return ret;
  }
  //number of range
  int size(){return int(s.size())-2;}
  // return mex
  T mex(T x = 0){
    auto itr = prev(s.lower_bound({x+1, x+1}));
		if(itr->first <= x and x <= itr->second) return itr->second + 1;
		else return x;
  }
};

void Verify(){
  /*
    Verify with ABC330-E (Mex and Update)
      https://atcoder.jp/contests/abc330/tasks/abc330_e
   */

  //Input
  int N,Q; cin >> N >> Q;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin>>A[i];
  map<int,int> m;
  RangeSet<int> rs;
  for (int i = 0; i < N; i++) {
    m[A[i]]++;
    rs.insert(A[i],A[i]);
  }

  //Solve
  while(Q--){
    int i,x; cin >> i >> x;
    i--;
    m[A[i]]--;
    if(m[A[i]] == 0) rs.erase(A[i],A[i]);
    A[i] = x;
    m[x]++;
    rs.insert(x,x);
    cout << rs.mex() << endl;
  }
}

int main(){
  Verify();
  return 0;
}