#include <libchess/position.hpp>

using namespace std;
using namespace libchess;

class checkmate_in_n{
    Position pos;

    public:
        checkmate_in_n(Position pos) {
            this->pos = pos;
        }

        bool findAnswer(int depth) {
            return _answerMove(depth);
        }
  
        bool _answerMove(int depth) {
            auto moves = this->pos.legal_moves();
            for(const auto &move : moves){
                this->pos.makemove(move);
                bool found = _opponentMove(depth);
                this->pos.undomove();
                if(found)
                {
                    return true;
                }
            }
            return false;
        }

        bool _opponentMove(int depth) {
            auto moves = this->pos.legal_moves();
            if (moves.size() == 0) {
                return this->pos.is_checkmate();
            } else if (depth == 1) {
                return false;
            }
            for(const auto &move : moves){
                this->pos.makemove(move);
                bool found = _answerMove(depth-1);
                this->pos.undomove();
                if (!found) {
                    return false;
                }
            }
            return true;
        }
};