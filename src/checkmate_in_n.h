#include "board.h"
#include "move.h"
#include "arraylist.h"
//#include "answer.h"

class checkmate_in_n{
    board_t board;

    public:
        checkmate_in_n(board_t board) {
            this->board = board;
        }

        bool findAnswer(int depth) {
            //Answer answer;
            //&answer,
            return _answerMove(depth);
            //return answer;
        }
        //Answer *answer,
        bool _answerMove( int depth) {
            alst_t* moves = board_get_moves(&board);
            for (int i = 0; i < moves->len; i++) {
                board_t* b_copy = board_copy(&board);
                move_t *move = (move_t*)alst_get(moves, i);
                board_apply_move(b_copy, move);
                //answer,
                bool found = _opponentMove(depth);
                if (found) {
                    //answer->setAnswerMove(*move);
                    return true;
                }
            }
            return false;
        }

        //Answer *answer
        bool _opponentMove(int depth) {
            alst_t* moves = board_get_moves(&board);
            if (moves->len == 0) {
                return board_is_mate(&board);
            } else if (depth == 1) {
                return false;
            }
            for (int i = 0; i < moves->len; i++) {
                board_t* b_copy = board_copy(&board);
                move_t *move = (move_t*)alst_get(moves, i);
                board_apply_move(b_copy, move);
               // Answer next;
               //&next
                bool found = _answerMove(depth - 1);
                if (!found) {
                    return false;
                }
                //answer->putAnswer(*move, next);
            }
            return true;
        }
};