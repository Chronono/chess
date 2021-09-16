#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>

#define BOARD_SIZE 64
#define LINE_SIZE 8

int setBoardToInitPos(uint8_t *board);
int printBoard(uint8_t *board);

#endif