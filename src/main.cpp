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
    auto checkmate_concurrent = checkmate_in_n_concurrent(pos);
    auto answer = checkmate.findAnswer(5);
    cout << answer << endl;
    cout << "here" << endl;
    auto answer_quick = checkmate_concurrent.findAnswer(5);
    return 0;
}