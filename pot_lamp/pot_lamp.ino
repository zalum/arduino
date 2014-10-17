#include <Adafruit_NeoPixel.h>

int noLeds = 16;
int connectedPin = 6;
int potPin = 11;
int maxPotInput = 1024;
#define noColorOptions 4
#define PURPLE {10,80,72} 
#define BLUE {0,0,127}
#define RED {0,127,0}
#define WHITE {127,127,127}
#define CLOSED {0,0,0}

int colorBorders[] = {256,512,768,1023};
int colors[][3]= {CLOSED,WHITE,RED,BLUE};
Adafruit_NeoPixel strip = Adafruit_NeoPixel(noLeds, connectedPin, NEO_RGB + NEO_KHZ800);

// Pin D6 has an LED connected on FLORA.
// give it a name:
 
// the setup routine runs once when you press reset:
void setup() {               
  Serial.begin(9600);
  strip.begin();
  strip.show();
}
 
// the loop routine runs over and over again forever:
void loop() {
  static int lastLedInput = 0;
  int potReading  = analogRead(potPin);
  int ledInput = calculateLedInput(potReading);
  Serial.println(ledInput);
  if(ledInput != lastLedInput){
    setNewColor(ledInput);
    lastLedInput = ledInput;
  }
  delay(500);
}

int calculateLedInput(int potInput){
  for(int i=0;i<noColorOptions;i++){
    if(potInput<=colorBorders[i]){
      return i;
    }
  }
}

void setNewColor(int ledInput){
  for(int i=0;i<noLeds;i++){
    strip.setPixelColor(i, 
      strip.Color(
              colors[ledInput][0],
              colors[ledInput][1], 
              colors[ledInput][2]));
    strip.show();
    delay(50);
  }
}
