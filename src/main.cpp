#include "checkmate_in_n.h"
#include <iostream>

using namespace std;
// Test the solution
int main() {
    board_t *board = board_make("3qr2k/pbpp2pp/1p5N/3Q2b1/2P1P3/P7/1PP2PPP/R4RK1 w - - 0 1");
    //checkmate_in_n *checkmate = new checkmate_in_n(board);
    //Answer answer = checkmate->findAnswer(2);
    // // print the answer by printing the contents of the answer map
    // for (auto const& x : answer.getAnswers()) {
    //     cout << x.first << ": " << x.second.getAnswerMove() << endl;
    // }
    return 0;
}