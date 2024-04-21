#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Edge{
  int from, to, id;
  T cost;
  Edge(int from, int to, int id, T cost):from(from), to(to), id(id), cost(cost){}
};

template<typename T>
struct WeightedGraph{
  int N;
  vector<vector<Edge<T>>> G;
  WeightedGraph(int N): N(N), G(N){}
  void add_edge(int u, int v, int id, T cost, int zero_indexed = 0, int directed = 0){
    if (!zero_indexed) {u--; v--;}
    G[u].emplace_back(u, v, id, cost);
    if(!directed)G[v].emplace_back(v, u, id, cost);
  }
  int size()const{return G.size();};
  const vector<Edge<T>>& operator[](int i)const{return G[i];};
};

struct UnweightedGraph{
  int N;
  vector<vector<int>> G;
  UnweightedGraph(int N): N(N), G(N){}
  void read_edge(int zero_indexed = 0, int directed = 0){
    int u, v; cin >> u >> v; 
    add_edge(u, v, zero_indexed, directed);
  }
  void add_edge(int u, int v, int zero_indexed = 0, int directed = 0){
    if (!zero_indexed) {u--; v--;}
    G[u].push_back(v);
    if(!directed)G[v].push_back(u);
  }
  int size()const{return G.size();};
  const vector<int>& operator[](int i)const{return G[i];};
};

int main(){
  return 0;
}