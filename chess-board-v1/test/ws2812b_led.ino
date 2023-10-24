#include <FastLED.h>

// Define the LED strip parameters
#define NUM_LEDS 8
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(40);

  // Initialize all LEDs to be off (black)
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // Light each LED with a different color
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Blue;
  leds[3] = CRGB::Yellow;
  leds[4] = CRGB::Purple;
  leds[5] = CRGB::Cyan;
  leds[6] = CRGB::Orange;
  leds[7] = CRGB::Pink;

  // Show the LEDs
  FastLED.show();

  // Delay for a while (adjust as needed)
  delay(500);

  // Turn off all LEDs
  FastLED.clear();
  FastLED.show();

  // Delay again or perform other tasks as needed
  delay(100);
}
