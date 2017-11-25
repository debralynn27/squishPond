//Squish Pond for Undetermined Origins, Future[tbd]Collective, East Austin Studio Tour 2017 - 
//Debra Lemak 11/16/17

#include "FastLED.h"

#define NUM_LEDS_PER_STRIP 5
#define NUM_STRIPS 3
#define NUM_SENSORS 3
#define LED_TYPE   WS2811
#define COLOR_ORDER   RGB 
#define BRIGHTNESS  255
#define FRAMES_PER_SECOND 160

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

// Intervals
unsigned long startTime = millis();
unsigned long firstInterval = 1000UL; // 15 seconds
unsigned long secondInterval = 3000UL; // 10 seconds
unsigned long thirdInterval = 6000UL; // 10 seconds

class Sensor {
  public:
    int pin;      // Pin number
    int state;    // 0 = off, 1 = on
    int pressed;  // Is pressed?  0 = false, 1 = true
    unsigned long startTime;

    // Constructor
    Sensor(int _pin, int _state, int _pressed, int _startTime)
    {
      pin = _pin;
      state = _state;
      pressed = _pressed;
      startTime = _startTime;
    }
};

// Sensor array
Sensor *sensors[3];

TBlendType blendingType; 
//tBlendType is a data type like int/char/uint8_t etc., used to choose LINERBLEND and NOBLEND

void setup() {
  sensors[0] = new Sensor(4, 0, 0, millis());
  sensors[1] = new Sensor(5, 0, 0, millis());
  sensors[2] = new Sensor(6, 0, 0, millis());

  // Enable pins
  for(int i = 0; i < NUM_SENSORS; ++i) {
    pinMode(sensors[i]->pin, INPUT_PULLUP);
  }
  
  FastLED.addLeds<LED_TYPE, 8, COLOR_ORDER>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<LED_TYPE, 10, COLOR_ORDER>(leds[2], NUM_LEDS_PER_STRIP);

  blendingType = LINEARBLEND; // options are LINEARBLEND or NOBLEND - linear is 'cleaner'
  FastLED.setBrightness( BRIGHTNESS );
  FastLED.clear();
  Serial.begin(9600);
}


//////////////////////////////////////////////////////////////////////////////////

void loop() {
  checkInputs();
  renderEffects();
  /*
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
  */
  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND);
  setPressed();
}

/**
 * Check our inputs and set the button state
 */
void checkInputs() 
{
  // Read pins
  for(int i = 0; i < NUM_SENSORS; ++i) {
    if (digitalRead(sensors[i]->pin) == LOW) {
      sensors[i]->state = 1;
      sensors[i]->startTime = millis();
      Serial.print(sensors[i]->pin);
      Serial.println(" pressed.");
    } else {
      sensors[i]->state = 0;
    } 
  } 
}

/**
 * Mark input as pressed after first loop
 */
void setPressed() 
{
  // Read pins
  for(int i = 0; i < NUM_SENSORS; ++i) {
    if ((sensors[i]->state == 1) && (sensors[i]->pressed == 0)) {
      sensors[i]->pressed = 1;
    }
  } 
}

/**
 * Handle the button states to render effects
 */
void renderEffects() {
  // Render effects based on sensors touched
  for(int i = 0; i < NUM_SENSORS; ++i) {
    if (sensors[i]->pressed == 1) {
      if((millis() - sensors[i]->startTime) < firstInterval)
      {
        aquapaint(i);
        addGlitter(i, 80);
      } else if ((millis() - sensors[i]->startTime) < secondInterval) {
        trailoff1(i);
      } else if ((millis() - sensors[i]->startTime) < thirdInterval) {
        trailoff2(i);
      } else {
        FastLED.clear(); 
        sensors[i]->startTime = millis();
        sensors[i]->pressed = 0;
      }
    } else {
      ambient(i);
    }
  } 
}

void ambient(int strip) 
{
  for( int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    leds[strip][i] = CHSV(160, 0, 30);
  }
}

void aquapaint (int strip){
    for( int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    float fractionOfTheWayAlongTheStrip = (float)i / (float)(NUM_LEDS_PER_STRIP-1);
    uint8_t amountOfBlending = fractionOfTheWayAlongTheStrip * 255;
    CRGB pixelColor = blend( CHSV(100, 255, 255),  CHSV(130, 255, 255), amountOfBlending);
    leds[strip][i] = pixelColor;
  }
}

void addGlitter(int strip, fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    CRGB pixelColor = blend( CHSV(100, 255, 255),  CHSV(130, 255, 255), 120);
    leds[strip][ random16(NUM_LEDS_PER_STRIP) ] += pixelColor;
  }
}

void trailoff1(int strip) {
   //referencing fading from /https://github.com/FastLED/FastLED/wiki/Pixel-reference 
     leds[strip][0].fadeLightBy(50);
     leds[strip][1].fadeLightBy(80);
     leds[strip][2].fadeLightBy(50);
     leds[strip][3].fadeLightBy(80);
     leds[strip][4].fadeLightBy(50);
     addGlitter(strip, 30); 
}

void trailoff2(int strip) {
   //referencing fading from /https://github.com/FastLED/FastLED/wiki/Pixel-reference 
     leds[strip][0].fadeLightBy(140);
     leds[strip][1].fadeLightBy(200);
     leds[strip][2].fadeLightBy(140);
     leds[strip][3].fadeLightBy(200);
     leds[strip][4].fadeLightBy(140);
     addGlitter(strip, 10); 
}

