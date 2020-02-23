#include "FastLED.h"

// Data pins                                            wire color
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

// Matrix details
const uint8_t kMatrixWidth = 62, kMatrixHeight = 4;
const bool kMatrixSerpentineLayout = false;
int16_t matrixLayout[kMatrixHeight][kMatrixWidth] = {
        {-1, -1, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, -1, -1, 138, 139, 140, 141, 142, 143, 144, 145},
        {30, 31, 32, 33, 34, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 146, 147, 148, 149, 150, 151, 152, 153},
        {-1, -1, -1, -1, -1, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, -1, -1, -1, -1, -1, -1, -1, -1, 154, 155, 156, 157, 158, 159, 160, 161},
        {-1, -1, -1, -1, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, -1, -1, -1, -1, -1, -1, -1, -1, 162, 163, 164, 165, 166, 167, 168, 169}
};

// Controller settings
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS 50

// Light strips
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
CRGB leds_plus_safety_pixel[NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

uint16_t XY( uint8_t x, uint8_t y) {
    return matrixLayout[y][x];
}

void setup() {
    delay(2000);
    // Initialize LEDs
    FastLED.addLeds<LED_TYPE, TT_PIN, COLOR_ORDER>(leds, 0, TT_LEDS);
    FastLED.addLeds<LED_TYPE, DT_PIN, COLOR_ORDER>(leds, TT_LEDS, DT_LEDS);
    FastLED.addLeds<LED_TYPE, SS_PIN, COLOR_ORDER>(leds, TT_LEDS + DT_LEDS, SS_LEDS);
    FastLED.addLeds<LED_TYPE, LR_PIN, COLOR_ORDER>(leds, TT_LEDS + DT_LEDS + SS_LEDS, LR_LEDS);
    FastLED.addLeds<LED_TYPE, RR_PIN, COLOR_ORDER>(leds, TT_LEDS + DT_LEDS + SS_LEDS + LR_LEDS, RR_LEDS);
    // set global brightness
    FastLED.setBrightness(BRIGHTNESS);
    // set all LEDs to black starting out
    FastLED.clear();
    // Wait 3s before starting up to ensure system's ready
    delay(3000);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void cylon_single_col(CHSV col, int delay_ms) {
    for( byte x = 0; x < kMatrixWidth; x++) {
        for( byte y = 0; y < kMatrixHeight; y++) {
            leds[ XY(x, y)] = col;
        }
        FastLED.show();
        fadeall();
        delay(delay_ms);
    }
}

// main program
void loop() {

}