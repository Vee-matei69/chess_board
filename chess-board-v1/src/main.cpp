
#include "Arduino.h"
#include "defs.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// CHESS board initialization pins - for rows and columns
int pins[4] = {2, 3, 4, 5};

// OLED screen variables
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define col_offset 10 // offset to arrange board layout on the screen

#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// matrix code
#define NO_OF_ROWS 8
#define NO_OF_COLS 8

byte rows[] = {2,3,4,5,6,7,8,9};
const int row_count = sizeof(rows)/sizeof(rows[0]);

byte cols[] = {10,11,12,13,14,15,16,17};
const int col_count = sizeof(cols)/sizeof(cols[0]);
byte keys[col_count][row_count];
byte previous_matrix[row_count][col_count];

// LED matrix variables
#define LED_PIN 52       // Define the digital pin connected to the data input of the NeoPixel strip.
#define NUM_LEDS 64      // Define the number of LEDs in your strip.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// set up LED control matrixes - control in groups of 8
int leds[col_count][row_count] = { // each LED for each row
  {0,1,2,3,4,5,6,7},
  {15,14,13,12,11,10,9,8 },// reverse-mapped
  {16,17,18,19,20,21,22,23},
  {31,30,29,28,27,26,25,24},// reverse-mapped
  {32,33,34,35,36,37,38,39},
  {47,46,45,44,43,42,41,40}, // reverse-mapped
  {48,49,50,51,52,53,54,55},
  {63,62,61,60,59,58,57,56} // reverse-mapped
};

/* initialize oled screen */
void initialize_oled(){
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    debugln("[-]ERR: Display allocation failed!");
    for(;;);
  }
  
  // allocation succeeded - buffer initial contents
  debugln("display found");
  display.clearDisplay();
}

void readMatrix(){
  // iterate thru the columns
  for(int col_index=0; col_index<col_count; col_index++){
    byte current_column = cols[col_index];
    pinMode(current_column, OUTPUT);
    digitalWrite(current_column, LOW);

    //iterate thru the rows 
    for(int row_index=0; row_index<row_count;row_index++){
      byte row_col = rows[row_index];
      pinMode(row_col, INPUT_PULLUP); // enable the pull up resistor
      keys[col_index][row_index] = digitalRead(row_col);
      pinMode(row_col, INPUT); // disable the pull up resistor
    }

    pinMode(current_column, INPUT); // disable the column
  }
}

void printMatrix(){
  for(int row_index=0; row_index<row_count; row_index++){
    if(row_index < 10){
      Serial.print(F("0"));
    }
    Serial.print(row_index); Serial.print(F(":"));

    // check each column
    for(int col_index=0; col_index<col_count; col_index++){
      Serial.print(keys[col_index][row_index]);
      if(col_index < col_count){
        Serial.print(F(", "));
      }
    }
    Serial.println();
  }
  Serial.println();

}

/* enum to store chess piece colors */
// enum COLOR{
//   WHITE,
//   BLACK
// };

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
  
  // initialize chess matrix
  //matrix.init_pins();
  for(int i=0; i<col_count; i++){
    pinMode(cols[i], INPUT_PULLUP);
  }

  for(int i=0; i<row_count; i++){
    pinMode(rows[i], INPUT);
  }

  // initialize LED strip
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'

}

void loop(){
  readMatrix();

  if(Serial.read() == '!'){
    printMatrix();
    //update_display();

    // light LEDS for the unoccupied cells
    for(int row=0; row<row_count; row++){
      for(int col=0; col<col_count; col++){
        if(keys[col][row] == 1){
          //1  means unoccupied cell - light LED
          
          strip.setPixelColor(leds[row][col], strip.Color(255, 50, 50));
        } else {
          strip.setPixelColor(leds[row][col], strip.Color(0,0,0));
        }

        strip.show();
      }

      
    }

    // strip.setPixelColor(leds[7][7], strip.Color(0, 255, 0));
    // // strip.setPixelColor(leds[1][1], strip.Color(0, 255, 0));
    // strip.show();

  }

  // test the LED matrix
  // for(int i=0;i<8; i++){
  //   strip.setPixelColor(pxl1[i], strip.Color(255, 50, 50));
  //   strip.setPixelColor(pxl2[i], strip.Color(255, 255, 50));
  //   strip.show();
  //   delay(50);
  // }


  // if(A_1.isInitiallyOccupied()){
  //   // this square has a piece on it at the beginning, so current state is true
  //   a1CurrentState = true;

  //   // set previous and current state the same in the beginning
  //   a1PreviousState = a1CurrentState;

  //   Serial.println("Piece initialized");

  // } else {

  
  // if(A_1.isOccupiedNow()){
  //     a1PreviousState = a1CurrentState;
  // }

  // if(A_1.getCurrentState() != a1PreviousState){
  //   Serial.println("Lifted");
  // } else {
  //   Serial.println("No change");
  // }  



}
