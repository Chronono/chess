#ifndef _MOVE_H_
#define _MOVE_H_

#include "piece.h"
#include "game.h"

#define DIR_UP           -8
#define DIR_DOWN         +8
#define DIR_LEFT         -1
#define DIR_RIGHT        +1

#define DIR_UP_RIGHT     -7
#define DIR_UP_LEFT      -9
#define DIR_DOWN_RIGHT   +9
#define DIR_DOWN_LEFT    +7

#define DIR_N_UP_LEFT    -17
#define DIR_N_UP_RIGHT   -15
#define DIR_N_RIGHT_UP   -6
#define DIR_N_RIGHT_DOWN +10
#define DIR_N_DOWN_RIGHT +17
#define DIR_N_DOWN_LEFT  +15
#define DIR_N_LEFT_DOWN  +6
#define DIR_N_LEFT_UP    -10

#define ABS(x) ((x < 0) ? -(x) : (x))

#define IS_WHITE(color) ((color) && WHITE)
#define LAST_ROW(pos, color) ((GET_ROW(pos) != ((IS_WHITE(color)) ? 0 : 7)) ? 0 : 1)

int getKnightDir(int index_dir);
int getStraightDir(int index_dir);
int getDiagonalDir(int index_dir);
int getAllSlidingDir(int index_dir);

int getAllMoves(game_info_t *game_info, move_t* pseudo_legal_moves, uint8_t *board);

int pawnEatDir(int dir, uint8_t pos, game_info_t *game_info, uint8_t *board, move_t *moves);
int getPawnMoves(game_info_t *game_info, uint8_t pos, move_t* pseudo_legal_moves, uint8_t *board);
int pawn1case(uint8_t pos, uint8_t *board, game_info_t *game_info, move_t *moves);
int pawn2case(uint8_t pos, uint8_t *board, game_info_t *game_info, move_t *moves);

int getBishopMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves);
int getKnightMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves);
int getRookMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves);
int getQueenMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves);
int getKingMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves);

int getCastleMoves(uint8_t *board, game_info_t game_info, move_t* pseudo_legal_moves);
int getEnPassantMove(uint8_t *board, game_info_t game_info, move_t* pseudo_legal_moves);

#endif