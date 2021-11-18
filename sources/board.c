#include <stdio.h>
#include <stdlib.h>

//  

#include "../headers/board.h"
#include "../headers/piece.h"

#ifdef DEBUG
#include "../headers/debug.h"
#endif

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


int decodeNotationSquare(char letter, char digit)
{
    int letter_int = letter - 'a';
    return letter_int + (8 * (8 - (digit - '0')));
}

int setBoardToFenPos(uint8_t *board, char *fen_code, game_info_t *game_info)
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

        #ifdef DEBUG
        printf("index_fen: %d\nindex_pos: %d\ntmp was:%d  ->  ", index_fen, index_pos, tmp);
        printf(PIECE_TO_BINARY_PATTERN, PIECE_TO_BINARY(tmp));
        printf("\n");
        #endif
    }
    if (fen_code[index_fen] == ' ')
        index_fen++; // blank space
    switch (fen_code[index_fen++]){
        case 'w':
        game_info->color_to_move = WHITE;
        break;

        case 'b':
        game_info->color_to_move = BLACK;
        break;
    }
    if (fen_code[index_fen] == ' ')
        index_fen++; // blank space
    while(fen_code[index_fen] != ' ')
    {
        switch(fen_code[index_fen++])
        {
            case 'K':
            game_info->castle_king_white = 1;
            break;

            case 'Q':
            game_info->castle_queen_white = 1;
            break;

            case 'k':
            game_info->castle_king_black = 1;
            break;

            case 'q':
            game_info->castle_queen_black = 1;
            break;
        }
    }
    if (fen_code[index_fen] == ' ')
        index_fen++; // blank space
    if (fen_code[index_fen] != '-')
    {
        game_info->en_passant_square = decodeNotationSquare(fen_code[index_fen], fen_code[index_fen+1]);
        index_fen+=2;
    }
    if (fen_code[index_fen] == ' ')
        index_fen++; // blank space
    if (fen_code[index_fen + 1] != ' '){
        game_info->moves_compt = (fen_code[index_fen] - '0')*10 + (fen_code[index_fen + 1] - '0');
        index_fen++;
    } else {
        game_info->moves_compt = fen_code[index_fen] - '0';
    }
    index_fen++;
    if (fen_code[index_fen] == ' ')
        index_fen++; // blank space
}

int decodeFenChar(char fen_char, int *index_pos)
{
    int fen_char_conv = 0;
    switch(fen_char)
    {
        case 'r':
            #ifdef DEBUG
            printf("it's a black rook, %d\n", *index_pos);
            #endif
            return ROOK | BLACK;
        
        case 'n':
            #ifdef DEBUG
            printf("it's a black knight, %d\n", *index_pos);
            #endif
            return KNIGHT | BLACK;

        case 'b':
            #ifdef DEBUG
            printf("it's a black bishop, %d\n", *index_pos);
            #endif
            return BISHOP | BLACK;

        case 'q':
            #ifdef DEBUG
            printf("it's a black queen, %d\n", *index_pos);
            #endif
            return QUEEN | BLACK;

        case 'k':
            #ifdef DEBUG
            printf("it's a black king, %d\n", *index_pos);
            #endif
            return KING | BLACK;

        case 'p':
            #ifdef DEBUG
            printf("it's a black pawn, %d\n", *index_pos);
            #endif
            return PAWN | BLACK;

        case 'R':
            #ifdef DEBUG
            printf("it's a white rook, %d\n", *index_pos);
            #endif
            return ROOK | WHITE;

        case 'N':
            #ifdef DEBUG
            printf("it's a white knight, %d\n", *index_pos);
            #endif
            return KNIGHT | WHITE;

        case 'B':
            #ifdef DEBUG
            printf("it's a white bishop, %d\n", *index_pos);
            #endif
            return BISHOP | WHITE;

        case 'Q':
            #ifdef DEBUG
            printf("it's a white queen, %d\n", *index_pos);
            #endif
            return QUEEN | WHITE;

        case 'K':
            #ifdef DEBUG
            printf("it's a white king, %d\n", *index_pos);
            #endif
            return KING | WHITE;

        case 'P':
            #ifdef DEBUG
            printf("it's a white pawn, %d\n", *index_pos);
            #endif            
            return PAWN | WHITE;            

        case '/':
            return 0;

        default:
            fen_char_conv = (int)fen_char - 48;
            #ifdef DEBUG
            printf("%d spaces to skip\n", fen_char_conv);
            #endif
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
