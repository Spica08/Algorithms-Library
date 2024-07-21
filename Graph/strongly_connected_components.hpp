#ifndef STRINGLT_CONNECTED_COMPONENTS_HPP
#define STRINGLT_CONNECTED_COMPONENTS_HPP

#include "../Utility/templete.hpp"
#include "../Graph/graph_templete.hpp"

class StrongConnectedComponents {
  public:
    int n;
    UnweightedGraph G, rG;

    StrongConnectedComponents(UnweightedGraph &g) : 
      n(g.size()), G(n), rG(n), component_(n, -1), seen_(n){
      for(int i = 0; i < n; i++){
        for(auto e : g[i]){
          G.add_edge(i, e, 1, 1);
          rG.add_edge(e, i, 1, 1);
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
    void rebuild(UnweightedGraph &nG, std::vector<int> &s){
      int N = 0;
      for (int c : component_) N = std::max(N, c + 1);
      nG = UnweightedGraph(N);
      s.assign(N, 0);
      std::set<std::pair<int, int>> connected; //多重辺を管理
      //グラフ再構築
      for (int u = 0; u < n; u++) {
        for (auto v : G[u]) {
          int x = component_[u];
          int y = component_[v];
          if(x == y)continue;
          if(connected.count({x, y})) continue;
          connected.emplace(x, y);
          nG.add_edge(x, y, 1, 1);
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
        if(seen_[e]) continue;
        dfs(e);
      }
      order_.push_back(n);
    }

    void rdfs(int n, int cnt){
      component_[n] = cnt;
      for(auto e : rG[n]){
        if(component_[e] != -1) continue;
        rdfs(e, cnt);
      }
    }
};

#endif //STRINGLT_CONNECTED_COMPONENTS_HPP