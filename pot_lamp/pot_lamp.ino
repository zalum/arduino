#include <Adafruit_NeoPixel.h>  

int noLeds = 16;
int connectedPin = 6;
int potPin = 11;
int maxPotInput = 1024;
int currentFrame;
#define noColorOptions 4
#define PURPLE {10,80,72} 
#define BLUE 0,0,127
#define RED 127,0,0
#define WHITE 127,127,127
#define CLOSED {0,0,0}

int colorBorders[] = {256,512,768,1023};

typedef struct led{
  int properties[5];
};

typedef struct frame{
  led leds[16];
};

frame framesx[]={
    //frames/leds
    {{{0,200,200,200,100}, {0,200,200,200,100}, {0,200,200,200,100}}},
    {{{0,200,200,200,100}, {0,200,200,200,100}}}
  };
  
// properties  
int frames[][16][5]= {
    //frame
    { 
      //pixel index, color, intensity
      {0,RED,100},
      {1,RED,100},
      {2,RED,100}
    },
    { 
      //pixel index, color, intensity
      {2,BLUE,100},
      {3,BLUE,100}       
    }
    ,
    { 
      //pixel index, color, intensity
      {4,WHITE,100},
      {5,WHITE,100}       
    }
};


Adafruit_NeoPixel strip = Adafruit_NeoPixel(noLeds, connectedPin, NEO_RGB + NEO_KHZ800);

// Pin D6 has an LED connected on FLORA.
// give it a name:
 
// the setup routine runs once when you press reset:
void setup() {               
  Serial.begin(9600);
  strip.begin();
  strip.show();
  currentFrame = 0; 
  frame x = {};
}
 
// the loop routine runs over and over again forever:
void loop() {
  static int lastLedInput = 0;
  int potReading  = analogRead(potPin);
  int ledInput = calculateLedInput(potReading);
  Serial.println(ledInput);
  printFrame(currentFrame++);  
  delay(500);
}

int calculateLedInput(int potInput){
  for(int i=0;i<noColorOptions;i++){
    if(potInput<=colorBorders[i]){
      return i;
    }
  }
}

void printFrame(int frameIndex){
  printFrame(frames[frameIndex]);
}

void printFrame(int  frame[][5]){
	for (int pixelIndex=0;pixelIndex<16;pixelIndex++){
    if(frame[pixelIndex] == NULL){
      break;
    }
		int pixelPosition = getPixelPositionInFrame(pixelIndex,frame);
		uint32_t pixelColor = getColorInFrame(pixelIndex,frame);
		strip.setPixelColor(pixelPosition,pixelColor);
	}	
	strip.show();
}

int getPixelPositionInFrame(int pixelIndex,int frame[][5]){
	return 1;
}

uint32_t getColorInFrame(int pixelIndex,int frame[][5]){
	return strip.Color(10,80,72);
}

