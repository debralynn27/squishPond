//Squish Pond for East Austin Studio Tour 2017 - Debra Lemak 
#include "FastLED.h"

#define NUM_LEDS_PER_STRIP 5
#define NUM_STRIPS 3
#define NUM_LEDS NUM_LEDS_PER_STRIP*NUM_STRIPS
#define LED_TYPE   WS2811
#define COLOR_ORDER   RGB

#define STRAND11        11
#define STRAND12        12
#define STRAND13        13


int buttonPin = 3; 
int buttonState = 0;
int offCounter = 0; 


CRGB leds[NUM_LEDS_PER_STRIP];

void setup() {
  delay( 3000 ); //safety startup delay
  FastLED.addLeds<LED_TYPE,STRAND11,COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE,STRAND12,COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE,STRAND13,COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP);
  ///Using FastLED reference to mirror strips - https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples 
//  .setCorrection(TypicalLEDStrip);
  pinMode(buttonPin, INPUT); 
}


void loop() {
  ///referencing color options from: https://github.com/FastLED/FastLED/wiki/Pixel-reference

  
  buttonState = digitalRead(buttonPin);
  
  if (buttonState ==HIGH) {
    leds[0] = CRGB::Turquoise;
    leds[1] = CRGB::Turquoise;
    leds[2] = CRGB::AliceBlue;
    leds[3] = CRGB::AliceBlue;
    leds[4] = CRGB::AliceBlue;
    addGlitter(80);
    offCounter = 0; 
     }
   else if (buttonState == LOW) { 
   offCounter++; 
   if (offCounter < 300) {
   //referencing fading from https://github.com/FastLED/FastLED/wiki/Pixel-reference 
     leds[0].fadeLightBy( 90);
     leds[0].fadeLightBy( 90);
     leds[0].fadeLightBy( 64);
     leds[0].fadeLightBy( 64);
     leds[0].fadeLightBy( 64);
     addGlitter(30); 
     }
   else if (offCounter < 1000) {
     leds[0].fadeLightBy( 200);
     leds[0].fadeLightBy( 200);
     leds[0].fadeLightBy( 90);
     leds[0].fadeLightBy( 90);
     leds[0].fadeLightBy( 90);
     addGlitter(5); 
     }
   }
   else  {
   fill_solid( leds, NUM_LEDS, CRGB::Seashell);
   }
   FastLED.show();
}



//////
void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS_PER_STRIP) ] += CRGB::White;
  }
}
////////////
