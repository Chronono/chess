#include "./headers/board.h"
#include "./headers/piece.h"
#include "./headers/debug.h"

int main(int argc, char* argv[])
{

    uint8_t boardgame[BOARD_SIZE];
    setBoardToInitPos(boardgame);
    printBoard(boardgame); printf("\n\n\n");


    return 0;
}
