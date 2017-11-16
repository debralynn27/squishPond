//Squish Pond for Undetermined Origins, Future[tbd]Collective, East Austin Studio Tour 2017 - 
//Debra Lemak 11/16/17

#include "FastLED.h"
#include <CapacitiveSensor.h>
//https://github.com/PaulStoffregen/CapacitiveSensor

#define NUM_LEDS_PER_STRIP 5
#define NUM_STRIPS 3
#define NUM_LEDS NUM_LEDS_PER_STRIP*NUM_STRIPS
#define LED_TYPE   WS2811
#define COLOR_ORDER   RGB
#define BRIGHTNESS  20
#define FRAMES_PER_SECOND 60

#define STRANDS1        9
#define STRANDS2        10
#define STRANDS3        11

int sensorPressed = 0;
int sensor1Counter = 0; 
int sensor2Counter = 0;
int sensor3Counter = 0;

const int s1on = 1;
const int s2on = 2;
const int s3on = 3;

CRGB cluster1[NUM_LEDS_PER_STRIP];
CRGB cluster2[NUM_LEDS_PER_STRIP];
CRGB cluster3[NUM_LEDS_PER_STRIP];

TBlendType blendingType; 
//tBlendType is a data type like int/char/uint8_t etc., used to choose LINERBLEND and NOBLEND

  CapacitiveSensor   cs_4_0 = CapacitiveSensor(4,0);   // 1M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
  CapacitiveSensor   cs_4_1 = CapacitiveSensor(4,1);   // 1M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
  CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2); // 1M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

void setup() {
  delay( 3000 ); //safety startup delay
  FastLED.addLeds<LED_TYPE,STRANDS1,COLOR_ORDER>(cluster1, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE,STRANDS2,COLOR_ORDER>(cluster2, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE,STRANDS3,COLOR_ORDER>(cluster3, NUM_LEDS_PER_STRIP);

  blendingType = LINEARBLEND;                       // options are LINEARBLEND or NOBLEND - linear is 'cleaner'
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.clear();
}


///////////////////////////Functiony Goodness///////////////////////////////////////////////////////
////// Glitter Bombs! 
void addGlitter1( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    cluster1[ random16(NUM_LEDS_PER_STRIP) ] += CRGB::White;
  }
}

void addGlitter2( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    cluster2[ random16(NUM_LEDS_PER_STRIP) ] += CRGB::White;
  }
}

void addGlitter3( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    cluster3[ random16(NUM_LEDS_PER_STRIP) ] += CRGB::White;
  }
}


void lookatThings() {
  // Read touch sensors
  long sensor1 =  cs_4_0.capacitiveSensor(80);
  long sensor2 =  cs_4_1.capacitiveSensor(80);
  long sensor3 =  cs_4_2.capacitiveSensor(80);
  
  if (sensor1 >= 1000) {
    sensorPressed = s1on;
    return sensorPressed;
  } 
  if (sensor2 >= 1000) {
    sensorPressed = s2on;
    return sensorPressed;
  } 
    if (sensor3 >= 1000) {
    sensorPressed = s3on;
    return sensorPressed;
  } 

  sensorPressed = 0;
}

void setActive() {
   switch (sensorPressed) {
    case s1on:
       cluster1[0] = CRGB::Turquoise;
       cluster1[1] = CRGB::Turquoise;
       cluster1[2] = CRGB::AliceBlue;
       cluster1[3] = CRGB::AliceBlue;
       cluster1[4] = CRGB::AliceBlue;
       addGlitter1(80);
       sensor1Counter = 1;
      break;
      
    case s2on:
       cluster2[0] = CRGB::Turquoise;
       cluster2[1] = CRGB::Turquoise;
       cluster2[2] = CRGB::AliceBlue;
       cluster2[3] = CRGB::AliceBlue;
       cluster2[4] = CRGB::AliceBlue;
       addGlitter2(80);
       sensor2Counter = 1;
      break;
      
    case s3on:
       cluster3[0] = CRGB::Turquoise;
       cluster3[1] = CRGB::Turquoise;
       cluster3[2] = CRGB::AliceBlue;
       cluster3[3] = CRGB::AliceBlue;
       cluster3[4] = CRGB::AliceBlue;
       addGlitter3(80);
       sensor3Counter = 1;
      break;
}
}

void sensor1trail() {
  if (sensorPressed != s1on && sensor1Counter>=1) { 
   sensor1Counter++; 
   if (sensor1Counter < 300) {
   //referencing fading from /https://github.com/FastLED/FastLED/wiki/Pixel-reference 
     cluster1[0].fadeLightBy( 90);
     cluster1[1].fadeLightBy( 90);
     cluster1[2].fadeLightBy( 64);
     cluster1[3].fadeLightBy( 64);
     cluster1[4].fadeLightBy( 64);
     addGlitter1(30); 
     }
   if (sensor1Counter < 1000) {
     cluster1[0].fadeLightBy( 200);
     cluster1[1].fadeLightBy( 200);
     cluster1[2].fadeLightBy( 90);
     cluster1[3].fadeLightBy( 90);
     cluster1[4].fadeLightBy( 90);
     addGlitter1(5); 
     }
    else if (sensor1Counter > 2000){
      sensor1Counter = 0; 
    }
   }
   else  {
   fill_solid( cluster1, NUM_LEDS, CRGB::Seashell);
   }
}

void sensor2trail() {
  if (sensorPressed != s2on && sensor2Counter>=1) { 
   sensor2Counter++; 
   if (sensor2Counter < 300) {
     cluster2[0].fadeLightBy( 90);
     cluster2[1].fadeLightBy( 90);
     cluster2[2].fadeLightBy( 64);
     cluster2[3].fadeLightBy( 64);
     cluster2[4].fadeLightBy( 64);
     addGlitter2(30); 
     }
   if (sensor2Counter < 1000) {
     cluster2[0].fadeLightBy( 200);
     cluster2[1].fadeLightBy( 200);
     cluster2[2].fadeLightBy( 90);
     cluster2[3].fadeLightBy( 90);
     cluster2[4].fadeLightBy( 90);
     addGlitter2(5); 
     }
    else if (sensor2Counter > 2000){
      sensor2Counter = 0; 
    }
   }
   else  {
   fill_solid( cluster2, NUM_LEDS, CRGB::Seashell);
   }
}

void sensor3trail() {
  if (sensorPressed != s3on && sensor3Counter>=1) { 
   sensor3Counter++; 
   if (sensor3Counter < 300) {
     cluster3[0].fadeLightBy( 90);
     cluster3[1].fadeLightBy( 90);
     cluster3[2].fadeLightBy( 64);
     cluster3[3].fadeLightBy( 64);
     cluster3[4].fadeLightBy( 64);
     addGlitter3(30); 
     }
   if (sensor3Counter < 1000) {
     cluster3[0].fadeLightBy( 200);
     cluster3[1].fadeLightBy( 200);
     cluster3[2].fadeLightBy( 90);
     cluster3[3].fadeLightBy( 90);
     cluster3[4].fadeLightBy( 90);
     addGlitter3(5); 
     }
    else if (sensor3Counter > 2000){
      sensor3Counter = 0; 
    }
   }
   else  {
   fill_solid( cluster3, NUM_LEDS, CRGB::Seashell);
   }
}

void setTrailing(){
    sensor1trail();
    sensor2trail();
    sensor3trail();
    }



//////////////////////////////////////////////////////////////////////////////////

void loop() {
  lookatThings();
  setActive();
  setTrailing();
  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}
  

