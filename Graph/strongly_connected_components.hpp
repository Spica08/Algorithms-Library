#ifndef STRINGLT_CONNECTED_COMPONENTS_HPP
#define STRINGLT_CONNECTED_COMPONENTS_HPP

#include "../Utility/templete.hpp"
#include "../Graph/graph_templete.hpp"

// G : WeightedGraph
template<typename Graph>
class StrongConnectedComponents {
  public:
    int n;
    Graph G, rG;

    StrongConnectedComponents(Graph &g) : 
      n(g.size()), G(n), rG(n), component_(n, -1), seen_(n){
      for(int i = 0; i < n; i++){
        for(auto e : g[i]){
          G.add_edge(i, e.to, e.id, e.cost, 1, 1);
          rG.add_edge(e.to, i, e.id, e.cost, 1, 1);
        }
      }
      for (int i = 0; i < n; i++) {
        if (seen_[i])continue;
        dfs(i);
      }
      reverse(order_.begin(), order_.end());
      int cnt = 0;
      for (int i : order_) {
        if (component_[i] != -1)continue;
        rdfs(i, cnt);
        cnt++;
      }
    }

    // SCC後のグラフ再構築
    void rebuild(Graph &nG, std::vector<int> &s){
      int N = 0;
      for (int c : component_) N = std::max(N, c + 1);
      nG = Graph(N);
      s.assign(N, 0);
      std::set<std::pair<int, int>> connected; //多重辺を管理
      //グラフ再構築
      for (int u = 0; u < n; u++) {
        for (auto v : G[u]) {
          int x = component_[u];
          int y = component_[v.to];
          if(x == y)continue;
          if(connected.count({x, y})) continue;
          connected.emplace(x, y);
          nG.add_edge(x, y, v.id, v.cost, 1, 1);
        }
      }
      //各強連結成分のサイズ
      for (auto x : component_) s[x]++;
    }

    bool IsSame(int x, int y) {return component_[x] == component_[y];}
  private:
    std::vector<int> order_, component_, seen_;

    void dfs(int n){
      seen_[n] = 1;
      for(auto e : G[n]){
        if(seen_[e.to]) continue;
        dfs(e.to);
      }
      order_.push_back(n);
    }

    void rdfs(int n, int cnt){
      component_[n] = cnt;
      for(auto e : rG[n]){
        if(component_[e.to] != -1) continue;
        rdfs(e.to, cnt);
      }
    }
};

#endif //STRINGLT_CONNECTED_COMPONENTS_HPP