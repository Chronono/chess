#include <stdio.h>


#include "../headers/debug.h"
#include "../headers/piece.h"
#include "../headers/board.h"
#include "../headers/move.h"

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
            switch (GET_COLOR(board[j + i*LINE_SIZE])){
                case WHITE: printf("W | "); break;
                case BLACK: printf("B | "); break;
                default: printf("  | "); break;
            }
        } printf("\n---------------------------------");
        if (i < LINE_SIZE-1) printf("\n| ");
    }
}

void debug_printGameInfo(game_info_t game_info)
{
    printf("|-----------------------------------------|\n");
    printf("|                GAME INFO                |\n");
    printf("|-----------------------------------------|\n");
    printf("|                                         |\n");
    printf("|  COLOR TO MOVE : %c                    |\n", (game_info.color_to_move == WHITE ? 'W' : 'B'));
    printf("|  Moves compt : %2d                      |\n", game_info.moves_compt);
    printf("|  Castle for White : %c %c            |\n", (game_info.castle_king_white == 1 ? 'K' : ' '), (game_info.castle_queen_white == 1 ? 'Q' : ' '));
    printf("|  Castle for Black : %c %c            |\n", (game_info.castle_king_black == 1 ? 'k' : ' '), (game_info.castle_queen_black == 1 ? 'q' : ' '));
    printf("|  En passant : %d                      |\n", game_info.en_passant_square);
    printf("|                                         |\n");
    printf("|-----------------------------------------|\n");
}