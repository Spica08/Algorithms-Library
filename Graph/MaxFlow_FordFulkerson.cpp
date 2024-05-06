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

struct MaxFlow{
  int N;
  vector<int> used;
  struct E{
    int w, rev;
    E(int w, int rev): w(w), rev(rev){}
  };
  struct ES{
    int from, to, w, flow;
    ES(int from, int to, int w, int flow): from(from), to(to), w(w), flow(flow) {}
  };
  WeightedGraph<E> G;

  MaxFlow(int N) : N(N), G(N){
    used.assign(N, 0);
  }

  void add_edge(int u, int v, int id, int w, int zero_indexed = 0, int directed = 1){
    int u_vID = G[u].size();
    int v_uID = G[v].size();
    G.add_edge(u, v, id, E(w, v_uID), zero_indexed, directed);
    G.add_edge(v, u, id^1, E(0, u_vID), zero_indexed, directed);
  }

  int dfs(int pos, int goal, int F){
    if(pos == goal) return F;
    used[pos] = 1;

    for(auto &e : G.G[pos]){
      if(e.cost.w == 0 or used[e.to])continue;
      int flow = dfs(e.to, goal, min(F, e.cost.w));
      if(flow){
        e.cost.w -= flow;
        G.G[e.to][e.cost.rev].cost.w += flow;
        return flow;
      }
    }
    return 0;
  }

  int maxflow(int s, int t){
    int res = 0;
    while(true){
      used.assign(N, 0);
      int flow = dfs(s, t, inf);
      if(flow == 0) break;
      res += flow;
    }
    return res;
  }

  vector<ES> get_edges(){
    vector<ES> res;
    for (int i = 0; i < N; i++) {
      for(auto e : G[i]){
        if(!e.id)continue;
        res.push_back({i, e.to, e.cost.w + G[e.to][e.cost.rev].cost.w, G[e.to][e.cost.rev].cost.w});
      }
    }
    return res;
  }
};

void Verify_1(){
  /*
    Verify with AOJ (Maximum Flow)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
   */

  //Input
  int N, M; cin >> N >> M;
  
  //Build
  MaxFlow mf(N);
  for (int i = 0; i < M; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    mf.add_edge(u, v, 1, c, 1, 1);
  }
  
  //Solve
  cout<<mf.maxflow(0, N - 1)<<endl;
}

void Verify_2(){
  /*
    Verify with ALPC-D (Maxflow)
      https://atcoder.jp/contests/practice2/tasks/practice2_d
   */

  //Input
  int N, M; cin >> N >> M;
  vector<string> G(N);
  for (int i = 0; i < N; i++) cin >> G[i];

  //Build (add edge)
  MaxFlow mf(N * M + 2);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if(G[i][j] == '#')continue;
      for (int d = 0; d < 4; d++) {
        int ni = i + dx[d];
        int nj = j + dy[d];
        if(ni < 0 || ni >= N || nj < 0 || nj >= M)continue;
        if(G[ni][nj] == '#')continue;
        if((i + j) & 1) continue;
        mf.add_edge(i * M + j, ni * M + nj, 1, 1, 1, 1);
      }
      if((i + j) & 1) mf.add_edge(i * M + j, N * M + 1, 1, 1, 1, 1);
      else mf.add_edge(N * M, i * M + j, 1, 1, 1, 1);
    }
  }
  //Solve
  int cnt = mf.maxflow(N * M, N * M + 1);
  auto ans = mf.get_edges();
  for(auto a : ans){
    if(a.from == N * M || a.to == N * M + 1) continue;
    if(a.flow){
      int ifrom = a.from / M, jfrom = a.from % M;
      int ito = a.to / M, jto = a.to % M;
      if(ifrom == ito){
        if (jfrom > jto) swap(jfrom, jto);
        G[ifrom][jfrom] = '>';
        G[ito][jto] = '<';
      }else if(jfrom == jto){
        if (ifrom > ito) swap(ifrom, ito);
        G[ifrom][jfrom] = 'v';
        G[ito][jto] = '^';
      }
    }
  }
  cout<<cnt<<endl;
  for(auto g:G) cout<<g<<endl;
}

int main(){
  Verify_1(); //Maximum Flow
  Verify_2(); //Matching on bibartite graph
  return 0;
}