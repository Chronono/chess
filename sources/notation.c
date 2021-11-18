#include "../headers/notation.h"
#include "../headers/board.h"

int thereIsSamePieceInDir(int pos, move_t move, int dir, uint8_t *board)
{
    if (GET_COL(pos) == 0 && GET_COL(pos+dir) == 7) return 0;
    if (GET_COL(pos) == 7 && GET_COL(pos+dir) == 0) return 0;
    if (((pos+dir) < 0) || ((pos+dir) > BOARD_SIZE)) return 0;
    if ((board[pos + dir] == board[move.initial_pos]) && ((pos + dir) != move.initial_pos)) return pos + dir; 
    if (board[pos + dir] != EMPTY) return 0;
    return thereIsSamePieceInDir(pos + dir, move, dir, board);
}

char getCol(int square) { 
    switch(GET_COL(square))
    {
        case 0: return 'a';       
        case 1: return 'b';       
        case 2: return 'c';       
        case 3: return 'd';       
        case 4: return 'e';       
        case 5: return 'f';       
        case 6: return 'g';       
        case 7: return 'h';       
    }
}

void pieceToMoveNotation(char *notation, move_t move, uint8_t *board, int *compt_notation)
{
    switch(GET_PIECE(board[move.initial_pos]))
    {
        case BISHOP:
            notation[(*compt_notation)++] = 'B'; 
            for (int dir = 0 ; dir < 4 ; dir++)  
            {
                if (thereIsSamePieceInDir(move.ending_pos, move, getDiagonalDir(dir), board) > 0)
                {
                    notation[(*compt_notation)++] = getCol(move.initial_pos); 
                    notation[(*compt_notation)++] = '8' - move.initial_pos/8; 
                    break;
                }
            }
        break;

        case KNIGHT:
            notation[(*compt_notation)++] = 'N';         
            for (int dir = 0 ; dir < 8 ; dir++)
            {
                if ((move.ending_pos + getKnightDir(dir)) != move.initial_pos && (board[move.ending_pos + getKnightDir(dir)] == board[move.initial_pos]))
                {
                    if (((ABS((getKnightDir(dir) + move.ending_pos)/8 - (move.ending_pos/8)) == 2) &&   (getKnightDir(dir) & 1))
                    || (ABS((getKnightDir(dir) + move.ending_pos)/8 - (move.ending_pos/8)) == 1) && (!(getKnightDir(dir) & 1)))
                    {
                        notation[(*compt_notation)++] = getCol(move.initial_pos); 
                        notation[(*compt_notation)++] = '8' - move.initial_pos/8; 
                        break;
                    }
                }
            }
        break;

        case ROOK:
            notation[(*compt_notation)++] = 'R'; 
            for (int dir = 0 ; dir < 4 ; dir++)
            {
                if (thereIsSamePieceInDir(move.ending_pos, move, getStraightDir(dir), board) > 0)
                {
                    notation[(*compt_notation)++] = getCol(move.initial_pos); 
                    notation[(*compt_notation)++] = '8' - move.initial_pos/8; 
                    break;
                }
            }
        break;

        case QUEEN:
            notation[(*compt_notation)++] = 'Q'; 
            for (int dir = 0 ; dir < 4 ; dir++)
            {
                if (thereIsSamePieceInDir(move.ending_pos, move, getStraightDir(dir), board) > 0)
                {
                    notation[(*compt_notation)++] = getCol(move.initial_pos); 
                    notation[(*compt_notation)++] = '8' - move.initial_pos/8; 
                    break;
                }
            }
            for (int dir = 0 ; dir < 4 ; dir++)
            {
                if (thereIsSamePieceInDir(move.ending_pos, move, getDiagonalDir(dir), board) > 0)
                {
                    notation[(*compt_notation)++] = getCol(move.initial_pos); 
                    notation[(*compt_notation)++] = '8' - move.initial_pos/8; 
                    break;
                }
            }
        break;

        case KING:
            notation[(*compt_notation)++] = 'K';   
        break;

        case PAWN:
            if (ABS(move.ending_pos - move.initial_pos) == 7 || ABS(move.ending_pos - move.initial_pos) == 9)
            {
                if ((board[move.ending_pos + PAWN_DIR_LEFT(board[move.initial_pos])] == board[move.ending_pos])
                    && (move.ending_pos + PAWN_DIR_LEFT(board[move.initial_pos]) != move.initial_pos))
                {
                    notation[(*compt_notation)++] = getCol(move.initial_pos); 
                    notation[(*compt_notation)++] = '8' - move.initial_pos/8; 
                } else if ((board[move.ending_pos + PAWN_DIR_RIGHT(board[move.initial_pos])] == board[move.ending_pos])
                    && (move.ending_pos + PAWN_DIR_RIGHT(board[move.initial_pos]) != move.initial_pos))
                {
                    notation[(*compt_notation)++] = getCol(move.initial_pos); 
                    notation[(*compt_notation)++] = '8' - move.initial_pos/8; 
                }
            }
        break;
    }
}

void targetMoveNotation(char * notation, move_t move, uint8_t *board, int *compt_notation)
{
    if (board[move.ending_pos] != EMPTY || move.en_passant_pawn_eaten < BOARD_SIZE)
    {                     
        if (*compt_notation == 0){
            notation[(*compt_notation)++] = getCol(move.initial_pos); 
        }          
        notation[(*compt_notation)++] = 'x'; 
    }
    notation[(*compt_notation)++] = getCol(move.ending_pos); 
    notation[(*compt_notation)++] = '8' - move.ending_pos/8; 
}

void decodeMove(move_t move, uint8_t *board, char *notation)
{
    int compt = 0;

    pieceToMoveNotation(notation, move, board, &compt);
    targetMoveNotation(notation, move, board, &compt);
    if (move.check == 1){
        notation[compt++] = '+';
    } else if (move.check == 2){
        notation[compt++] = '#';
    }
    if (move.en_passant_pawn_eaten < BOARD_SIZE)
    {
        notation[compt++] = ' ';
        notation[compt++] = 'e';
        notation[compt++] = '.';
        notation[compt++] = 'p';
    }
    notation[compt] = '\0';
}