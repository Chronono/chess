#include "./headers/board.h"
#include "./headers/piece.h"
#include "./headers/debug.h"
#include "./headers/move.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    game_info_t game_info;
    game_info.color_to_move = WHITE;
    uint8_t boardgame[BOARD_SIZE];
    //setBoardToInitPos(boardgame);
    resetBoard(boardgame);
    setBoardToFenPos(boardgame, "r1b1k1nr/p2p1pNp/n2B4/1p1NP2P/6P1/3P1Q2/P1P1K3/q5b1.");
    printBoard(boardgame); printf("\n\n\n");
    move_t moves[100];

    

    printf("total pawn moves : %d\n", getAllMoves(&game_info, moves, boardgame));


    return 0;
}
