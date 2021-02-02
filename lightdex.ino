#include <Adafruit_NeoPixel.h>
#define panelcount 6
#define ledseach 12
#define fadeSteps 10

//X and Y layout of panels in order they are wired
//Refer to "2D diagram.png" for example
int panelX[] = {3, 3, 2, 1, 0, 2};
int panelY[] = {1, 0, 0, 0, 1, 1};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(panelcount * ledseach, 6, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  //Static(255, 255, 255);
  //Pulse(0, 0, 0, 255, 0, 0);
  SetPanelXY(2, 1, 255, 0, 255);
  SetPanelXY(3, 0, 0, 255, 255);
}
 
void loop() {
  /*//Simple rainbow effect
  FadeAll(255, 0, 0, 255, 255, 0);
  FadeAll(255, 255, 0, 0, 255, 0);
  FadeAll(0, 255, 0, 0, 255, 255);
  FadeAll(0, 255, 255, 0, 0, 255);
  FadeAll(0, 0, 255, 255, 0, 255);
  FadeAll(255, 0, 255, 255, 0, 0);*/
}

//Sets panels individually. panelNumber starts at 0, from the arduino side of the strip
void SetPanel(int panelNumber, int red, int green, int blue) {
  for (int i = 0; i <= ledseach-1; i++) {
  	strip.setPixelColor(i+12*panelNumber, red, green, blue);
  }
  strip.show();
}

//Sets panels individually based on X & Y values
void SetPanelXY(int x, int y, int red, int green, int blue) {
  //Seach for panel number with coresponding coordinates
  int panelNumber = 1;
  for(int i = 0; i <= panelcount; i++) {
    if(panelX[i]==x && panelY[i] == y) {
     	panelNumber = i;
    	break;
  	}
  }
  //Set
  SetPanel(panelNumber, red, green, blue);
}

//Sets everything to one colour. Good for clearing or no animation
void Static(int red, int green, int blue) {
  for (int i = 0; i <= panelcount*ledseach-1; i++) {
  	strip.setPixelColor(i , red, green, blue);
  }
  strip.show();
}

//Pulses entire array from one colour to another and back
//Takes (delayTime*fadeSteps*2) mills to run
void Pulse(int red1, int green1, int blue1, int red2, int green2, int blue2) {
  	int delayTime = 100;
	for (int col = 0; col <= fadeSteps; col++) {
		for (int i = 0; i <= panelcount*ledseach-1; i++) {
			strip.setPixelColor(i, ((red2-red1)*col/fadeSteps)+red1, ((green2-green1)*col/fadeSteps)+green1, ((blue2-blue1)*col/fadeSteps)+blue1);
        }
      strip.show();
      delay(delayTime);
	}
  	for (int col = 0; col <= fadeSteps; col++) {
		for (int i = 0; i <= panelcount*ledseach-1; i++) {
			strip.setPixelColor(i, ((red1-red2)*col/fadeSteps)+red2, ((green1-green2)*col/fadeSteps)+green2, ((blue1-blue2)*col/fadeSteps)+blue2);
        }
      strip.show();
      delay(delayTime);
	}
}


//Pulses one panel from one colour to another and back
//Takes (delayTime*fadeSteps*2) mills to run
void PulsePanel(int panelNumber, int red1, int green1, int blue1, int red2, int green2, int blue2) {
  	int delayTime = 100;
	for (int col = 0; col <= fadeSteps; col++) {
		for (int i = panelNumber*12; i <= (panelNumber+1)*12-1; i++) {
			strip.setPixelColor(i, ((red2-red1)*col/fadeSteps)+red1, ((green2-green1)*col/fadeSteps)+green1, ((blue2-blue1)*col/fadeSteps)+blue1);
        }
      strip.show();
      delay(delayTime);
	}
  	for (int col = 0; col <= fadeSteps; col++) {
		for (int i = panelNumber*12; i <= (panelNumber+1)*12-1; i++) {
			strip.setPixelColor(i, ((red1-red2)*col/fadeSteps)+red2, ((green1-green2)*col/fadeSteps)+green2, ((blue1-blue2)*col/fadeSteps)+blue2);
        }
      strip.show();
      delay(delayTime);
	}
}


//Fades all panels at the same time from 1 to 2
void FadeAll(int red1, int green1, int blue1, int red2, int green2, int blue2) {
  for (int col = 0; col <= fadeSteps; col++) {
      for (int i = 0; i <= panelcount*ledseach-1; i++) {
        strip.setPixelColor(i, ((red2-red1)*col/fadeSteps)+red1, ((green2-green1)*col/fadeSteps)+green1, ((blue2-blue1)*col/fadeSteps)+blue1);
      }
      strip.show();
      delay(100);
    }
}


// legacy fade method
//Fades each panel seperately from 1 to 2
void Fade(int red1, int green1, int blue1, int red2, int green2, int blue2) {
  for (int i = 0; i <= panelcount-1; i++) {
    for (int col = 0; col <= fadeSteps-1; col++) { 
      for (int j = 0; j <= ledseach-1; j++) {
        strip.setPixelColor(i*ledseach+j , ((red2-red1)*col/fadeSteps)+red1, ((green2-green1)*col/fadeSteps)+green1, ((blue2-blue1)*col/fadeSteps)+blue1);
      }
      strip.show();
      delay(100);
    }
  }
}
