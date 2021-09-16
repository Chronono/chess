#include <stdio.h>
#include <stdlib.h>

#include "../headers/board.h"
#include "../headers/piece.h"

int setBoardToInitPos(uint8_t *board)
{
    uint8_t board_tmp[BOARD_SIZE] = {
        ROOK | BLACK, KNIGHT | BLACK, BISHOP | BLACK, QUEEN | BLACK, KING | BLACK, BISHOP | BLACK, KNIGHT | BLACK, ROOK | BLACK,
        PAWN | BLACK, PAWN | BLACK, PAWN | BLACK, PAWN | BLACK, PAWN | BLACK, PAWN | BLACK, PAWN | BLACK, PAWN | BLACK,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
        PAWN | WHITE, PAWN | WHITE, PAWN | WHITE, PAWN | WHITE, PAWN | WHITE, PAWN | WHITE, PAWN | WHITE, PAWN | WHITE,
        ROOK | WHITE, KNIGHT | WHITE, BISHOP | WHITE, QUEEN | WHITE, KING | WHITE, BISHOP | WHITE, KNIGHT | WHITE, ROOK | WHITE
        
    };

    for (int i = 0 ; i < BOARD_SIZE ; i++) board[i] = board_tmp[i];

    return 0;
}

int printBoard(uint8_t *board)
{              
    printf("---------------------------------\n| ");
    for (int i = 0 ; i < LINE_SIZE ; i++){
        for (int j = 0 ; j < LINE_SIZE ; j++){
            printPiece(board[j + i*LINE_SIZE]);
            printf(" | ");
        } 
        printf("\n---------------------------------"); 
        if (i < LINE_SIZE - 1) printf("\n| ");
    }

    return 0;
}
