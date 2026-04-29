#include <Arduino.h>

// include TFT and SPI libraries
#include <TFT.h>  
#include <SPI.h>

const int cs =  10;
const int dc =  9;
const int rst = 8;

TFT TFTscreen = TFT(cs, dc, rst);

void setup() {

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  //initialize the library
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);
}

int ledState = LOW;
unsigned long previousMillis = 0;
const long interval = 1000;

void loop() {
 unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_BUILTIN, ledState);
  }

  //generate a random color
  int redRandom = random(0, 255);
  int greenRandom = random (0, 255);
  int blueRandom = random (0, 255);
  
  // set the color for the figures
  TFTscreen.stroke(redRandom, greenRandom, blueRandom);

  // light up a single point
  TFTscreen.point(80,64);
  // wait 200 miliseconds until change to next figure
  delay(500);

  // draw a line
  TFTscreen.line(0,64,160,64);
  delay(500);

  //draw a square
  TFTscreen.rect(50,34,60,60);
  delay(500);
    
  //draw a circle
  TFTscreen.circle(80,64,30);
  delay(500);

  //erase all figures
  TFTscreen.background(0,0,0);

}

