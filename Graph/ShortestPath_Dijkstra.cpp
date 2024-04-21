#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1000000000000000000;

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

template<typename S, typename T>
struct Dijkstra{
  S nan;
  vector<int> prev;
  vector<S> dist;
  function<S(S, T)> d;
  Dijkstra(WeightedGraph<T> &G, int s, S nan, function<S(S, T)> d)
    :nan(nan), prev(G.size(), -1), dist(G.size(), nan), d(d){
    priority_queue<pair<S, int>, vector<pair<S, int>>, greater<pair<S, int>>> pq;
    dist[s] = 0;
    pq.emplace(dist[s],s);
    while (!pq.empty()) {
      pair<S, int> p = pq.top(); pq.pop();
      int v = p.second;
      S cost = p.first;
      if (dist[v] < cost) continue;
      for (auto next_v : G[v]) {
        if (d(dist[v], next_v.cost) < dist[next_v.to]) {
          dist[next_v.to] = d(dist[v], next_v.cost);
          prev[next_v.to] = v;
          pq.emplace(dist[next_v.to], next_v.to);
        }
      }
    }
  }
  // reconstruct the shortest path
  vector<int> Reconstruct(int g){
    vector<int> res(1,g);
    int cur = g;
    while (cur != -1) {
      cur = prev[cur];
      if (cur != -1) res.push_back(cur);
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

void Verify_1(){
  /*
    Verify with Library Checker (Shortest Path)
      https://judge.yosupo.jp/problem/shortest_path
   */

  //Input
  int N, M; cin >> N >> M;
  int s, t; cin >> s >> t;
  WeightedGraph<ll> G(N);
  for (int i = 0; i < M; i++) {
    int a, b; cin >> a >> b;
    ll c; cin >> c;
    G.add_edge(a, b, i, c, 1, 1);
  }

  //Solve
  ll nan = INF;
  auto d = [](ll a, ll b){return a + b;};
  Dijkstra<ll,ll> dijk(G, s, nan, d);
  if(dijk.dist[t] == dijk.nan) cout << -1 << endl;
  else{
    vector<int> ans = dijk.Reconstruct(t);
    cout << dijk.dist[t] << " " << ans.size() - 1 << endl;
    for (int i = 0; i < ans.size() - 1; i++) {
      cout << ans[i] << " " << ans[i+1] <<endl;
    }
  }
}

void Verify_2(){
  /*
    Verify with ABC192-E (Train)
      https://atcoder.jp/contests/abc192/tasks/abc192_e
   */

  //Input
  int N, M, X, Y;
  cin >> N >> M >> X >> Y;
  X--; Y--;
  struct Cost{
    ll t, k;
    Cost(ll t, ll k) : t(t), k(k){}
  };
  WeightedGraph<Cost> G(N);
  for (int i = 0; i < M; i++) {
    ll u, v, t, k;
    cin >> u >> v >> t >> k;
    G.add_edge(u, v, i, Cost(t,k), 0, 0);
  }
  
  //Solve
  ll nan = INF;
  auto d = [](ll a, Cost b){return (a + b.k - 1)/b.k * b.k + b.t;};
  Dijkstra<ll, Cost> dijk(G, X, nan, d);
  if (dijk.dist[Y] == nan) cout << -1 << endl;
  else cout << dijk.dist[Y] << endl;
}

int main(){
  Verify_1(); // Shortest Path
  Verify_2(); // Shortest Path with irregular cost
  return 0;
}