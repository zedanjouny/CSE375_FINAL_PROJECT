#include <libchess/position.hpp>
#include <answer_sequential.hpp>

using namespace std;
using namespace libchess;

class checkmate_in_n{
    Position pos;

    public:
        checkmate_in_n(Position pos) {
            this->pos = pos;
        }

        Answer findAnswer(int depth) {
            Answer *answer = new Answer();
            _answerMove(answer, depth);
            return *answer;
        }

        
        bool _answerMove(Answer *answer, int depth) {
            auto moves = this->pos.legal_moves();
            for(const auto &move : moves){
                this->pos.makemove(move);
                bool found = _opponentMove(answer, depth);
                this->pos.undomove();
                if(found)
                {
                    answer->setAnswerMove(move);
                    return true;
                }
            }
            return false;
        }

        bool _opponentMove(Answer *answer, int depth) {
            auto moves = this->pos.legal_moves();
            if (moves.size() == 0) {
                return this->pos.is_checkmate();
            } else if (depth == 1) {
                return false;
            }
            for(const auto &move : moves){
                this->pos.makemove(move);
                Answer *next = new Answer();
                bool found = _answerMove(next, depth-1);
                this->pos.undomove();
                if (!found) {
                    return false;
                }
                answer->putAnswer(move, *next);
            }
            return true;
        }
};