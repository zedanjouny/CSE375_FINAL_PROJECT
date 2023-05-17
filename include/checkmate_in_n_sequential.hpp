#include <libchess/position.hpp>

using namespace std;
using namespace libchess;

class checkmate_in_n{
    Position pos;

    public:
        checkmate_in_n(Position pos) {
            this->pos = pos;
        }
        // checkmate finding function, calls answer move first assuming the attacker is moving first
        bool findAnswer(int depth) {
            return _answerMove(depth);
        }
        // attacker move function (the party attempting to perform forced checkmate)
        bool _answerMove(int depth) {
            auto moves = this->pos.legal_moves();
            for(const auto &move : moves){
                this->pos.makemove(move); // making the move
                bool found = _opponentMove(depth);
                this->pos.undomove(); // using one position board and undoing moves instead of copying the board
                if(found) { // at least one possible sequence of moves for attacker needs to result in a checkmate
                    return true; // if the defender cannot escape the checkmate, then the attacker wins
                }
            }
            return false;
        }
        // defender move function
        bool _opponentMove(int depth) {
            auto moves = this->pos.legal_moves();
            if (moves.size() == 0) { // no moves left, return either checkmate (true) or stalemate (false)
                return this->pos.is_checkmate();
            } else if (depth == 1) {
                return false;
            }
            for(const auto &move : moves){
                this->pos.makemove(move);
                bool found = _answerMove(depth-1);
                this->pos.undomove();
                if (!found) { // all need to be true in order to pass the for loop, if 
                // one is false, then the defender can escape the checkmate
                    return false;
                }
            }
            return true;
        }
};