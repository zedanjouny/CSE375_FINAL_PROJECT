#include <checkmate_in_n_sequential.hpp>
#include <checkmate_in_n_concurrent.hpp>
#include <iostream>
#include <string>

using namespace std;

// Test the solution
int main() {
    string fen = "r1bq2k1/ppp2r1p/2np1pNQ/2bNpp2/2B1P3/3P4/PPP2PPP/R3K2R w KQ - 0 1";
    auto pos = libchess::Position(fen, true);
    auto checkmate = checkmate_in_n(pos);
    auto answer = checkmate.findAnswer(5);
    auto mv = answer.getAnswerMove();
    while(mv)
    {
        cout << mv << endl;
        answer = answer.getNextAnswer(mv);
        if(mv == answer.getAnswerMove())
        {
            break;
        }
        mv = answer.getAnswerMove();
    }
    return 0;
}