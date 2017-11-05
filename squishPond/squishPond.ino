//Squish Pond for East Austin Studio Tour 2017 - Debra Lemak 
// Using "Ripple" Conversion by Andrew Tuline
//


#include <FastLED.h>        // FastLED library

 
#define LED_DT 11
#define NUM_LEDS 24

struct CRGB leds[NUM_LEDS];
 
int color;
int center = 0;
int step = -1;
int maxSteps = 16;
float fadeRate = 0.8;
int diff;
int buttonPin = 3; 
int buttonState = 0;
int hueValue = 140;
int splashZone01 [] = {0,1,2,3,4,5,6
}; 
//background color
uint32_t currentBg = hueValue;
uint32_t nextBg = currentBg;
 
void setup() {

  Serial.begin(9600);
  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, NUM_LEDS);
  pinMode(buttonPin, INPUT); 
}
 
void loop () {
  buttonState = digitalRead(buttonPin);
 if (buttonState ==HIGH) {
  ripple();
  }
}
 
void ripple() {

    if (currentBg == nextBg) {
      nextBg = hueValue;
    } 
    else if (nextBg > currentBg) {
      currentBg++;
    } else {
      currentBg--;
    }
    for(uint16_t l = 0; l < NUM_LEDS; l++) {
      leds[l] = CHSV(currentBg, 255, 50);         // strip.setPixelColor(l, Wheel(currentBg, 0.1));
    }
 
  if (step == -1) {
    center = random(NUM_LEDS);
    color = hueValue;
    step = 0;
  }
 
  if (step == 0) {
    leds[center] = CHSV(color, 255, 255);         
    step ++;
  } 
  else {
    if (step < maxSteps) {
      Serial.println(pow(fadeRate,step));

      leds[wrap(center + step)] = CHSV(color, 255, pow(fadeRate, step)*255);       
      leds[wrap(center - step)] = CHSV(color, 255, pow(fadeRate, step)*255);       
      if (step > 3) {
        leds[wrap(center + step - 3)] = CHSV(color, 255, pow(fadeRate, step - 2)*255);     
        leds[wrap(center - step + 3)] = CHSV(color, 255, pow(fadeRate, step - 2)*255);    
      }
      step ++;
    } 
    else {
      step = -1;
    }
  }
  
  LEDS.show();
  delay(50);
}
 
 
int wrap(int step) {
  if(step < 0) return NUM_LEDS + step;
  if(step > NUM_LEDS - 1) return step - NUM_LEDS;
  return step;
}
 



 

