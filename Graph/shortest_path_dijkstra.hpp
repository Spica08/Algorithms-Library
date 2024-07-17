#ifndef SHORTEST_PATH_DIJKSTRA_HPP
#define SHORTEST_PATH_DIJKSTRA_HPP

#include "../Utility/templete.hpp"
#include "../Graph/graph_templete.hpp"

template<typename S, typename T>
class Dijkstra{
  public:
    std::vector<S> dist;
    Dijkstra(WeightedGraph<T> &G, int s, S nan, std::function<S(S, T)> d)
      :nan_(nan), prev_(G.size(), -1), dist(G.size(), nan), d_(d){
      std::priority_queue<std::pair<S, int>, std::vector<std::pair<S, int>>, std::greater<std::pair<S, int>>> pq;
      dist[s] = 0;
      pq.emplace(dist[s], s);
      while (!pq.empty()) {
        std::pair<S, int> p = pq.top(); pq.pop();
        int v = p.second;
        S cost = p.first;
        if (dist[v] < cost) continue;
        for (auto next_v : G[v]) {
          if (d(dist[v], next_v.cost) < dist[next_v.to]) {
            dist[next_v.to] = d(dist[v], next_v.cost);
            prev_[next_v.to] = v;
            pq.emplace(dist[next_v.to], next_v.to);
          }
        }
      }
    }
    // reconstruct the shortest path
    std::vector<int> Reconstruct(int g){
      std::vector<int> res;
      int cur = g;
      do{
        res.push_back(cur);
        cur = prev_[cur];
      }while(cur != -1);
      std::reverse(res.begin(), res.end());
      return res;
    }
  private:
    S nan_;
    std::vector<int> prev_;
    std::function<S(S, T)> d_;
};

#endif //SHORTEST_PATH_DIJKSTRA_HPP