
#include <OctoWS2811.h>

const int ledsPerStrip = 24;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_RGB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  pinMode(0, INPUT_PULLUP);

  leds.begin();
  leds.show();

  randomSeed(analogRead(1));
}

#define BLACK  0x000000
#define RED    0xFF0000
#define GREEN  0x00FF00
#define BABYBLUE   0x6666FF
#define BLUE   0x0000FF
#define YELLOW 0xFF9900
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF

#define RANDOM_WALK_MODE 0
#define H_SLICE_MODE 1
#define V_SLICE_MODE 2
#define D0_SLICE_MODE 3
#define D1_SLICE_MODE 4
#define D2_SLICE_MODE 5
#define D3_SLICE_MODE 6
#define RANDOM_MODE 7
#define VARI_SLICE_MODE 8
#define INFECT_MODE 9
#define FADE_MODE 10

int drawMode = RANDOM_WALK_MODE;

int sliceLen = 9;

int numHSlices = 4;
int hSlices[10][9] {
  { 0,  7,  8, 11, 12, 18, 19, -1, -1},
  { 2,  5,  6, 14, 15, 16, 17, 20, 21},
  { 1,  9, 10, 13, 22, 23, -1, -1, -1},
  { 3,  4, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int numVSlices = 6;
int vSlices[10][9] {
  { 0,  1, -1, -1, -1, -1, -1, -1, -1},
  { 2,  3,  4,  5,  6, -1, -1, -1, -1},
  { 7,  8,  9, 10, 11, 12, 13, -1, -1},
  {14, 15, 16, 17, -1, -1, -1, -1, -1},
  {18, 19, 22, 23, -1, -1, -1, -1, -1},
  {20, 21, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int numD0Slices = 6;
int d0Slices[10][9] = {
  { 6,  7, -1, -1, -1, -1, -1, -1, -1},
  { 0,  5,  8, -1, -1, -1, -1, -1, -1},
  { 1,  2,  4,  9, 11, 17, -1, -1, -1},
  { 3, 10, 12, 16, 18, -1, -1, -1, -1},
  {13, 15, 19, 21, 22, -1, -1, -1, -1},
  {14, 20, 23, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int numD1Slices = 9;
int d1Slices[10][9] = {
  { 1, -1, -1, -1, -1, -1, -1, -1, -1},
  { 0,  3, -1, -1, -1, -1, -1, -1, -1},
  { 2,  4, 13, -1, -1, -1, -1, -1, -1},
  { 5, 10, 12, 14, -1, -1, -1, -1, -1},
  { 6,  9, 11, 15, -1, -1, -1, -1, -1},
  { 8, 16, 23, -1, -1, -1, -1, -1, -1},
  { 7, 17, 19, 22, -1, -1, -1, -1, -1},
  {18, 20, -1, -1, -1, -1, -1, -1, -1},
  {21, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int numD2Slices = 10;
int d2Slices[10][9] = {
  { 0, -1, -1, -1, -1, -1, -1, -1, -1},
  { 1, -1, -1, -1, -1, -1, -1, -1, -1},
  { 2, 12, -1, -1, -1, -1, -1, -1, -1},
  { 3,  5, 11, 13, 14, -1, -1, -1, -1},
  { 4,  6,  8, 10, 15, -1, -1, -1, -1},
  { 7,  9, 16, 19, -1, -1, -1, -1, -1},
  {17, 18, 23, -1, -1, -1, -1, -1, -1},
  {22, -1, -1, -1, -1, -1, -1, -1, -1},
  {20, -1, -1, -1, -1, -1, -1, -1, -1},
  {21, -1, -1, -1, -1, -1, -1, -1, -1}
};

int numD3Slices = 6;
int d3Slices[10][9] = {
  { 4,  6, -1, -1, -1, -1, -1, -1, -1},
  { 1,  3,  5,  7,  9, -1, -1, -1, -1},
  { 0,  2,  8, 10, 17, -1, -1, -1, -1},
  {11, 13, 16, 22, -1, -1, -1, -1, -1},
  {12, 15, 18, 21, 23, -1, -1, -1, -1},
  {14, 19, 20, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int numRhombododdies = 24;
int numSides = 12;
int walkData[24][12] = {
  { 1,  2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  { 0,  2,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  { 0,  1,  3,  5, 10, 11, 12, 13, -1, -1, -1, -1},
  { 1,  2,  4, 10, 13, -1, -1, -1, -1, -1, -1, -1},
  { 3,  5,  9, 10, -1, -1, -1, -1, -1, -1, -1, -1},
  { 2,  4,  6,  8,  9, 10, 11, -1, -1, -1, -1, -1},
  { 5,  7,  8,  9, -1, -1, -1, -1, -1, -1, -1, -1},
  { 6, 17,  8, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  { 5,  6,  7,  9, 11, 17, 16, -1, -1, -1, -1, -1},
  { 4,  5,  6,  8, 10, 16, 17, -1, -1, -1, -1, -1},
  { 2,  3,  4,  5,  9, 11, 13, 15, 16, -1, -1, -1},
  { 2,  5,  8, 10, 12, 15, 16, -1, -1, -1, -1, -1},
  { 2, 11, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1},
  { 2,  3, 12, 10, 14, 15, -1, -1, -1, -1, -1, -1},
  {12, 13, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {10, 11, 12, 13, 14, 16, 19, 23, -1, -1, -1, -1},
  { 8,  9, 10, 11, 15, 17, 18, 19, 20, 22, -1, -1},
  { 7,  8,  9, 16, 18, 22, -1, -1, -1, -1, -1, -1},
  {16, 17, 19, 20, 21, 22, -1, -1, -1, -1, -1, -1},
  {15, 16, 18, 20, 23, -1, -1, -1, -1, -1, -1, -1},
  {18, 19, 21, 22, 23, -1, -1, -1, -1, -1, -1, -1},
  {18, 20, 22, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {16, 17, 18, 20, 21, 23, -1, -1, -1, -1, -1, -1},
  {15, 16, 19, 20, 22, -1, -1, -1, -1, -1, -1, -1}
};

int prevIndex = 0;
int currIndex = 0;

int maxInfections = 9;

int prevNumInfections = 1;
int prevInfections[9] = {15, -1, -1, -1, -1, -1, -1, -1, -1};

int numInfections = 1;
int infections[9] = {15, -1, -1, -1, -1, -1, -1, -1, -1};

int fadeSteps = 16;
int fadeDir = 1;

void loop() {
  if (isActive()) {
    drawMode = RANDOM_MODE;
  }
  else {
    drawMode = INFECT_MODE;
  }

  switch (drawMode) {
    case RANDOM_WALK_MODE:
      loopWalk();
      break;
    case H_SLICE_MODE:
      loopSlice(hSlices, numHSlices);
      break;
    case V_SLICE_MODE:
      loopSlice(vSlices, numVSlices);
      break;
    case D0_SLICE_MODE:
      loopSlice(d0Slices, numD0Slices);
      break;
    case D1_SLICE_MODE:
      loopSlice(d1Slices, numD1Slices);
      break;
    case D2_SLICE_MODE:
      loopSlice(d2Slices, numD2Slices);
      break;
    case D3_SLICE_MODE:
      loopSlice(d3Slices, numD3Slices);
      break;
    case RANDOM_MODE:
      loopRandom();
      break;
    case VARI_SLICE_MODE:
      loopVariSlice();
      break;
    case INFECT_MODE:
      loopInfect();
      break;
    case FADE_MODE:
      loopFade();
      break;
  }
}

void loopWalk() {
  colorWipe(RED);
  leds.setPixel(prevIndex, BLUE);
  leds.setPixel(currIndex, WHITE);
  leds.show();
  delayMicroseconds(100000);

  int noVisitIndex = prevIndex;
  prevIndex = currIndex;
  currIndex = nextIndex(currIndex, noVisitIndex);
}

void loopSlice(int slice[10][9], int numSlices) {
  colorWipe(RED);
  colorWipeSlice(slice[currIndex], BLUE);
  leds.show();
  delayMicroseconds(1000000);

  prevIndex = currIndex;
  currIndex++;
  if (currIndex >= numSlices) {
    currIndex = 0;
  }
}

void loopRandom() {
  for (int i = 0; i < leds.numPixels(); i++) {
    int n = random(3);
    if (n < 1) {
      leds.setPixel(i, WHITE);
    }
    else if (n < 2) {
      leds.setPixel(i, RED);
    }
    else {
      leds.setPixel(i, BLUE);
    }
  }
  leds.show();
  delayMicroseconds(50000);
}

void loopVariSlice() {
  colorWipe(RED);
  switch (currIndex) {
    case 0:
      colorAltSlice(hSlices, numHSlices, BLUE);
      break;
    case 1:
      colorAltSlice(vSlices, numVSlices, BLUE);
      break;
    case 2:
      colorAltSlice(d0Slices, numD0Slices, BLUE);
      break;
    case 3:
      colorAltSlice(d1Slices, numD1Slices, BLUE);
      break;
    case 4:
      colorAltSlice(d2Slices, numD2Slices, BLUE);
      break;
    case 5:
      colorAltSlice(d3Slices, numD3Slices, BLUE);
      break;
  }

  leds.show();
  delayMicroseconds(500000);

  prevIndex = currIndex;
  currIndex++;
  if (currIndex >= 6) {
    currIndex = 0;
  }
}

void loopInfect() {
  colorWipe(PINK);
  for (int i = 0; i < prevNumInfections; i++) {
    leds.setPixel(prevInfections[i], BABYBLUE);
  }
  for (int i = 0; i < numInfections; i++) {
    leds.setPixel(infections[i], YELLOW);
  }

  leds.show();
  delayMicroseconds(100000);

  stepInfections();
}

void loopFade() {
  int c = lerpColor(RED, BLUE, (float)currIndex / fadeSteps);
  colorWipe(c);
  leds.show();
  delayMicroseconds(100000);

  if (fadeDir > 0) {
    currIndex++;
    if (currIndex >= fadeSteps) {
      fadeDir = -1;
    }
  }
  else {
    currIndex--;
    if (currIndex <= 0) {
      fadeDir = 1;
    }
  }
}

void colorAltSlice(int slice[10][9], int numSlices, int color) {
  for (int i = 0; i < numSlices; i += 2) {
    colorWipeSlice(slice[i], color);
  }
}

void colorWipe(int color) {
  for (int i = 0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
  }
}

void colorWipeSlice(int slice[10], int color) {
  for (int i = 0; i < sliceLen; i++) {
    int index = slice[i];
    if (index < 0) break;
    leds.setPixel(index, color);
  }
}

int nextIndex(int index) {
  return nextIndex(index, -1);
}

int nextIndex(int index, int noVisitIndex) {
  int numCandidates = 0;
  for (int i = 0; i < numSides; i++) {
    if (walkData[index][i] < 0) break;
    numCandidates++;
  }
  int nextIndex;
  while ((nextIndex = walkData[index][random(numCandidates)]) == noVisitIndex) {};
  return nextIndex;
}

void stepInfections() {
  prevNumInfections = numInfections;
  for (int i = 0; i < prevNumInfections; i++) {
    prevInfections[i] = infections[i];

    if (numInfections > 1 && random(8) < 1) {
      // Current infection dies.
      infections[i] = infections[numInfections - 1];
      numInfections--;
      prevNumInfections--;
    }
    else {
      if (numInfections < maxInfections && random(6) < 1) {
        // New infection.
        infections[numInfections] = nextIndex(infections[i], prevInfections[i]);
        numInfections++;
      }
      infections[i] = nextIndex(infections[i]);
    }
  }
}

int redMask = 0xFF0000, greenMask = 0xFF00, blueMask = 0xFF;
int lerpColor(int a, int b, float v) {
  int ar = (a & redMask) >> 16;
  int ag = (a & greenMask) >> 8;
  int ab = (a & blueMask);
  int br = (b & redMask) >> 16;
  int bg = (b & greenMask) >> 8;
  int bb = (b & blueMask);

  ar += (br - ar) * v;
  ag += (bg - ag) * v;
  ab += (bb - ab) * v;

  int rgb = (ar << 16) + (ag << 8) + ab;
  return rgb;
}

bool isActive() {
  return digitalRead(0) == HIGH;
}
