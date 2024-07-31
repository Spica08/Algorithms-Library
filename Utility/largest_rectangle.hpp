#ifndef LARGEST_RECTANGLE_HPP
#define LARGEST_RECTANGLE_HPP

#include "../Utility/templete.hpp"

template <typename T>
T LargestRectangle(std::vector<T> &H){
  int N = int(H.size());
  std::vector<T> hist(N + 2, 0);
  for(int i = 0; i < N; i++) hist[i + 1] = H[i];
  hist[0] = -inf;
  T maxarea = 0;
  std::stack<T> h;
  h.push(0);
  for(int i = 1; i <= N + 1; i++){
    while(hist[h.top()] >= hist[i]){
      T height = hist[h.top()];
      h.pop();
      maxarea = std::max<T>(maxarea, height * (i - h.top() - 1));
    }
    h.push(i);
  }
  return maxarea;
}

#endif //LARGEST_RECTANGLE_HPP