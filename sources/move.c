#include "../headers/move.h"
#include "../headers/board.h"

#include <stdlib.h>
#include <stdio.h>

#define DEBUG

//#define ON_C_COL(pos, c) ((GET_COL(pos) == c) ? 1 : 0)

int getDiagonalDir(int index_dir)
{
    switch(index_dir)
    {
        case 0: return DIR_UP_RIGHT;
        case 1: return DIR_UP_LEFT;
        case 2: return DIR_DOWN_RIGHT;
        case 3: return DIR_DOWN_LEFT;
        default: exit(1);
    }
}
int getKnightDir(int index_dir)
{
    switch(index_dir)
    {
         case 0: return DIR_N_UP_LEFT;
         case 1: return DIR_N_UP_RIGHT;
         case 2: return DIR_N_RIGHT_UP;
         case 3: return DIR_N_RIGHT_DOWN;
         case 4: return DIR_N_DOWN_RIGHT;
         case 5: return DIR_N_DOWN_LEFT;
         case 6: return DIR_N_LEFT_DOWN;
         case 7: return DIR_N_LEFT_UP;
        default: exit(1);
    }
}

int getAllSlidingDir(int index_dir)
{
    switch(index_dir)
    {
        case 0: return DIR_UP;
        case 1: return DIR_DOWN;
        case 2: return DIR_LEFT;
        case 3: return DIR_RIGHT;
        case 4: return DIR_UP_RIGHT;
        case 5: return DIR_UP_LEFT;
        case 6: return DIR_DOWN_RIGHT;
        case 7: return DIR_DOWN_LEFT;
        default: exit(1);
    }
}
int getStraightDir(int index_dir)
{
    switch(index_dir)
    {
        case 0: return DIR_UP;
        case 1: return DIR_DOWN;
        case 2: return DIR_LEFT;
        case 3: return DIR_RIGHT;
    }
}


int getAllMoves(game_info_t *game_info, move_t* pseudo_legal_moves, uint8_t *board)
{
    uint8_t moves_compt = 0;
    moves_compt += getEnPassantMove(board, *game_info, pseudo_legal_moves + moves_compt);
    for (int cell_pos = 0 ; cell_pos < BOARD_SIZE ; cell_pos++)
    {
        if (board[cell_pos] == EMPTY || (GET_COLOR(board[cell_pos]) != game_info->color_to_move))
            continue;

        #ifdef DEBUG
        #endif

        switch(GET_PIECE(board[cell_pos])){
            case PAWN:
                moves_compt += getPawnMoves(game_info, cell_pos, pseudo_legal_moves + moves_compt, board);         
                break;
            case BISHOP:
                moves_compt += getBishopMoves(board, cell_pos, pseudo_legal_moves + moves_compt);
                break;
            case KNIGHT:
                moves_compt += getKnightMoves(board, cell_pos, pseudo_legal_moves + moves_compt);
                break;
            case ROOK:
                moves_compt += getRookMoves(board, cell_pos, pseudo_legal_moves + moves_compt);
                break;
            case QUEEN:
                moves_compt += getQueenMoves(board, cell_pos, pseudo_legal_moves + moves_compt);
                break;
            case KING:
                moves_compt += getKingMoves(board, cell_pos, pseudo_legal_moves + moves_compt);
                break;

            default: printf("cell %u -> %u is not recognized\n",cell_pos, board[cell_pos]);                
        }      
    }
    return moves_compt;
}

//int pawnEnPassant();
int pawnEatDir(int dir, uint8_t pos, game_info_t *game_info, uint8_t *board, move_t *moves)
{
    if (!LAST_ROW(pos,game_info->color_to_move)){
        if (!(GET_COL(pos) == ((dir == ABS(DIR_UP_RIGHT)) ? 7 : 0))){
            if ((GET_COLOR(board[pos + ((game_info->color_to_move == WHITE) ? -dir : dir)]) != game_info->color_to_move) && (GET_COLOR(board[pos + ((game_info->color_to_move == WHITE) ? -dir : dir)]) != 0)){
                move_t new_move = {
                    pos, 
                    pos+((game_info->color_to_move == WHITE) ? -dir : dir),
                    0,
                    BOARD_SIZE
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
                pos + ((game_info->color_to_move == WHITE) ? -8 : 8),
                0,
                BOARD_SIZE
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
                pos + ((game_info->color_to_move == WHITE) ? -16 : 16),
                0,
                BOARD_SIZE
            };
            *moves = new_move;
            return 1;
        }
    }
    return 0;
}

int getPawnMoves(game_info_t *game_info, uint8_t pos, move_t* pseudo_legal_moves, uint8_t *board)
{
    short int compt_move = 0;
    compt_move+=pawnEatDir(ABS(DIR_UP_RIGHT), pos, game_info, board, pseudo_legal_moves);
    compt_move+=pawnEatDir(ABS(DIR_UP_LEFT), pos, game_info, board, pseudo_legal_moves + compt_move);
    compt_move+=pawn1case(pos, board, game_info, pseudo_legal_moves + compt_move);
    compt_move+=pawn2case(pos, board, game_info, pseudo_legal_moves + compt_move);
    return compt_move;
}

int getSlidingPiecesMovesDir(uint8_t *board, uint8_t pos, move_t *moves, int dir, uint8_t initial_pos)  // Check if he can move one step more, if yes, it will be added otherwise, return 
{
    // check if border
    if (GET_COL(pos) == 0 && GET_COL(pos+dir) == 7) return 0;
    if (GET_COL(pos) == 7 && GET_COL(pos+dir) == 0) return 0;
    if (((pos + dir) >= BOARD_SIZE) || ((pos + dir) < 0)) return 0;
    // check if next square is empty
    if (board[pos + dir] == EMPTY){
        // if yes, add the move and recurse into the function with the next pos
        move_t new_move = {
            initial_pos, 
            pos + dir,
            0,
            BOARD_SIZE
        };
        *moves = new_move;
        return 1 + getSlidingPiecesMovesDir(board, pos + dir, moves + 1, dir, initial_pos);
    }
    // check if next square is occupied by enemy
    if (GET_COLOR(board[pos + dir]) != GET_COLOR(board[initial_pos]))
    {
        // if yes, add the move and return
        move_t new_move = {
            initial_pos,
            pos + dir,
            0,
            BOARD_SIZE
        };
        *moves = new_move;
        return 1;
    }
    return 0;
}   
int getBishopMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves)
{
    uint8_t move_compt = 0;
    for (int dir = 0 ; dir < 4 ; dir++)
    {
        move_compt += getSlidingPiecesMovesDir(board, pos, pseudo_legal_moves + move_compt, getDiagonalDir(dir), pos);
    }
    return move_compt;
}

int getRookMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves)
{
    uint8_t move_compt = 0;
    for (int dir = 0 ; dir < 4 ; dir++)
    {
        move_compt += getSlidingPiecesMovesDir(board, pos, pseudo_legal_moves + move_compt, getStraightDir(dir), pos);
    }
    return move_compt;
}

int getKnightMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves)
{
    int compt_move = 0;
    for (int dir = 0 ; dir < 8 ; dir++){
        if (((pos + getKnightDir(dir)) < BOARD_SIZE) && ((pos + getKnightDir(dir)) >= 0))
        {
            if (((ABS((getKnightDir(dir) + pos)/8 - (pos/8)) == 2) &&   (getKnightDir(dir) & 1))
              || (ABS((getKnightDir(dir) + pos)/8 - (pos/8)) == 1) && (!(getKnightDir(dir) & 1)))
            {
                if ((board[pos + getKnightDir(dir)] == EMPTY) || (GET_COLOR(board[pos]) != GET_COLOR(board[pos + getKnightDir(dir)])))
                {
                    move_t new_move =  {
                        pos, 
                        pos + getKnightDir(dir), 
                        0,
                        BOARD_SIZE
                    };
                    pseudo_legal_moves[compt_move++] = new_move;
                }
            }
        }
    }
    return compt_move;
}

int getQueenMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves)
{
    uint8_t move_compt = 0;
    for (int dir = 0 ; dir < 8 ; dir++)
    {
        move_compt += getSlidingPiecesMovesDir(board, pos, pseudo_legal_moves + move_compt, getAllSlidingDir(dir), pos);
    }
    return move_compt;
}

int getKingMoves(uint8_t *board, uint8_t pos, move_t* pseudo_legal_moves)
{
    int compt_move = 0;
    for (int dir = 0 ; dir < 8 ; dir++)
    {
        if (board[pos + getAllSlidingDir(dir)] == EMPTY ||
            GET_COLOR(board[pos + getAllSlidingDir(dir)]) != GET_COLOR(board[pos]))
        {
            switch (ABS(getAllSlidingDir(dir)))
            {
                case 1:
                    if (((pos/8) - (pos + getAllSlidingDir(dir))/8) == 0)
                    {
                        move_t new_move = {
                            pos,
                            pos + getAllSlidingDir(dir), 
                            0,
                            BOARD_SIZE
                        };
                        pseudo_legal_moves[compt_move++] = new_move;
                    }
                break;

                default:
                    if ((ABS((pos/8) - (pos + getAllSlidingDir(dir))/8) == 1) &&
                    (((pos + getAllSlidingDir(dir)) < BOARD_SIZE) && ((pos + getAllSlidingDir(dir)) >= 0)))
                    {
                        move_t new_move = {
                            pos,
                            pos + getAllSlidingDir(dir), 
                            0,
                            BOARD_SIZE
                        };
                        pseudo_legal_moves[compt_move++] = new_move;
                    }
            }
        }
    }
    return compt_move;
}


int getCastleMoves(uint8_t *board, game_info_t game_info, move_t* pseudo_legal_moves)
{

}

int getEnPassantMove(uint8_t *board, game_info_t game_info, move_t* pseudo_legal_moves)
{
    int compt_move = 0;
    if (game_info.en_passant_square < BOARD_SIZE)
    {
        if (board[game_info.en_passant_square + (game_info.color_to_move == WHITE ? 7 : -7)] == (PAWN | game_info.color_to_move))
        {
            move_t new_move = {
                game_info.en_passant_square + (game_info.color_to_move == WHITE ? 7 : -7), 
                game_info.en_passant_square,
                0,
                game_info.en_passant_square + (game_info.color_to_move == WHITE ? -8 : 8)
            };
            pseudo_legal_moves[compt_move++] = new_move;
        }
        if (board[game_info.en_passant_square + (game_info.color_to_move == WHITE ? 9 : -9)] == (PAWN | game_info.color_to_move))
        {
            move_t new_move = {
                game_info.en_passant_square + (game_info.color_to_move == WHITE ? 9 : -9), 
                game_info.en_passant_square,
                0,
                game_info.en_passant_square + (game_info.color_to_move == WHITE ? -8 : 8)
            };
            pseudo_legal_moves[compt_move++] = new_move;
        }
    }
    return compt_move;
}