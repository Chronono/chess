#ifndef _GAME_H_
#define _GAME_H_

#include <stdint.h>

typedef struct move {
    uint8_t initial_pos;
    uint8_t ending_pos;
}move_t;

typedef struct game_info {
    move_t lastMove;
    uint8_t color_to_move;
    uint8_t in_check;
    uint8_t checkmate;
    uint8_t moves_compt;
    uint8_t castle_white;
    uint8_t castle_black;
}game_info_t;


#endif