#ifndef MAXFLOW_FORDFULKERSON
#define MAXFLOW_FORDFULKERSON

#include "../Utility/templete.hpp"
#include "../Graph/graph_templete.hpp"

class MaxFlow{
  public:
    struct E{
      int cap, rev_edge_id;
    };
    struct ES{
      int from, to, cap, flow;
    };

    MaxFlow(int N) : N_(N), G_(N){ used_.assign(N, 0);}

    void add_edge(int u, int v, int w, int zero_indexed = 0, int directed = 1){
      int IsForward = 1;
      int u_vID = G_[u].size();
      int v_uID = G_[v].size();
      G_.add_edge(u, v, IsForward, E{w, v_uID}, zero_indexed, directed); // forward_edge
      G_.add_edge(v, u, IsForward ^ 1, E{0, u_vID}, zero_indexed, directed); // reverse_edge
    }

    int maxflow(int s, int t){
      int res = 0;
      while(true){
        used_.assign(N_, 0);
        int flow = dfs(s, t, inf);
        if(flow == 0) break;
        res += flow;
      }
      return res;
    }

    std::vector<ES> get_edges(){
      std::vector<ES> res;
      for (int i = 0; i < N_; i++) {
        for(auto e : G_[i]){
          if(e.id == 0)continue; //IsFoward
          res.push_back({i, e.to, e.cost.cap + G_[e.to][e.cost.rev_edge_id].cost.cap, G_[e.to][e.cost.rev_edge_id].cost.cap});
        }
      }
      return res;
    }

  private:
    int N_;
    std::vector<int> used_;
    WeightedGraph<E> G_;

    int dfs(int pos, int goal, int F){
      if(pos == goal) return F;
      used_[pos] = 1;
      for(auto &e : G_[pos]){
        if(e.cost.cap == 0 || used_[e.to])continue;
        int flow = dfs(e.to, goal, std::min(F, e.cost.cap));
        if(flow){
          e.cost.cap -= flow;
          G_[e.to][e.cost.rev_edge_id].cost.cap += flow;
          return flow;
        }
      }
      return 0;
    }
};

#endif //MAXFLOW_FORDFULKERSON