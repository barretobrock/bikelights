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
CHSV blk(0, 0, 0);
CHSV red(0, 255, 255);
CHSV prp(192, 255, 255);
//CHSV org(32, 255, 255);
CHSV ylw(50, 255, 255);
CHSV grn(96, 255, 255);

void light_order(CHSV col, uint32_t delay_ms) {
    for (int i=0; i<TT_LEDS; i++) {
        // TT_LEDS are the longest, so inside this loop, handle other strips by checking their length against i
        ttleds[i] = col;
        if (i<DT_LEDS) { dtleds[i] = col;}
        if (i<RR_LEDS) { rrleds[i] = col;}
        if (i<SS_LEDS) { ssleds[i] = col;}
        if (i<LR_LEDS) { lrleds[i] = col;}
    }
    FastLED.show();
    delay(delay_ms);
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
    // Wait 3s before starting up to ensure system's ready
    delay(3000);
    startup(grn, prp, red, 500);
}

void startup(CHSV col1, CHSV col2, CHSV col3, uint32_t delay_ms) {
    // Do something different at startup
    light_order(col1, delay_ms);
    light_order(col2, delay_ms);
    light_order(col3, delay_ms);
}

void quick_blink(CHSV col1, CHSV col2, uint8_t n_times, uint8_t delay_ms) {
    // Produces a fast round of blinks alternating between two colors
    for (int i=0; i<n_times; i++) {
        light_order(col1, delay_ms);
        light_order(col2, delay_ms);
    }
}

void single_color_cycle(CHSV col, uint32_t secs, uint32_t blink_every_s) {
    uint8_t total_cycles = ceil(secs / blink_every_s);
    for (int i=0; i<total_cycles; i++) {
        light_order(col, blink_every_s * 1000);
        quick_blink(blk, col, 10, 50);
    }
}

// main program
void loop() {
    single_color_cycle(red, 300, 10);
    single_color_cycle(prp, 120, 10);
    single_color_cycle(grn, 60, 10);
    single_color_cycle(ylw, 60, 10);
}