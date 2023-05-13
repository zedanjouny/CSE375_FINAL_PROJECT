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
    atomic<bool> check_mate_found;

public:
    checkmate_in_n_concurrent(Position pos)
        : pos(pos), check_mate_found(false) {}

    bool findAnswer(int depth) {
        return _answerMove(depth, this->pos);
    }

    bool _answerMove(int depth, Position p) {
        if (check_mate_found.load(memory_order_acquire)) {
            return false;
        }

        auto moves = p.legal_moves();
        task_group tg;

        for (const auto &move : moves) {
            if (check_mate_found.load(memory_order_acquire)) {
                break;
            }

            tg.run([&, move]() {
                Position temp = p;
                temp.makemove(move);
                bool found = _opponentMove(depth, temp);
                if (found) {
                    bool expected = false;
                    check_mate_found.compare_exchange_strong(expected, true, memory_order_acq_rel);
                }
            });
        }

        tg.wait();
        return check_mate_found.load(memory_order_acquire);
    }

    bool _opponentMove(int depth, Position p) {
        if (check_mate_found.load(memory_order_acquire)) {
            return false;
        }

        auto moves = p.legal_moves();
        if (moves.size() == 0) { // no moves left -> checkmate
            if (p.is_checkmate()) {
                return true;
            } else {
                cout << "Error on calling checkmate step\n";
            }
        } else if (depth == 1) {
            return false;
        }
        for (const auto &move : moves) {
            if (check_mate_found.load(memory_order_acquire)) {
                break;
            }

            Position temp = p;
            temp.makemove(move);
            bool found = _answerMove(depth - 1, temp);
            if (!found) {
                return false;
            }
        }
        cout << "Not supposed to reach here ever\n"; // for concurrent version it is reaching this print statement 
        // due to skips within the for loop once the checkmate has been found
        // need more testing sets to prove/disprove the algorithm works
        return true;
    }
};
