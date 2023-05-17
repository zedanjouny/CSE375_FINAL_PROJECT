#include <libchess/position.hpp>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include <atomic>
#include <iostream>

using namespace std;
using namespace libchess;
using namespace tbb;

class checkmate_in_n_concurrent_bfs {
    Position pos;

public:
    // Constructor initializing position
    checkmate_in_n_concurrent_bfs(Position pos)
        : pos(pos) {}

    // Main function to find the answer
    bool findAnswer(int depth) {
        return mateMove(depth, this->pos, 0);
    }

    // Recursive function to find the checkmate
    bool mateMove(int depth, Position p, int turn)
    {
        auto moves = p.legal_moves();

        if(turn == 1)
        {
            if (moves.size() == 0) {
                return p.is_checkmate();
            } else if (depth == 1) {
                return false;
            }
        }

        // Create an array of temporary positions using parallel_for
        Position ps[moves.size()];
        parallel_for(blocked_range<int>(0, moves.size()), [&](blocked_range<int> r) {
            for (int i = r.begin(); i < r.end(); ++i) {
                Position t(p.get_fen());
                t.makemove(moves[i]);
                ps[i] = t;
            }
        });

        if(turn == 0)
        {
            // Attacker's turn: iterate through temporary positions and call mateMove recursively with turn = 1
            for(int i = 0; i < moves.size(); i++)
            {
                bool found = mateMove(depth, ps[i], 1);
                if(found) {
                    return true;
                }
            }
            return false;
        }
        else
        {
            // Defender's turn: iterate through temporary positions and call mateMove recursively with turn = 0
            for(int i = 0; i < moves.size(); i++)
            {
                bool found = mateMove(depth - 1, ps[i], 0);
                if (!found) {
                    return false;
                }
            }
            return true;
        }
    }
};
