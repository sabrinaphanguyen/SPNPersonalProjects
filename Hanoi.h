//Hanoi header file
// Student ID: 20470614

#ifndef Hanoi_h
#define Hanoi_h
#include <string>
#include <sstream>
#include <vector>

using namespace std; 

class Hanoi {
private:
    int _num_poles;
    int _num_discs;

    // TODO: Declare the _cache member using an appropriate
    // level of nesting within std::vectors to put each string
    // of moves. You should be able to access the cache like so:
    //   _cache[num_discs][src][dst] = "move1\nmove2\n..."

    vector<vector<vector<string>>> _cache;

    std::string lookup_moves(int num_discs, int src, int dst) const;
    std::string get_moves(int num_discs, int src, int dst, int tmp);
    void create_vect(int _num_discs, int src, int dst);
public:
    // Use freebie default constructor
    std::string solve(int num_discs, int src, int dst, int tmp);
    friend class Tests; // Don't remove this line
};

#endif