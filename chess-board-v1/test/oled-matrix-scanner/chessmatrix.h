#ifndef CHESSMATRIX_H
#define CHESSMATRIX_H

#include <Arduino.h>

class ChessMatrix{
  public:
    // constructor
    ChessMatrix(int, int, int, int, int, int, int, int, int, int, int, int,int, int, int, int); 
    int _c0, _c1, _c2, _c3, _c4, _c5, _c6, _c7; // columns
    int _r0, _r1,_r2, _r3, _r4, _r5, _r6, _r7; // rows
    int NO_OF_COLUMNS;
    int NO_OF_ROWS;
    byte board_cells[8][8];
        
    int rows[8];
    int cols[8];
    void init_pins();
    void scan();
    void print_matrix();
    
};

#endif
