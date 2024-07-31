#include "../../Graph/maxflow_fordfulkerson.hpp"

void Verify_1(){
  /*
    Verified : with AOJ (Maximum Flow)
      https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
   */

  //Input
  int N, M; std::cin >> N >> M;
  
  //Build
  MaxFlow mf(N);
  for (int i = 0; i < M; i++) {
    int u, v, c;
    std::cin >> u >> v >> c;
    mf.add_edge(u, v, c, 1, 1);
  }
  
  //Solve
  std::cout << mf.maxflow(0, N - 1) << std::endl;
}

void Verify_2(){
  /*
    Verified : with ALPC-D (Maxflow)
      https://atcoder.jp/contests/practice2/tasks/practice2_d
   */

  //Input
  int N, M; std::cin >> N >> M;
  std::vector<std::string> G(N);
  for (int i = 0; i < N; i++) std::cin >> G[i];

  //Build (add edge)
  MaxFlow mf(N * M + 2);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if(G[i][j] == '#')continue;
      for (int d = 0; d < 4; d++) {
        int ni = i + dx[d];
        int nj = j + dy[d];
        if(ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
        if(G[ni][nj] == '#') continue;
        if((i + j) & 1) continue;
        mf.add_edge(i * M + j, ni * M + nj, 1, 1, 1);
      }
      if((i + j) & 1) mf.add_edge(i * M + j, N * M + 1, 1, 1, 1);
      else mf.add_edge(N * M, i * M + j, 1, 1, 1);
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
        if (jfrom > jto) std::swap(jfrom, jto);
        G[ifrom][jfrom] = '>';
        G[ito][jto] = '<';
      }else if(jfrom == jto){
        if (ifrom > ito) std::swap(ifrom, ito);
        G[ifrom][jfrom] = 'v';
        G[ito][jto] = '^';
      }
    }
  }
  std::cout << cnt << std::endl;
  for(auto g:G) std::cout << g << std::endl;
}

int main(){
  //Verify_1(); //Maximum Flow
  Verify_2(); //Matching on bibartite graph
  return 0;
}