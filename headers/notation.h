#ifndef _NOTATION_H_
#define _NOTATION_H_

#include "move.h"

#define PAWN_DIR_LEFT(piece)((GET_COLOR(piece) == BLACK)?9:-9)
#define PAWN_DIR_RIGHT(piece)((GET_COLOR(piece) == BLACK)?16:-16)
#define MAX_NOTATION_SIZE 7

int thereIsSamePieceInDir(int pos, move_t move, int dir, uint8_t *board);
char getCol(int square); 
void pieceToMoveNotation(char *notation, move_t move, uint8_t *board, int *compt_notation);
void targetMoveNotation(char * notation, move_t move, uint8_t *board, int *compt_notation);
void decodeMove(move_t move, uint8_t *board, char *notation);


#endif