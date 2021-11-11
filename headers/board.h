#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>

#define BOARD_SIZE 64
#define LINE_SIZE 8
#define NB_SLASH_IN_FEN 7

#define GET_COL(cell_pos) (cell_pos & 0b111)
#define GET_ROW(cell_pos) ((cell_pos & 0b111000) >> 3)

int setBoardToInitPos(uint8_t *board);
int setBoardToFenPos(uint8_t *board, char *fen_code);

int decodeFenChar(char fen_char, int *index_fen);

int printBoard(uint8_t *board);

#endif