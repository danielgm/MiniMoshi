
#include <OctoWS2811.h>

const int ledsPerStrip = 24;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_RGB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  leds.begin();
  leds.show();
}

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF

int currLED = 0;

void loop() {
  for (int i = 0; i < leds.numPixels(); i++) {
    if (i == currLED) {
      if (i % 5 == 0) {
        leds.setPixel(i, RED);
      }
      else {
        leds.setPixel(i, BLUE);
      }
    }
    else {
      leds.setPixel(i, GREEN);
    }
  }
  leds.show();
  delayMicroseconds(2000000);

  currLED++;
  if (currLED >= ledsPerStrip) {
    currLED = 0;
  }
}

void colorWipe(int color) {
  for (int i = 0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
    leds.show();
  }
}
