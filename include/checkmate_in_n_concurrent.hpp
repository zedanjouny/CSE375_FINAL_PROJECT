#include <libchess/position.hpp>
// #include <answer_concurrent.hpp>
#include <tbb/task_group.h>

using namespace std;
using namespace libchess;
using namespace tbb;

class checkmate_in_n_concurrent{
    Position pos;

    public:
        checkmate_in_n_concurrent(Position pos) {
            this->pos = pos;
        }
        
        bool findAnswer(int depth) {
            task_group g;
            return _answerMove(depth, g);
        }

        bool _answerMove(int depth, task_group &g) {
            auto moves = this->pos.legal_moves();
            bool found = false;
            for(const auto &move : moves){
                g.run([&]() {
                this->pos.makemove(move);
                if (!_opponentMove(depth, g)) {
                    this->pos.undomove();
                } else {
                    found = true;
                    g.cancel(); // stop executing other sub-tasks
                }
                });
            }
            g.wait();
            return found;
        }

        bool _opponentMove(int depth, task_group &g) {
            auto moves = this->pos.legal_moves();
            if (moves.size() == 0) {
                return this->pos.is_checkmate();
            } else if (depth == 1) {
                return false;
            }
            bool found = true;
            for (const auto &move : moves) {
                g.run([&]() {
                    this->pos.makemove(move);
                    if (!_answerMove(depth - 1, g)) {
                        this->pos.undomove();
                    } else {
                        // answer->putAnswer(move, *next);
                    }
                    found &= found; // combine results from sub-tasks
                });
            }
            g.wait(); // wait for all sub-tasks to complete
            return found;
        }
};