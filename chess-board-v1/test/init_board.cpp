#include <stdio.h>
#include <string.h>

#define ROWS 8
#define COLS 8

typedef struct piece{
    char name;
    int row_pos;
    int col_pos;
    int side;
} Piece;

Piece* board[ROWS][COLS] = {};

/* functions prototypes */
/* end of functions prototypes */

/* function definitions */
void printBoard(int rows, int cols){

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            /* get the piece name*/
            // printf("%p  ", board[i][j]);
            printf("%c ", (board[i][j])->name);

        }

        printf("\n");
    }
}

void createPieces(int rows, int cols){

    Piece* empty_piece;
    Piece* pawn;
    Piece* rook;
    Piece* bishop;
    Piece* knight;
    Piece* queen;
    Piece* king;

    for(int r = 0; r < rows; r++){
        if (r != 1){
            for(int c = 0; c < cols; c++){
                
                /* create a place holder piece */
                empty_piece = new Piece;
                empty_piece->name = 'X';

                *(*(board + r) + c) = empty_piece;
            }

        } else{
             for(int c = 0; c < cols; c++){

                // create pawn
                pawn = new Piece;
                pawn->name = 'P';

                *(*(board + r) + c) = pawn;
                // printf("%p ", pawn);
            }
        }
    }
}

/* end of function definitions */

int main(){
    
    /* print board layout */
    // printBoard(board[0], ROWS, COLS);

    /* create pieces */
    createPieces(ROWS, COLS);

    /* print board layout */
    printBoard(ROWS, COLS);

}