#include <libchess/move.hpp>
#include <map>

using namespace std;
using namespace libchess;

class Answer {
    Move answerMove;
    map<Move, Answer> nextAnswer;

    public:
        Answer() {}

        Move getAnswerMove() {
            return this->answerMove;
        }

        void setAnswerMove(Move move) {
            this->answerMove = move;
        }

        void setNextAnswer(map<Move, Answer> nextAnswer) {
            this->nextAnswer = nextAnswer;
        }

        map<Move, Answer> getAnswers() {
            return nextAnswer;
        }

        void putAnswer(Move move, Answer answer) {
            nextAnswer[move] = answer;
        }

        Answer getNextAnswer(Move move) {
            return nextAnswer[move];
        }

        bool end() {
            return nextAnswer.empty();
        }
};