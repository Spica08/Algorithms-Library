#ifndef RANDOM_TEMPLETE_HPP
#define RANDOM_TEMPLETE_HPP

#include "../Utility/templete.hpp"
#include <random>

std::random_device seed_gen;
std::mt19937 engine(seed_gen());
std::mt19937 engine_fixed(0);

template<typename T>
T GenerateRandInt(T min, T max, bool fixed = false){
  std::uniform_int_distribution<T> gen(min, max);
  return (fixed ? gen(engine_fixed) : gen(engine));
}

#endif //RANDOM_TEMPLETE_HPP