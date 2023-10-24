#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include "chessmatrix.h"

// ChessMatrix matrix(2,3,4,5,6,7,8,9, 10, 11, 12, 13, 14, 15, 16, 17);

/* debug directives */
#define DEBUG 1

#if DEBUG
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#define debugf(x, y) Serial.printf(x, y)

#else 

#define debug(x) 
#define debugln(x)
#define debugf(x, y)

#endif

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
#define col_offset 10 // offset to arrange board layout on the screen

#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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

// timing variables
unsigned long current_time = 0;
unsigned long previous_time = 0;
unsigned long scan_interval = 1000;

// matrix code
#define NO_OF_ROWS 8
#define NO_OF_COLS 8

byte rows[] = {2,3,4,5,6,7,8,9};
const int row_count = sizeof(rows)/sizeof(rows[0]);

byte cols[] = {10,11,12,13,14,15,16,17};
const int col_count = sizeof(cols)/sizeof(cols[0]);
byte keys[col_count][row_count];

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

void update_display(){
  display.clearDisplay();

  display.setCursor(0,0);
  display.print("hello");
  display.display();

  for(int i=0; i < row_count; i++){
    for(int j=0; j<col_count; j++){
      display.setCursor(j + col_offset, i);
      if(keys[j][i] == 0){
        // occupied
        display.print('x', WHITE);
      } else{
        display.print('-', WHITE);
      }
      
    }
  }

}

void setup() {
  Serial.begin(9600);
  
  // initialize chess matrix
  //matrix.init_pins();
  for(int i=0; i<col_count; i++){
    pinMode(cols[i], INPUT_PULLUP);
  }

  for(int i=0; i<row_count; i++){
    pinMode(rows[i], INPUT);
  }
  
  //initialize_oled();
}

void loop() {
  readMatrix();

  if(Serial.read() == '!'){
    printMatrix();
//    update_display();
  }
   
}
