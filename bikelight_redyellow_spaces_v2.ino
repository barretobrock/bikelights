#include "FastLED.h"

// Data pins
#define TT_PIN 3 // Top tube + fork pin                 <green>
#define DT_PIN 4 // Down tube pin                       <blue>
#define SS_PIN 5 // Seat stays pin (seat + chain)       <brown>
#define LR_PIN 6 // Left rear rack pin (sides + back)   <lt blue>
#define RR_PIN 7 // Right rear rack pin                 <lt grn>

// LEDs
#define TT_LEDS 56
#define DT_LEDS 32
#define SS_LEDS 40
#define LR_LEDS 42
#define RR_LEDS 10

// Other settings
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 50

// Light strips
CRGB ttleds[TT_LEDS],
        dtleds[DT_LEDS],
        ssleds[SS_LEDS],
        lrleds[LR_LEDS],
        rrleds[RR_LEDS];

// Colors
CRGB blk = CRGB::Black;
CRGB red = CHSV(0, 255, 255);
CRGB prp = CHSV(192, 255, 255);
CRGB ylw = CHSV(64, 255, 255);

// Estimated span of all the leds
int totallen = 57;

void light_order(CRGB col) {
    for (int i=0; i<TT_LEDS; i++) {
        // TT_LEDS are the longest, so inside this loop, handle other strips by checking their length against i
        ttleds[i] = col;
        if (i<DT_LEDS) { dtleds[i] = col;}
        if (i<RR_LEDS) { rrleds[i] = lrleds[i] = col;}
        if (i<SS_LEDS) { ssleds[i] = col;}
        if (i<LR_LEDS) { lrleds[i] = col;}
    }
    FastLED.show();
    delay(10000);
}

void setup() {
    delay(2000);
    // Initialize LEDs
    FastLED.addLeds<LED_TYPE, TT_PIN, COLOR_ORDER>(ttleds, TT_LEDS);
    FastLED.addLeds<LED_TYPE, DT_PIN, COLOR_ORDER>(dtleds, DT_LEDS);
    FastLED.addLeds<LED_TYPE, SS_PIN, COLOR_ORDER>(ssleds, SS_LEDS);
    FastLED.addLeds<LED_TYPE, LR_PIN, COLOR_ORDER>(lrleds, LR_LEDS);
    FastLED.addLeds<LED_TYPE, RR_PIN, COLOR_ORDER>(rrleds, RR_LEDS);
    // set global brightness
    FastLED.setBrightness(BRIGHTNESS);
    // set all LEDs to black starting out
    FastLED.clear();
    delay(1000);
}


// main program
void loop() {
    light_order();
}