#include "checkmate_in_n.h"

// Test the solution
int main() {
    board_t *board = board_make("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    checkmate_in_n *checkmate = new checkmate_in_n(board);
    Answer answer = checkmate->findAnswer(3);
    return 0;
}