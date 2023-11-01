#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
#define SSD1306_MY_RED 0xFF0000 // Red color in RGB format (red, green, blue)
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Define the size of the chessboard
const int boardSize = 8;

// Define the chessboard squares and piece positions
char chessboard[boardSize][boardSize] = {
  {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
  {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
  {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
};

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  
  display.clearDisplay();
  display.display();
  Serial.begin(9600);
}

void loop() {
  display.clearDisplay();
  drawChessboard();
  display.display();
  delay(5000); // Display for 5 seconds (adjust as needed)
}

void drawChessboard() {
  int squareSize = SCREEN_HEIGHT / boardSize;

  for (int y = 0; y < boardSize; y++) {
    for (int x = 0; x < boardSize; x++) {
      if ((x + y) % 2 == 0) {
        display.fillRect(x * squareSize, y * squareSize, squareSize, squareSize, BLACK);
      } else {
        display.fillRect(x * squareSize, y * squareSize, squareSize, squareSize,MAGENTA);
      }
      display.setCursor(x * squareSize + 3, y * squareSize + 3);
      display.setTextSize(1);
      display.setTextColor(SSD1306_BLACK);
      display.print(chessboard[y][x]);
    }
  }
}

