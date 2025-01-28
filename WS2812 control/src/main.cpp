//WS2812灯珠控制

#include <Arduino.h>
#include <fastled.h>

#define LED_PIN 48
#define NUM_LED 1
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB


CRGB leds[NUM_LED];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LED);
  FastLED.setBrightness(10);
  FastLED.clear();
  FastLED.show();

}

void loop() {
  leds[0] = CRGB::MediumOrchid;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Moccasin;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(500);
}