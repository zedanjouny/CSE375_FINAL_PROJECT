#include <libchess/position.hpp>
#include <tbb/task_group.h>
#include <tbb/tbb.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_invoke.h>
#include <atomic>
#include <iostream>

using namespace std;
using namespace libchess;
using namespace tbb;

class checkmate_in_n_concurrent {
    Position pos;
    atomic<bool> check_mate_found; // Flag to check if checkmate has been found

public:
    // Constructor initializing position and checkmate flag
    checkmate_in_n_concurrent(Position pos)
        : pos(pos), check_mate_found(false) {}

    // Main function to find the answer
    bool findAnswer(int depth) {
        return mateMove(depth, this->pos, 0);
    }

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
        Position ps[moves.size()];
        parallel_for(blocked_range<int>(0,moves.size()), [&](blocked_range<int> r) {
            for (int i=r.begin(); i<r.end(); ++i)
            {
                Position t(p.get_fen());
                t.makemove(moves[i]);
                ps[i] = t;
            }
        });
        if(turn == 0)
        {
            for(int i = 0;i<moves.size();i++)
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
            for(int i = 0;i<moves.size();i++)
            {
                bool found = mateMove(depth-1, ps[i], 0);
                if (!found) {
                    return false;
                }
            }
            return true;
        }
    }

    bool _answerMove(int depth, Position p) {
        auto moves = p.legal_moves();
        Position ps[moves.size()];
        parallel_for(blocked_range<int>(0,moves.size()), [&](blocked_range<int> r) {
            for (int i=r.begin(); i<r.end(); ++i)
            {
                Position t(p.get_fen());
                t.makemove(moves[i]);
                ps[i] = t;
            }
        });
        for(int i = 0;i<moves.size();i++)
        {
            bool found = _opponentMove(depth, ps[i]);
            if(found) {
                return true;
            }
        }
        return false;
    }

    bool _opponentMove(int depth, Position p) {
        auto moves = p.legal_moves();
        if (moves.size() == 0) {
            return p.is_checkmate();
        } else if (depth == 1) {
            return false;
        }
        for(const auto &move : moves){
            Position temp = p;
            temp.makemove(move);
            bool found = _answerMove(depth-1, temp);
            if (!found) {
                return false;
            }
        }
        return true;
    }
};
