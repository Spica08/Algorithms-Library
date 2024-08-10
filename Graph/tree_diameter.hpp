#ifndef TREE_DIAMETER_HPP
#define TREE_DIAMETER_HPP

#include "../Utility/templete.hpp"
#include "../Graph/graph_templete.hpp"

// G : WeightedGraph
// T : int or ling long
template<typename Graph, typename T>
class TreeDiameter{
  public:
    T diameter;
    std::vector<int> path;
    TreeDiameter(Graph &G) : G_(G){
      std::pair<T, int> ft = dfs_(0, -1);
      std::pair<T, int> st = dfs_(ft.second, -1);

      diameter = st.first;
      find_path_(st.second, ft.second, -1, path);
    }

  private:
    Graph G_;
    std::pair<T, int> dfs_(int v, int p){
      std::pair<T, int> d = std::make_pair(0, v);
      for(auto e : G_[v]){
        if(e.to == p) continue;
        std::pair<T, int> nc = dfs_(e.to, v);
        nc.first += e.cost;
        d = max(d, nc);
      }
      return d;
    }
    bool find_path_(int s, int g, int p, std::vector<int> &path){
      if(s == g) { path.push_back(s); return true; }
      for(auto e : G_[s]){
        if(e.to == p) continue;
        if(find_path_(e.to, g, s, path)){
          path.push_back(s);
          return true;
        }
      }
      return false;
    }
};

#endif //TREE_DIAMETER_HPP