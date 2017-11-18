//Squish Pond for Undetermined Origins, Future[tbd]Collective, East Austin Studio Tour 2017 - 
//Debra Lemak 11/16/17

#include "FastLED.h"

#define NUM_LEDS_PER_STRIP 5
#define NUM_STRIPS 3
#define NUM_LEDS NUM_LEDS_PER_STRIP*NUM_STRIPS
#define LED_TYPE   WS2811
#define COLOR_ORDER   RGB 
#define BRIGHTNESS  80
#define FRAMES_PER_SECOND 60
#define SENSOR1 7
#define STRANDS1 9

// Sensors
const int sensorPin01 = 7;
int sensorPressed = 0;
int sensor1Counter = 0;
unsigned long startTime = millis();
unsigned long firstInterval = 15000UL; // 15 seconds
unsigned long secondInterval = 25000UL; // 10 seconds
unsigned long thirdInterval = 40000UL; // 15 seconds
unsigned long fourthInterval = 60000UL; // 20 seconds

CRGB cluster1[NUM_LEDS_PER_STRIP];

TBlendType blendingType; 
//tBlendType is a data type like int/char/uint8_t etc., used to choose LINERBLEND and NOBLEND

void setup() {
  delay( 3000 ); //safety startup delay
  FastLED.addLeds<LED_TYPE,STRANDS1,COLOR_ORDER>(cluster1, NUM_LEDS_PER_STRIP);
  Serial.begin(9600);
  pinMode(sensorPin01, INPUT);
  blendingType = LINEARBLEND;                       // options are LINEARBLEND or NOBLEND - linear is 'cleaner'
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.clear();
}


//////////////////////////////////////////////////////////////////////////////////

void loop() {
  if(millis() - startTime < firstInterval)
  {
    aquapaint();
    addGlitter(80);
  } else if (millis() - startTime < secondInterval) {
    trailoff1();
  } else if (millis() - startTime < thirdInterval) {
    trailoff2(); 
  } else if (millis() - startTime < fourthInterval) {
    FastLED.clear();  
  } else {
    startTime = millis();
  }
  
  FastLED.show();
 }


void aquapaint (){
    for( int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    float fractionOfTheWayAlongTheStrip = (float)i / (float)(NUM_LEDS_PER_STRIP-1);
    uint8_t amountOfBlending = fractionOfTheWayAlongTheStrip * 255;
    CRGB pixelColor = blend( CHSV(100, 255, 255),  CHSV(130, 255, 255), amountOfBlending);
    cluster1[i] = pixelColor;
  }}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    cluster1[ random16(NUM_LEDS_PER_STRIP) ] += CRGB::White;
  }
}

void trailoff1() {
   //referencing fading from /https://github.com/FastLED/FastLED/wiki/Pixel-reference 
     cluster1[0].fadeLightBy( 90);
     cluster1[1].fadeLightBy( 90);
     cluster1[2].fadeLightBy( 64);
     cluster1[3].fadeLightBy( 64);
     cluster1[4].fadeLightBy( 64);
     addGlitter(30); 
     }

void trailoff2() {
     cluster1[0].fadeLightBy( 200);
     cluster1[1].fadeLightBy( 200);
     cluster1[2].fadeLightBy( 90);
     cluster1[3].fadeLightBy( 90);
     cluster1[4].fadeLightBy( 90);
     addGlitter(5); 
     }

