#include "./headers/board.h"
#include "./headers/debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char *not = malloc(sizeof(char) * MAX_NOTATION_SIZE);
    game_info_t game_info;
    initGameInfo(&game_info);

    uint8_t boardgame[BOARD_SIZE];
    //setBoardToInitPos(boardgame);
    resetBoard(boardgame);
    setBoardToFenPos(boardgame, "r1bqkbnr/ppp1p2p/n5p1/3pPpP1/8/8/PPPP1P1P/RNBQKBNR w KQkq f6 0 5", &game_info);
    printBoard(boardgame); printf("\n\n\n");
    debug_printGameInfo(game_info);
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
