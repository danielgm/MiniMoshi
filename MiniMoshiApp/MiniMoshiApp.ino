
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

int sliceLen = 9;

int numHSlices = 4;
int hSlices[4][9] {
  {0, 7, 8, 11, 12, 18, 19, -1, -1},
  {2, 5, 6, 14, 15, 16, 17, 20, 21},
  {1, 9, 10, 13, 22, 23, -1, -1, -1},
  {3, 4, -1, -1, -1, -1, -1, -1, -1},
};

int numVSlices = 6;
int vSlices[6][9] {
  {0, 1, -1, -1, -1, -1, -1, -1, -1},
  {2, 3, 4, 5, 6, -1, -1, -1, -1},
  {7, 8, 9, 10, 11, 12, 13, -1, -1},
  {14, 15, 16, 17, -1, -1, -1, -1, -1},
  {18, 19, 22, 23, -1, -1, -1, -1, -1},
  {20, 21, -1, -1, -1, -1, -1, -1, -1}
};


int currLED = 0;
int currSlice = 0;

void loop() {
  colorWipe(WHITE);
  for (int i = 0; i < sliceLen; i++) {
    int index = vSlices[currSlice][i];
    if (index >= 0) {
      leds.setPixel(index, RED);
    }
  }
  leds.show();
  delayMicroseconds(2000000);

  currSlice++;
  if (currSlice >= numVSlices) {
    currSlice = 0;
  }
}

void colorWipe(int color) {
  for (int i = 0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
  }
}
