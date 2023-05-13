#include <libchess/position.hpp>

using namespace std;
using namespace libchess;

class checkmate_in_n_modified{
    Position pos;

    public:
        checkmate_in_n_modified(Position pos) {
            this->pos = pos;
        }

        bool findAnswer(int depth) {
            return _answerMove(depth, this->pos);
        }
  
        bool _answerMove(int depth, Position p) {
            auto moves = p.legal_moves();
            for(const auto &move : moves){
                Position temp = p;
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