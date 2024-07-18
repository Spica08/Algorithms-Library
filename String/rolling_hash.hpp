#ifndef ROLLING_HASH_HPP
#define ROLLING_HASH_HPP

#include "../Utility/templete.hpp"
#include "../Utility/random_templete.hpp"

//ref : https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
class RollingHash {
  public:
    std::string s;
    ull base;
    std::vector<ull> hashed, power;
    RollingHash(std::string s, ull base = GenerateRandInt<ull>(0, mod_hash - 1)) : s(s), base(base){
      int sz = (int)s.size();
      hashed.assign(sz+1, 0UL);
      power.assign(sz+1, 1UL);
      for (int i = 0; i < sz; i++) {
        power[i + 1] = CalcMod(Mul(power[i], base));
        hashed[i + 1] = CalcMod(Mul(hashed[i], base) + s[i]);
      }
    }

    // get hash of [l, r) (0-indexed)
    ull get(int l, int r){
      ull POSITIVIZER = mod_hash * 4;
      ull ret = CalcMod(hashed[r] + POSITIVIZER - Mul(hashed[l], power[r - l]));
      return ret;
    }
  private:
    ull CalcMod(ull x){
        ull xu = x >> 61;
        ull xd = x & mod_hash;
        ull res = xu + xd;
        if (res >= mod_hash) res -= mod_hash;
        return res;
    }

    ull Mul(ull a, ull b){
        ull au = a >> 31;
        ull ad = a & ((1UL << 31) - 1);
        ull bu = b >> 31;
        ull bd = b & ((1UL << 31) - 1);
        ull mid = ad * bu + au * bd;
        ull midu = mid >> 30;
        ull midd = mid & ((1UL << 30) - 1);
        return au * bu * 2 + midu + (midd << 31) + ad * bd;
    }
};

#endif //ROLLING_HASH_HPP