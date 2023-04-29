#include "board.h"
#include "move.h"
#include "arraylist.h"
#include "answer.h"

class checkmate_in_n{
    board_t board;

    public:
        checkmate_in_n(board_t board) {
            this->board = board;
        }

        Answer findAnswer(int depth) {
            Answer answer;
            _answerMove(&answer, depth);
            return answer;
        }

        bool _answerMove(Answer *answer, int depth) {
            alst_t moves = board_get_moves(&board);
            for (int i = 0; i < moves.len; i++) {
                board_t* b_copy = board_copy(&board);
                move_t *move = alst_get(&moves, i);
                board_apply_move(&b_copy, move);
                bool found = _opponentMove(answer, depth);
                if (found) {
                    answer->setAnswerMove(*move);
                    return true;
                }
            }
            return false;
        }

        bool _opponentMove(Answer *answer, int depth) {
            alst_t moves = board_get_moves(&board);
            if (moves.len == 0) {
                return board_is_mate(&board);
            } else if (depth == 1) {
                return false;
            }
            for (int i = 0; i < moves.len; i++) {
                board_t* b_copy = board_copy(&board);
                move_t *move = alst_get(&moves, i);
                board_apply_move(&b_copy, move);
                Answer next;
                bool found = _answerMove(&next, depth - 1);
                if (!found) {
                    return false;
                }
                answer->putAnswer(*move, next);
            }
            return true;
        }


}