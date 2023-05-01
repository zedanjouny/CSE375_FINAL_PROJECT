#include "move.h"
#include <map>

using namespace std;

class Answer {
    move_t answerMove;
    map<move_t, Answer> nextAnswer;

    public:
        Answer() {}

        move_t getAnswerMove() {
            return this.answerMove;
        }

        void setAnswerMove(move_t move) {
            this.answerMove = move;
        }

        void setNextAnswer(map<move_t, Answer> nextAnswer) {
            this.nextAnswer = nextAnswer;
        }

        map<move_t, Answer> getAnswers() {
            return nextAnswer;
        }

        void putAnswer(move_t move, Answer answer) {
            nextAnswer[move] = answer;
        }

        Answer getNextAnswer(move_t move) {
            return nextAnswer[move];
        }

        bool end() {
            return nextAnswer.empty();
        }
};