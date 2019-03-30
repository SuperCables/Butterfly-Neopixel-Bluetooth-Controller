#include <FastLED.h>

CHSV GetLEDSpreadPallet(CHSVPalette16 palette, uint16_t i, byte shift = 0);

#define LED_PIN     2
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    25
CRGB rgbOutput[NUM_LEDS];
CHSV leds[NUM_LEDS];

byte Respond = 0;
char BluetoothData;
int Debug[10];
//0 - 
//1 - 
//2 - 
//3 - 
//4 - 
//5 - 
//6 - 
//7 - 
//8 - 
//9 - 
//clock
uint64_t ms = millis();
uint64_t ts = 0;
uint64_t lastFrame = 0;
uint64_t lastRippleDamp = 0;
uint64_t lastPaletteFade = 0;
uint64_t lastButtonPress = 0;
uint64_t lastRipplePulse = 0;

//Palettes
CHSVPalette16 basePalette;
CHSVPalette16 nextBasePalette;

CHSVPalette16 ripplePalette;
CHSVPalette16 nextRipplePalette;

CHSVPalette16 incomingPalette;

//CHSVPalette16

// This is the array that we keep our computed noise values in
uint8_t noise[NUM_LEDS];

//noise shift paramiters
int tmpSpeedDampThingyBiasWhatever = 250; //Is this value good?
int timeScale = 450;
int spaceScale = 311;

//Primary
byte brightness = 128;
int HueSpread = 13;
byte nextPaletteSpeed = 0;

//For Ripple Layer
int rippleVelocityDamp = 150;
int rippleForceDamp = 16;
int rippleSpeedDamp = 32;
byte rippleMinBrightness = 75;
uint64_t rippleInterval = 25000;

//ripple
byte pulse = 0;
int ripplepos;

//twinkle
byte twinkleChance = 7;

//simple mode
byte hue1 = 41;
byte hue2 = 210;

void setup() {
  pinMode(7, INPUT_PULLUP); //button
  pinMode(8, INPUT_PULLUP); //switch1
  pinMode(9, INPUT_PULLUP); //switch2
  Serial.begin(9600);
  //Serial.begin(115200);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(rgbOutput, NUM_LEDS).setCorrection(TypicalSMD5050);
  //FastLED.setBrightness(75);
  //FastLED.setDither(0);
  FastLED.show();

  Serial.println(F("Boot"));

  basePalette = SetupRoyalPurplePalette();
  nextBasePalette = SetupGoldenPeachPalette();
  ripplePalette = SetupGoldenPeachPalette();
  nextRipplePalette = SetupRoyalPurplePalette();

}

