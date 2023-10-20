#include "chessmatrix.h"

// class implementation
ChessMatrix::ChessMatrix(int c0, int c1,int c2, int c3, int c4, int c5, int c6, int c7, int r0,int r1,int r2,int r3, int r4,int r5,int r6,int r7){

    // assign pins to local variables 

    // assign  columns
    this->_c0 = c0;
    this->cols[0] = this->_c0;
    this->_c1 = c1;
    this->cols[1] = this->_c1;
    this->_c2 = c2;
    this->cols[2] = this->_c2;
    this->_c3 = c3;
    this->cols[3] = this->_c3;
    this->_c4 = c4;
    this->cols[4] = this->_c4;
    this->_c5 = c5;
    this->cols[5] = this->_c5;
    this->_c6 = c6;
    this->cols[6] = this->_c6;
    this->_c7 = c7;
    this->cols[7] = this->_c7;

    // assign rows
    this->_r0 = r0;
    this->_r1 = r1;
    this->_r2 = r2;
    this->_r3 = r3;
    this->_r4 = r4;
    this->_r5 = r5;
    this->_r6 = r6;
    this->_r7 = r7;

    this->NO_OF_COLUMNS = 8;
    this->NO_OF_ROWS = 8;

    // initialize the board cells matrix
    this->board_cells[NO_OF_COLUMNS][NO_OF_ROWS];
    
}

/**
 * Set up pins as inputs and outputs
 * Columns -> outputs
 * Rows -> inputs
 */
void ChessMatrix::init_pins(){
  pinMode(_c0, OUTPUT);
  pinMode(_c1, OUTPUT);
  pinMode(_c2, OUTPUT);
  pinMode(_c3, OUTPUT);
  pinMode(_c4, OUTPUT);
  pinMode(_c5, OUTPUT);
  pinMode(_c6, OUTPUT);
  pinMode(_c7, OUTPUT);

  pinMode(_r0, INPUT); 
  pinMode(_r1, INPUT); 
  pinMode(_r2, INPUT); 
  pinMode(_r3, INPUT); 
  pinMode(_r4, INPUT); 
  pinMode(_r5, INPUT); 
  pinMode(_r6, INPUT); 
  pinMode(_r7, INPUT); 

}

/**
 * Scan the matrix
 */

void ChessMatrix::scan(){
  // iterate thru columns
  for(int col_index=0; col_index < this->NO_OF_COLUMNS; col_index++){
    byte current_column = this->cols[col_index];
    // column is already set as OUTPUT

    // drive column LOW
    digitalWrite(current_column, LOW);

    // iterate thru rows
    for(int row_index=0; row_index < this->NO_OF_ROWS; row_index++){
      byte row_col = rows[row_index];
      pinMode(row_col, INPUT_PULLUP);

      board_cells[col_index][row_index] = digitalRead(row_col);
      pinMode(row_col, INPUT);
    }

    // disable the column
    pinMode(current_column, INPUT);
    
  }
}

void ChessMatrix::print_matrix(){
  for(int row_index=0; row_index < this->NO_OF_ROWS; row_index++){
    if(row_index < 10){
      Serial.print(F("0"));
    }

    Serial.print(row_index); Serial.print(F(": "));

    for(int col_index=0; col_index < this->NO_OF_COLUMNS; col_index++){
        Serial.print(board_cells[col_index][row_index]);
        if(col_index < this->NO_OF_COLUMNS){
          Serial.print(F(", "));
        }
      }

      Serial.println(" ");
    }

    Serial.println(" ");
    
  }
