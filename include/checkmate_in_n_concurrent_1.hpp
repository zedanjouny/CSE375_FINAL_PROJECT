#include <libchess/position.hpp>
#include <iostream>
#include <thread>

using namespace std;
using namespace libchess;
using namespace tbb;

class checkmate_in_n_concurrent_1 {
    Position pos;
    int threads_size;

public:
    // Constructor initializing position and checkmate flag
    checkmate_in_n_concurrent_1(Position pos, int threads_size)
        : pos(pos), threads_size(threads_size) {}


    void do_work(int starting_index, int ending_index, vector<Position> &ps, vector<bool> &founded, int depth, int thread_index)
    {
        for(int i = starting_index; i<ending_index; i++)
        {
            if(_answerMove(depth, ps[i]))
            {
                founded[i] = true;
                break;
            }
        }
    }

    // Main function to find the answer
    bool findAnswer(int depth) {
        auto moves = this->pos.legal_moves();
        vector<Position> ps(moves.size());
        parallel_for(blocked_range<int>(0,moves.size()), [&](blocked_range<int> r) {
            for (int i=r.begin(); i<r.end(); ++i)
            {
                Position t(this->pos.get_fen());
                t.makemove(moves[i]);
                ps[i] = t;
            }
        });
        vector<bool> founded(moves.size());
        vector<thread> threads(threads_size);
        for(int i = 0;i<threads.size();i++)
        {
            threads[i] = thread(&checkmate_in_n_concurrent_1::do_work, this, i * (ps.size()/threads_size), (i+1) * (moves.size()/threads_size), ref(ps), ref(founded), depth, i);
        }
        for(int i = 0;i<founded.size();i++)
        {
            if(founded[i])
            {
                return true;
            }
        }
        return false;
    }


    bool _answerMove(int depth, Position p) {
        auto moves = p.legal_moves();
        for(const auto &move : moves){
            Position temp(p.get_fen());
            temp.makemove(move);
            bool found = _opponentMove(depth, temp);
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
            Position temp(p.get_fen());
            temp.makemove(move);
            bool found = _answerMove(depth-1, temp);
            if (!found) {
                return false;
            }
        }
        return true;
    }
};
