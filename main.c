#include "./headers/board.h"
#include "./headers/piece.h"
#include "./headers/debug.h"
#include "./headers/move.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char *not = malloc(sizeof(char) * MAX_NOTATION_SIZE);
    game_info_t game_info;
    game_info.color_to_move = WHITE;
    uint8_t boardgame[BOARD_SIZE];
    //setBoardToInitPos(boardgame);
    resetBoard(boardgame);
    setBoardToFenPos(boardgame, "8/8/8/3K4/8/8/8/8 w - - 0 1");
    printBoard(boardgame); printf("\n\n\n");
    move_t moves[100];

    
    int all_move = getAllMoves(&game_info, moves, boardgame);
    printf("total pawn moves : %d\n", all_move);
    for (int i = 0 ; i < all_move ; i++)
    {
        decodeMove(moves[i], boardgame, not);
        printf("%s\n", not);
    }

    return 0;
}
