#ifndef _GAME_H_
#define _GAME_H_

#include <stdint.h>

typedef struct move {
    uint8_t initial_pos;
    uint8_t ending_pos;
    uint8_t check;  // 0 no 1 check 2 checkmate
    uint8_t en_passant_pawn_eaten;
}move_t;

typedef struct game_info {
    move_t lastMove;
    uint8_t color_to_move;
    uint8_t in_check;
    uint8_t checkmate;
    uint8_t moves_compt;
    uint8_t castle_king_white;
    uint8_t castle_queen_white;
    uint8_t castle_king_black;
    uint8_t castle_queen_black;
    uint8_t en_passant_square;
}game_info_t;

void initGameInfo(game_info_t *game_info);

#endif