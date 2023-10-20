#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include "chessmatrix.h"

#define NO_OF_ROWS 8
#define NO_OF_COLS 8

ChessMatrix matrix(2,3,4,5,6,7,8,9, 10, 11, 12, 13, 14, 15, 16, 17);

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

  // invert display
  display.invertDisplay(true);
}

void setup() {
  Serial.begin(9600);
  
  // initialize chess matrix
  matrix.init_pins();
  
  initialize_oled();

  // display buffer contents
  display.display();

  for(int i = 0; i < 8; i++){
    debugln(matrix.cols[i]);
  }

  digitalWrite(matrix._c0, HIGH);
  
  for(int i=0; i < 8; i++){
    digitalWrite(matrix.cols[i], LOW);
  }
  
}

void loop() {
  
}
