#ifndef MINIMUM_SPANNING_TREE_KRUSKAL_HPP
#define MINIMUM_SPANNING_TREE_KRUSKAL_HPP

#include "../Graph/graph_templete.hpp"
#include "../DataStructure/union_find.hpp"

template<typename T>
class MinimumSpanningTree{
  public:
    T cost = 0;
    std::vector<Edge<T>> edges;
    std::vector<Edge<T>> mst_edges;

    MinimumSpanningTree(int N) : n_(N){};

    void add_edge(int u, int v, int id, T cost, int zero_indexed = 0){
      if (!zero_indexed) {u--; v--;}
      assert(u >= 0 && u < n_);
      assert(v >= 0 && v < n_);
      edges.emplace_back(u, v, id, cost);
    }

    //build MST (Kruskal)
    void build(){
      UnionFind uf(n_);
      std::sort(edges.begin(), edges.end(), [](Edge<T> &a, Edge<T> &b){return a.cost < b.cost;});
      for(auto e : edges){
        if (!uf.same(e.from, e.to)){
          uf.unite(e.from, e.to);
          mst_edges.push_back(e);
          cost += e.cost;
        }
      }
    }
  private:
    int n_;
};

#endif //MINIMUM_SPANNING_TREE_KRUSKAL_HPP