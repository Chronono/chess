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

int resetBoard(uint8_t *board)
{
    int i;
    for (i = 0 ; i < BOARD_SIZE ; i++) board[i] = 0;
    return 0;
}

int setBoardToFenPos(uint8_t *board, char *fen_code)
{
    int index_fen = 0;
    int index_pos = 0;
    int *pt_index_pos = &index_pos;
    int tmp=0;

    while(index_pos < BOARD_SIZE)
    {
        if ((tmp = decodeFenChar(fen_code[index_fen], pt_index_pos)) > 0)
        {
            board[index_pos] = tmp;
            index_pos++;
        }
        index_fen++;
        printf("index_fen: %d\nindex_pos: %d\ntmp was:%d  ->  ", index_fen, index_pos, tmp);
        printf(PIECE_TO_BINARY_PATTERN, PIECE_TO_BINARY(tmp));
        printf("\n");
    }
}

int decodeFenChar(char fen_char, int *index_pos)
{
    int fen_char_conv = 0;
    switch(fen_char)
    {
        case 'r':
            printf("it's a black rook, %d\n", *index_pos);
            return ROOK | BLACK;
        
        case 'n':
            printf("it's a black knight, %d\n", *index_pos);
            return KNIGHT | BLACK;
        
        case 'b':
            printf("it's a black bishop, %d\n", *index_pos);
            return BISHOP | BLACK;
        
        case 'q':
            printf("it's a black queen, %d\n", *index_pos);
            return QUEEN | BLACK;
        
        case 'k':
            printf("it's a black king, %d\n", *index_pos);
            return KING | BLACK;
        
        case 'p':
            printf("it's a black pawn, %d\n", *index_pos);
            return PAWN | BLACK;
        
        case 'R':
            printf("it's a white rook, %d\n", *index_pos);
            return ROOK | WHITE;
        
        case 'N':
            printf("it's a white knight, %d\n", *index_pos);
            return KNIGHT | WHITE;
        
        case 'B':
            printf("it's a white bishop, %d\n", *index_pos);
            return BISHOP | WHITE;
        
        case 'Q':
            printf("it's a white queen, %d\n", *index_pos);
            return QUEEN | WHITE;
        
        case 'K':
            printf("it's a white king, %d\n", *index_pos);
            return KING | WHITE;
        
        case 'P':
            printf("it's a white pawn, %d\n", *index_pos);
            return PAWN | WHITE;

        case '/':
            return 0;

        default:
            fen_char_conv = (int)fen_char - 48;
            printf("%d spaces to skip\n", fen_char_conv);
            if (fen_char_conv > 0 && fen_char_conv < 9)
            {
                *index_pos+=fen_char_conv;
                return 0;
            }
    }
    return -1;
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
