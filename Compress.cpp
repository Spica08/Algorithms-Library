#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Graph = vector<vector<int>>;
using Grid = vector<vector<char>>;

template <typename T>
void compress(vector<T> &A) {
  vector<T> vals = A;
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  for (int i = 0; i < A.size(); i++) {
    A[i] = lower_bound(vals.begin(), vals.end(), A[i]) - vals.begin();
  }
}

int main() { return 0; }