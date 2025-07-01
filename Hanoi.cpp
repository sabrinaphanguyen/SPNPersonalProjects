// Student ID: 20470614

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Hanoi.h"

using namespace std;

std::string Hanoi::lookup_moves(int num_discs, int src, int dst) const {

   if (signed(_cache.size()) < num_discs + 1 ||
      signed(_cache[num_discs].size()) < src + 1 ||
      signed(_cache[num_discs][src].size()) < dst + 1) {
      return "";
   }

   if (_cache[num_discs][src][dst] != "") {
      return _cache[num_discs][src][dst];
   }

   return "";
}

std::string Hanoi::get_moves(int num_discs, int src, int dst, int tmp) {

   string look_up = lookup_moves(num_discs, src, dst);

   if (look_up != "") {
      return look_up;
   }

   string output = "";
   
   if (num_discs == 1) {
      output += to_string(src) + "->" + to_string(dst) + "\n";

   }
   else if (num_discs == 0) {

   }
   else {
      output += get_moves(num_discs - 1, src, tmp, dst);
      output += to_string(src) + "->" + to_string(dst) + "\n";
      output += get_moves(num_discs - 1, tmp, dst, src);
      _cache[num_discs - 1].clear();
   }

   create_vect(num_discs, src, dst);

   _cache[num_discs][src][dst] = output;

   return output;
}

std::string Hanoi::solve(int num_discs, int src, int dst, int tmp) {

   _num_discs = num_discs;
   _num_poles = 3;

   string output = "# Below, 'A->B' means 'move the top disc on pole A to pole B'\n";
   output += get_moves(num_discs, src, dst, tmp);



   for (int i = 0; i < signed(_cache.size()); i++) { // type everything in cache
      for (int j = 0; j < signed(_cache[i].size()); j++) {
         for (int k = 0; k < signed(_cache[i][j].size()); k++) {
            cout << "_cache["+to_string(i) + "][" + to_string(j) + "][" + to_string(k) + "] = " + _cache[i][j][k] + "\n";
         }
      }
   }

   return output;
}

void Hanoi::create_vect(int num_discs, int src, int dst) {
   if (signed(_cache.size()) < num_discs + 1)
      _cache.resize(num_discs + 1);

   if (signed(_cache[num_discs].size()) < src + 1)
      _cache[num_discs].resize(src + 1);

   if (signed(_cache[num_discs][src].size()) < dst + 1)
      _cache[num_discs][src].resize(dst+1);
}
