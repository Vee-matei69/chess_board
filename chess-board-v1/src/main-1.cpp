#include "defs.h"

// pins
int pins[4] = {2, 3, 4, 5};

/* enum to store chess piece colors */
enum COLOR{
  WHITE = 1,
  BLACK = 0
};

enum SIDE{
  WHITE_SIDE = 1,
  BLACK_SIDE = 0
};

enum piece_values{}; // todo: add later


typedef struct {
  int row, col;
} Position;


/* class to define chess piece */
class Piece{
  public:
    int color;
    char name[10];
    bool moved;
    bool lifted;
    Position piece_position;
    
    void forward();
    void capture();
    void checkmate();
    void captured();
};

// create pieces subclasses
class Pawn extends Piece{
  public:
    char possible_moves[4] = {
        "forward",
        "diagonal",
    } 
};

/**
  * Initilize the board structure, shape, no of cols and rows
  *
  *
  */
class Board{

  int board[ROWS][COLS];
  int pieces = NO_OF_PIECES;
  
  Position piece_position; 

};

/* player class */
class Player{
  int side;
  
  
};

/**
 * Initialize board before game
 */
void initializePieces(){  
  
  /**
   * Initialize pieces
   */
  /* instantiate a pawn object */
  Piece pawn;
  pawn.lifted = false; // the pawn is not moved initially
  pawn.piece_position.row = 0;
  pawn.piece_position.col = 0;
  
  /* ========= END ====== */
  
  // todo: initialize all the remaining pieces
  
}

/**
 * Initialize players
 */
void initializePlayers(){
  
  Player white_player, black_player;
  
}

void initializePins(){
  int no_of_pins = sizeof(pins)/sizeof(int);
  
  for(int i=0; i < no_of_pins; i++){
    pinMode(pins[i], INPUT);
  }
  
}

void setup(){
  
  initializePieces();
   
}

void loop(){
  
  // simulate a lift
  if(digitalRead(pins[0])){
    // pawn has been lifted
    pawn.lifted = true;
    
    // light leds to show possible move positions
    
    
  } else {
    pawn.lifted = false;
  }
  
  
  
}
