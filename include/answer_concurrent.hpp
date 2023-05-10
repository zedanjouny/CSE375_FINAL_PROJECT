#include <libchess/move.hpp>
#include <tbb/concurrent_hash_map.h>
#include <functional>
#include <string>

using namespace std;
using namespace libchess;
using namespace tbb;

class Answer_Concurrent {
    struct MyHashCompare {
        static size_t hash(const Move& x) {
            string temp = static_cast<string>(x);
            size_t h = 0;
            for( const char* s = temp.c_str(); *s; ++s )
                h = (h*17)^*s;
            return h;
        }
        static bool equal( const Move& x, const Move& y ) {
            return x==y;
        }
    };

    Move answerMove;
    concurrent_hash_map<Move, Answer, MyHashCompare> nextAnswer;

    public:
        Answer_Concurrent() {}

        Move getAnswerMove() {
            return this->answerMove;
        }

        void setAnswerMove(Move move) {
            this->answerMove = move;
        }

        void setNextAnswer(concurrent_hash_map<Move, Answer, MyHashCompare> nextAnswer) {
            this->nextAnswer = nextAnswer;
        }

        concurrent_hash_map<Move, Answer, MyHashCompare> getAnswers() {
            return nextAnswer;
        }

        void putAnswer(Move move, Answer answer) {
            this->nextAnswer.insert(make_pair(move,answer));
        }

        Answer getNextAnswer(Move move) {
            concurrent_hash_map<Move, Answer, MyHashCompare>::accessor a;
            this->nextAnswer.find(a, move);
            return a->second;
        }

        bool end() {
            return nextAnswer.empty();
        }
};