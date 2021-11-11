#include "../headers/move.h"
#include "../headers/board.h"

//#define ON_C_COL(pos, c) ((GET_COL(pos) == c) ? 1 : 0)

int getAllMoves(game_info_t *game_info, move_t* legal_moves, uint8_t *board)
{
    uint8_t moves_compt = 0;
    for (int cell_pos = 0 ; cell_pos < BOARD_SIZE ; cell_pos++)
    {
        if (board[cell_pos] == EMPTY || (GET_COLOR(board[cell_pos]) != game_info->color_to_move))
            continue;
        
        printf("We need to calculate this piece %d\n", cell_pos);
         
        switch(GET_PIECE(board[cell_pos])){
            case PAWN:
                moves_compt += getPawnMoves(game_info, cell_pos, legal_moves + moves_compt, board);         
                break;
            case BISHOP:
                moves_compt += getBishopMoves(cell_pos, legal_moves + moves_compt);
                break;
            case KNIGHT:
                moves_compt += getKnightMoves(cell_pos, legal_moves + moves_compt);
                break;
            case ROOK:
                moves_compt += getRookMoves(cell_pos, legal_moves + moves_compt);
                break;
            case QUEEN:
                moves_compt += getQueenMoves(cell_pos, legal_moves + moves_compt);
                break;
            case KING:
                moves_compt += getKingMoves(cell_pos, legal_moves + moves_compt);
                break;

            default: printf("cell %u -> %u is not recognized\n",cell_pos, board[cell_pos]);                
        }      
    }
    return moves_compt;
}

//int pawnEnPassant();
int pawnEatDir(uint8_t dir, uint8_t pos, game_info_t *game_info, uint8_t *board, move_t *moves)
{
    if (!LAST_ROW(pos,game_info->color_to_move)){
        if (!(GET_COL(pos) == ((dir == ABS(DIR_UP_RIGHT)) ? 7 : 0))){
            if ((GET_COLOR(board[pos + ((game_info->color_to_move == WHITE) ? -dir : dir)]) != game_info->color_to_move) && (GET_COLOR(board[pos + ((game_info->color_to_move == WHITE) ? -dir : dir)]) != 0)){
                move_t new_move = {
                    pos, 
                    pos+((game_info->color_to_move == WHITE) ? -dir : dir)
                };
                *moves = new_move;
                return 1;            
            }
        }
    }
    return 0;
}

int pawn1case(uint8_t pos, uint8_t *board, game_info_t *game_info, move_t *moves)
{
    if (!LAST_ROW(pos, game_info->color_to_move)){
        if (board[pos + ((game_info->color_to_move == WHITE) ? -8 : 8)] == EMPTY){
            move_t new_move = {
                pos,
                pos + ((game_info->color_to_move == WHITE) ? -8 : 8)
            };
            *moves = new_move;
            return 1;
        }       
    }
    return 0;
}

int pawn2case(uint8_t pos, uint8_t *board, game_info_t *game_info, move_t *moves)
{
    if (GET_ROW(pos) == ((game_info->color_to_move == WHITE) ? 6 : 1)){
        if (board[pos + ((game_info->color_to_move == WHITE) ? -16 : 16)] == EMPTY){
            move_t new_move = {
                pos,
                pos + ((game_info->color_to_move == WHITE) ? -16 : 16)
            };
            *moves = new_move;
            return 1;
        }
    }
    return 0;
}

int getPawnMoves(game_info_t *game_info, uint8_t pos, move_t* legal_moves_piece, uint8_t *board)
{
    short int compt_move = 0;
    compt_move+=pawnEatDir(ABS(DIR_UP_RIGHT), pos, game_info, board, legal_moves_piece);
    compt_move+=pawnEatDir(ABS(DIR_UP_LEFT), pos, game_info, board, legal_moves_piece + compt_move);
    compt_move+=pawn1case(pos, board, game_info, legal_moves_piece);
    compt_move+=pawn2case(pos, board, game_info, legal_moves_piece);
    return compt_move;
}


int getBishopMoves(uint8_t pos, move_t* legal_moves_piece)
{
    return 0;
}

int getKnightMoves(uint8_t pos, move_t* legal_moves_piece)
{
    return 0;
}

int getRookMoves(uint8_t pos, move_t* legal_moves_piece)
{
    return 0;
}

int getQueenMoves(uint8_t pos, move_t* legal_moves_piece)
{
    return 0;
}

int getKingMoves(uint8_t pos, move_t* legal_moves_piece)
{
    return 0;
}