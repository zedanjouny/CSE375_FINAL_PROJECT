#include <libchess/position.hpp>

using namespace std;
using namespace libchess;

class checkmate_in_n_modified {
    Position pos;

public:
    checkmate_in_n_modified(Position pos) {
        this->pos = pos;
    }

    // Checkmate finding function, calls _answerMove first assuming the attacker is moving first
    bool findAnswer(int depth) {
        return _answerMove(depth, this->pos);
    }

    // Attacker move function (the party attempting to perform forced checkmate)
    bool _answerMove(int depth, Position p) {
        auto moves = p.legal_moves();

        for (const auto &move : moves) {
            Position temp = p;
            temp.makemove(move); // Making the move on a temporary position
            bool found = _opponentMove(depth, temp);

            if (found) {
                return true; // If the defender cannot escape the checkmate, then the attacker wins
            }
        }
        return false;
    }

    // Defender move function
    bool _opponentMove(int depth, Position p) {
        auto moves = p.legal_moves();

        if (moves.size() == 0) { // No moves left, return either checkmate (true) or stalemate (false)
            return p.is_checkmate();
        } else if (depth == 1) {
            return false;
        }

        for (const auto &move : moves) {
            Position temp = p;
            temp.makemove(move); // Making the move on a temporary position
            bool found = _answerMove(depth - 1, temp);

            if (!found) { // All need to be true in order to pass the for loop, if one is false, then the defender can escape the checkmate
                return false;
            }
        }
        return true;
    }
};
