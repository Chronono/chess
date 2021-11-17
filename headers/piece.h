#ifndef _PIECE_H_
#define _PIECE_H_

#include <stdint.h>

// #define EMPTY   0b00000
// #define PAWN    0b00001
// #define BISHOP  0b00010
// #define KNIGHT  0b00011
// #define ROOK    0b00100
// #define QUEEN   0b00101
// #define KING    0b00110

#define GET_COLOR(piece) (piece & 0b11000)
#define GET_PIECE(piece) (piece & 0b00111)

#define WHITE   0b01000
#define BLACK   0b10000

typedef enum piece {
    EMPTY,
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING
} piece_e;

int printPiece(uint8_t cell);

#endif