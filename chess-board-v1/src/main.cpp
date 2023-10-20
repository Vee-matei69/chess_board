
#include "Arduino.h"
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

// reed switches 


/* class to define chess piece */
// class Pawn{
//   public:
//     int color;
//     char name[10];
//     bool moved;
//     bool lifted;
//     Position piece_position;
    
//     void forward();
//     void capture();
//     void checkmate();
//     void captured();
// };

// create pieces subclasses
// class Pawn : public Piece {
//   public:
//     const  possible_moves[2] = {
//         "forward",
//         "diagonal",
//     } 
// };

/**
  * Initilize the board structure, shape, no of cols and rows
  *
  *
  */
// class Board{

//   int board[ROWS][COLS];
//   int pieces = NO_OF_PIECES;
  
//   Position piece_position; 

// };

/* initial states of all the squares */
bool a1CurrentState, a1PreviousState;

enum PIECE_VALUES{
  PAWN =1,
  KNIGHT = 2,
  BISHOP = 3,
  ROOK = 4,
  QUEEN = 5,
  KING = 6
};

/* hold piece properties */
class Piece {
  public:
    uint8_t piece_value = 0;  // no piece placed here by default

};

/* create chess pieces */
/*================== PAWN ========================*/
class Pawn: public Piece{
  String validMoves[2] = {"forward", "diagonal"};
};

/* hold the properties of a single square */
class Square{
  public:
    String address = "";
    uint8_t reedPin;
    uint8_t ledPin;
    uint8_t piece = 0;
    bool previous_state;
    bool current_state; 

    /* check if the square is occupied*/
    bool isInitiallyOccupied(){

      if(digitalRead(this->reedPin) == 0){

        current_state = true;  // true represents an occupied square and 0 respresents a "not occupied" square
        previous_state = current_state; // same in the beginning

        return true;
      } else {
        current_state = false;
        previous_state = current_state; // same in the beginning

        return false;
      }
    }

    /* check if this square is occupied at this moment */
    bool isOccupiedNow(){
      if(digitalRead(this->reedPin) == 0){
        current_state = true; // piece is still on the square
      } else {
        current_state = false; // the piece has been lifted
      }
    }

    /* check the current state of a sqaure*/
    bool getCurrentState(){
      isOccupiedNow();

      return this->current_state;
    }

    /* check the previous state of a sqaure*/
    bool getPreviousState(){
      return this->previous_state;
    }

    /* light LED */
    void lightLED(){
      digitalWrite(this->ledPin, HIGH);
    }

};


// create a square
Square A_1;

void initializeBoard(){  

  /* initialize square A_1*/
  A_1.reedPin = 2;
  A_1.ledPin = 14;
  
  if(A_1.isInitiallyOccupied()){
    A_1.lightLED();
  }

  A_1.piece = PIECE_VALUES::PAWN; /* initial piece is a PAWN */

  a1CurrentState = A_1.getCurrentState();
  a1PreviousState = A_1.getPreviousState();

  Serial.println(a1CurrentState);
  Serial.println(a1PreviousState);

}

void initializePins(){
  int no_of_pins = sizeof(pins)/sizeof(int);
  
  for(int i=0; i < no_of_pins; i++){
    pinMode(pins[i], INPUT);
  }

}

void setup(){
  Serial.begin(9600);
  
  initializePins();
  initializeBoard();
   
}

void loop(){

  // if(A_1.isInitiallyOccupied()){
  //   // this square has a piece on it at the beginning, so current state is true
  //   a1CurrentState = true;

  //   // set previous and current state the same in the beginning
  //   a1PreviousState = a1CurrentState;

  //   Serial.println("Piece initialized");

  // } else {

  
    if(A_1.isOccupiedNow()){
        a1PreviousState = a1CurrentState;
    }

    if(A_1.getCurrentState() != a1PreviousState){
      Serial.println("Lifted");
    } else {
      Serial.println("No change");
    }
  


}
