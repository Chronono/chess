#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "move.h"

#define PIECE_TO_BINARY_PATTERN "%c%c%c%c%c"
#define PIECE_TO_BINARY(piece)      \
    (piece & 0b10000 ? '1' : '0'),  \
    (piece & 0b01000 ? '1' : '0'),  \
    (piece & 0b00100 ? '1' : '0'),  \
    (piece & 0b00010 ? '1' : '0'),  \
    (piece & 0b00001 ? '1' : '0')   

#define MAX_NOTATION_SIZE 7

void decodeMove(move_t move, uint8_t *board, char *notation);

void targetMoveNotation(char * notation, move_t move, uint8_t *board, int *compt_notation);
void pieceToMoveNotation(char *notation, move_t move, uint8_t *board, int *compt_notation);

void debug_printPiecesColor(uint8_t *board);
void debug_printPiecesType(uint8_t *board);
void debug_printGameInfo(game_info_t game_info);



#endif