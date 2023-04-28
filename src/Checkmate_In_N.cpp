#include "board.h"
#include "move.h"
#include "arraylist.h"

class Checkmate_In_N{
    // should be a pointer?
    board_t board;
    int depth;

    public:
        Checkmate_In_N(board_t board, int depth) {
            this->board = board;
            this->depth = depth;
        }

        bool checkMateHelper(board_t board, int depth)
        {
            if(this->depth >= currDepthCount) {
                return false;
            }
            if(opponent move)
            {
                // MoveList availableMoves 
                for (m : availableMoves){
                    // do recursive calls here
                    
                    if(!checkMateHelper(board, depth + 1)) {
                        return false;
                    }
                }
            }
            return true;            
        }
        
        bool findCheckmate()
        {
            return checkMateHelper(this->board, this->depth);
        }

        

}