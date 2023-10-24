#include <Adafruit_NeoPixel.h>

#define LED_PIN 52       // Define the digital pin connected to the data input of the NeoPixel strip.
#define NUM_LEDS 64      // Define the number of LEDs in your strip.

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// set up LED control matrixes
int pxl1[] = {0,1,2,3,4,5,6,7};
int pxl2[] = {8,9,10,11,12,13,14,15};
int pxl3[] = {16,17,18,19,20,21,22,23};
int pxl4[] = {24,25,26,27,28,29,30,31};
int pxl5[] = {32,33,34,35,36,37,38,39};
int pxl6[] = {40,41,42,43,44,45,46,47};
int pxl7[] = {48,49,50,51,52,53,54,55};
int pxl8[] = {56,57,58,59,60,61,62,63};

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
//  for(int i=0;i<8; i++){
//    strip.setPixelColor(pxl1[i], strip.Color(255, 50, 50));
//    strip.show();
//    delay(50);
//  }

  strip.setPixelColor(pxl1[i], strip.Color(255, 50, 50));
  
  // Set all LEDs to green
  // colorWipe(strip.Color(255, 50, 50), 50);  // Green color with a 50ms delay between LEDs
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t color, int wait) {
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}
