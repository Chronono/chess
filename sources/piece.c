#include "../headers/piece.h"
#include <stdio.h>

int printPiece(uint8_t cell)
{
    if (cell == EMPTY){
        printf(" ");
        return 0;
    }

    if (GET_COLOR(cell) == BLACK){
        printf("\033[0;31m");       // color for black
    } else printf("\033[0;34m");    // color for white

    switch(GET_PIECE(cell)){
        case PAWN: printf("P"); break;
        case BISHOP: printf("B"); break;
        case KNIGHT: printf("N"); break;
        case ROOK: printf("R"); break;
        case QUEEN: printf("Q"); break;
        case KING: printf("K"); break;
    }

    printf("\033[0m"); // Going back to default color
    return 0;
}