#include <checkmate_in_n.hpp>
#include <iostream>
#include <string>

using namespace std;

// Test the solution
int main() {
    string fen = "3qr2k/pbpp2pp/1p5N/3Q2b1/2P1P3/P7/1PP2PPP/R4RK1 w - - 0 1";
    auto pos = libchess::Position(fen, true);
    auto checkmate = checkmate_in_n(pos);
    auto answer = checkmate.findAnswer(2);
    auto mv = answer.getAnswerMove();
    while(mv)
    {
        cout << mv << endl;
        answer = answer.getNextAnswer(mv);
        mv = answer.getAnswerMove();
    }
    return 0;
}