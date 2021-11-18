#include "../headers/game.h"
#include "../headers/piece.h"

void initGameInfo(game_info_t *game_info)
{
    game_info->color_to_move = WHITE;
    game_info->castle_king_black = 1;
    game_info->castle_queen_black = 1;
    game_info->castle_king_white = 1;
    game_info->castle_queen_white = 1;
    game_info->in_check = 0;
    game_info->checkmate = 0;
    game_info->moves_compt = 0;
}