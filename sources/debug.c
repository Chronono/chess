#include <stdio.h>


#include "../headers/debug.h"
#include "../headers/piece.h"
#include "../headers/board.h"


void debug_printPiecesType(uint8_t *board)
{
    printf("---------------------------------\n| ");
    for (int i = 0 ; i < LINE_SIZE ; i++){
        for (int j = 0 ; j < LINE_SIZE ; j++){
            switch (board[j + i*LINE_SIZE] & 0b111){
                case PAWN: printf("P | "); break;
                case KNIGHT: printf("N | "); break;
                case BISHOP: printf("B | "); break;
                case ROOK: printf("R | "); break;
                case QUEEN: printf("Q | "); break;
                case KING: printf("K | "); break;
                case EMPTY: printf("  | "); break;
            }
        } printf("\n---------------------------------");
        if (i < LINE_SIZE-1) printf("\n| ");
    }
}

void debug_printPiecesColor(uint8_t *board)
{
    printf("---------------------------------\n| ");
    for (int i = 0 ; i < LINE_SIZE ; i++){
        for (int j = 0 ; j < LINE_SIZE ; j++){
            switch (board[j + i*LINE_SIZE] & 0b11000){
                case WHITE: printf("W | "); break;
                case BLACK: printf("B | "); break;
                default: printf("  | "); break;
            }
        } printf("\n---------------------------------");
        if (i < LINE_SIZE-1) printf("\n| ");
    }
}