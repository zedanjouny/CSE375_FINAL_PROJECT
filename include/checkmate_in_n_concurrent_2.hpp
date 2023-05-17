#include <libchess/position.hpp>
#include <iostream>
#include <thread>
#include <tbb/tbb.h>

using namespace std;
using namespace libchess;
using namespace tbb;

class checkmate_in_n_concurrent_2 {
    Position pos;
    int threads_size;
    atomic<bool> checkmate_found;
    int maxdepth;

public:
    // Constructor initializing position, thread size, and checkmate-related variables
    checkmate_in_n_concurrent_2(Position pos, int threads_size)
        : pos(pos), threads_size(threads_size), checkmate_found(false), maxdepth(-1) {}

    // Main function to find the answer
    bool findAnswer(int depth) {
        auto moves = this->pos.legal_moves();
        maxdepth = depth;
        vector<Position> ps(moves.size());

        // Create temporary positions
        for (int i = 0; i < moves.size(); i++) {
            Position t(this->pos.get_fen());
            t.makemove(moves[i]);
            ps[i] = t;
        }

        vector<thread> threads(threads_size);

        // Spawn multiple threads to perform the work concurrently
        for (int i = 0; i < threads.size(); i++) {
            int ending_index = (i + 1) * (ps.size() / threads_size);
            if (i == threads.size() - 1) {
                ending_index = ps.size();
            }
            threads[i] = thread(&checkmate_in_n_concurrent_2::do_work, this, i * (ps.size() / threads_size), ending_index, ps, depth, i);
        }

        // Wait for all threads to finish
        for (int i = 0; i < threads.size(); i++) {
            threads[i].join();
        }

        // Return the value of checkmate_found
        return checkmate_found.load(memory_order_acquire);
    }

    // Worker function for each thread
    void do_work(int starting_index, int ending_index, vector<Position> ps, int depth, int thread_index) {
        for (int i = starting_index; i < ending_index; i++) {
            _opponentMove(depth, ps[i]);
        }
    }

    // Attacker move function (the party attempting to perform forced checkmate)
    bool _answerMove(int depth, Position p) {
        if (checkmate_found.load(memory_order_relaxed)) {
            return true;
        }
        auto moves = p.legal_moves();

        for (const auto &move : moves) {
            Position temp(p.get_fen());
            temp.makemove(move);
            bool found = _opponentMove(depth, temp);

            if (found) {
                return true; // If the defender cannot escape the checkmate, then the attacker wins
            }
        }
        return false;
    }

    // Defender move function
    bool _opponentMove(int depth, Position p) {
        if (checkmate_found.load(memory_order_relaxed)) {
            return true;
        }
        auto moves = p.legal_moves();

        if (moves.size() == 0) { // No moves left, return either checkmate (true) or stalemate (false)
            return p.is_checkmate();
        } else if (depth == 1) {
            return false;
        }

        for (const auto &move : moves) {
            Position temp(p.get_fen());
            temp.makemove(move);
            bool found = _answerMove(depth - 1, temp);

            if (!found) { // All need to be true in order to pass the for loop, if one is false, then the defender can escape the checkmate
                return false;
            }
        }

        if (depth == maxdepth) {
            checkmate_found.store(true, memory_order_relaxed);
        }
        return true;
    }
};
