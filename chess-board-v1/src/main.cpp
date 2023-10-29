
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

/* initial states of all the squares */
bool a1CurrentState, a1PreviousState;

// enum PIECE_VALUES{
//   PAWN =1,
//   KNIGHT = 2,
//   BISHOP = 3,
//   ROOK = 4,
//   QUEEN = 5,
//   KING = 6
// };

#define PAWN 1
#define KNIGHT  2
#define BISHOP  3
#define ROOK  4
#define QUEEN  5
#define KING  6

/**
 * @brief each piece has a name
 * each piece has a square it is currently on - defined by (row,col)
 * each piece has a square it was previously on - defined by (row,col)
 * each piece has its own valid moves
 * 
 */
typedef struct piece{
  char name; // what piece it is
  char side; // side = 1(WHITE), -1(BLACK)
  char xpos; // ranges between A and H (A=0, H=7)
  char ypos; // ranges between 1 and 8 (1=0, 8=7)
  char moved; // 1 - has moved this game

} piece; 

piece* board[8][8] = {0}; // initialize a 8x8 board of pieces

void initializeBoard(){  
  piece* pawn;
  piece* rook;
  piece* knight;
  piece* bishop;
  piece* queen;
  piece* king;

  char side_loop = -1;

  // initialize white pawns
  uint8_t i, j;

  for(j = 1; j < 8; j+=5){
    side_loop = side_loop * -1; // side_lopp = 1
    for(int i=0; i< 8; i++){
      pawn = (piece*) malloc(sizeof(piece)); // allocate memory for a single piece
      board[j][i] = pawn;
      //pawn->name = PIECE_VALUES::PAWN;
      pawn->name = PAWN;
      pawn->side = side_loop;
      pawn->xpos = i;
      pawn->ypos = j;

    }
    
  }

  // initialize rooks
  side_loop = -1;
  for(j=0; j <8; j+=7){
    side_loop = side_loop * -1;
    for(i=0; i<8; i+=7){
      rook = (piece*) malloc(sizeof(piece));
      board[j][i] = rook;
      // rook->name = PIECE_VALUES::ROOK;
      rook->name = ROOK;
      rook->side = side_loop;
      rook->xpos = i;
      rook->ypos = j;
      rook->moved = 0;
    }

  }

  // initialize knights
  side_loop = -1;
  for(j=0; j < 8; j+=7){
    side_loop = side_loop * -1;
    for(i = 1; i<8; i+=5){
      knight = (piece*) malloc(sizeof(piece));
      board[j][i] = knight;
      // knight->name = PIECE_VALUES::KNIGHT;
      knight->name = KNIGHT;
      knight->side = side_loop;
      knight->xpos = i;
      knight->ypos = j;

    }
  }

  // initialize bishop
  side_loop = -1;
  for(j=0; j < 8; j+=7){
    for(i = 2; i < 8; i+=3){
      bishop = (piece*) malloc(sizeof(piece));
      board[j][i] = bishop;
      // bishop->name = PIECE_VALUES::BISHOP;
      bishop->name = BISHOP;
      bishop->side = side_loop;
      bishop->xpos = i;
      bishop->ypos = j;

    }
  }

  // initialize queen
  side_loop = -1;
  for(j=0; j < 8; j += 7){
    side_loop = side_loop * -1;
    queen = (piece*) malloc(sizeof(piece));
    board[j][3] = queen;
    // queen->name = PIECE_VALUES::QUEEN;
    queen->name = QUEEN;
    queen->side = side_loop;
    queen->ypos = j;
    queen->xpos = 3;
  }

  // initialize king
  side_loop = -1;
  for(int j =0; j < 8; j+=7){
    side_loop = side_loop * -1;
    king = (piece*) malloc(sizeof(piece));
    board[j][4] = king;
    // king->name = PIECE_VALUES::KING;
    king->name = KING;
    king->side = side_loop;
    king->xpos = 4;
    king->ypos = j;
    king->moved = 0; 

  }

}

void initializePins(){
  int no_of_pins = sizeof(pins)/sizeof(int);
  
  for(int i=0; i < no_of_pins; i++){
    pinMode(pins[i], INPUT);
  }

}

void setup(){
  Serial.begin(9600);
  delay(200);

  // initialize chess matrix
  //matrix.init_pins();
  for(int i=0; i<col_count; i++){
    pinMode(cols[i], INPUT_PULLUP);
  }

  // set up row pins as INPUTS
  for(int i= 0; i<row_count; i++){
    pinMode(rows[i], INPUT);
  }

  Serial.println("Intialized");

  initializeBoard();

  // print initial baord setup
  for (int j = 0; j < 8; j++){ // rows
    /* code */
    for (int i = 0; i < 8; i++){ // columns
      /* code */
      Serial.print(board[j][i]->name); Serial.print(" | ");
    }

    Serial.println();
    
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
