/*  *** LIGHTDEX ***
    A project by MJJoaquin

    Originally created for the Nanoleaf replica
    light panels project by Akyelle
    https://www.thingiverse.com/thing:4686921/comments
    This program can easily be modified to work with
    any serial ARGB LEDs that "group" into sections

    This proram is designed to be as modular
    as possible for creating your own animations
    for any range of coding experience.

 *  *** SETUP ***
    FOLLOW CAREFULLY
    Set variables
      pin = Which pin is connected to the strip
      panelcount = How many "groups" in your project
      ledseach = How many LEDs are in each group
      fadeSteps = How smooth you want your transitions.
        More is better. Default to moderate processing
        time. If you have a lot of LEDs decrease to 20
        with 50ms delays, for few LEDs increase to 60
        with 17ms delays.
        *delayTime can be changed on the fly, just*
        *change it back!*

    Choose the animation
      Use lightdex_controller.ino on another arduino
        or jumpers to select animation. Or hook up a
        few switches. Or set  "int animation = #" to
        force only one animation. Or put it in a for
        loop to make it cycle through them. Or... the
        possibilities are endless, it's up to you!
      There are a variety of methods available to make
      it easy to create your own animations as well.
*/

#include <Adafruit_NeoPixel.h>
#define pin 13
#define panelcount 6
#define ledseach 12
#define fadeSteps 40
int delayTime = 25;

//X and Y layout of panels in order they are wired
//Refer to "2D diagram.png" for example
static int panelX[] = {0, 1, 1, 2, 3, 4};
static int panelY[] = {1, 1, 0, 0, 1, 1};
int width = 0;
int height = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(panelcount * ledseach, pin, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  strip.begin();
  Static(0, 0, 0);
  Pulse(0, 0, 0, 255, 255, 255);

  // Set width and height
  for (int i = 0; i <= panelcount - 1; i++) {
    if (width > panelX[i]) {
      width = panelX[i];
    }
  }
  for (int i = 0; i <= panelcount - 1; i++) {
    if (height > panelY[i]) {
      height = panelY[i];
    }
  }
}

void loop() {
  //Read
  int animation = Animation();

  //Output
  switch (animation) {
    case 0:
      FadeAll(255, 0, 0, 255, 255, 0);
      animation = Animation(); // allows animation to skip if changed
      if (animation != 0) {
        break;
      }
      FadeAll(255, 255, 0, 0, 255, 0);
      animation = Animation();
      if (animation != 0) {
        break;
      }
      FadeAll(0, 255, 0, 0, 255, 255);
      animation = Animation();
      if (animation != 0) {
        break;
      }
      FadeAll(0, 255, 255, 0, 0, 255);
      animation = Animation();
      if (animation != 0) {
        break;
      }
      FadeAll(0, 0, 255, 255, 0, 255);
      animation = Animation();
      if (animation != 0) {
        break;
      }
      FadeAll(255, 0, 255, 255, 0, 0);
      break;

    //Static colours
    case 1:
      Static(255, 255, 255);
      break;
    case 2:
      Static(255, 0, 0);
      break;
    case 3:
      Static(255, 255, 0);
      break;
    case 4:
      Static(0, 255, 0);
      break;
    case 5:
      Static(0, 255, 255);
      break;
    case 6:
      Static(0, 0, 255);
      break;
    case 7:
      Static(255, 0, 255);
      break;

    //Simple fades
    case 8:
      Pulse(255, 0, 0, 255, 255, 0);
      break;
    case 9:
      Pulse(255, 255, 0, 0, 255, 0);
      break;
    case 10:
      Pulse(0, 255, 0, 0, 255, 255);
      break;
    case 11:
      Pulse(0, 255, 255, 0, 0, 255);
      break;
    case 12:
      Pulse(0, 0, 255, 255, 0, 255);
      break;
    case 13:
      Pulse(255, 0, 255, 255, 0, 0);
      break;

    //2D animations
    case 14:
      delayTime = 10;
      Static(0, 0, 255);
      for (int i = 0; i <= 4; i++) {
        FadePanelColumn(i, 0, 0, 255, 255, 0, 255);
      }
      for (int i = 0; i <= 4; i++) {
        FadePanelColumn(i, 255, 0, 255, 0, 0, 255);
      }
      delayTime = 25;
      break;

    default:
      Static(0, 0, 0);
      break;
  }
}

// Reads selection pins
int Animation() {
  int result = 0;
  if (digitalRead(8) == HIGH) {
    result++;
  }
  if (digitalRead(9) == HIGH) {
    result += 2;
  }
  if (digitalRead(10) == HIGH) {
    result += 4;
  }
  if (digitalRead(11) == HIGH) {
    result += 8;
  }
  if (digitalRead(12) == HIGH) {
    result += 16;
  }
  return result;
}

//Sets panels individually. panelNumber starts at 0, from the arduino side of the strip
void SetPanel(int panelNumber, int red, int green, int blue) {
  for (int i = 0; i <= ledseach - 1; i++) {
    strip.setPixelColor(i + 12 * panelNumber, red, green, blue);
  }
  strip.show();
}

//Sets panels individually based on X & Y values
void SetPanelXY(int x, int y, int red, int green, int blue) {
  //Seach for panel number with coresponding coordinates
  int panelNumber;
  for (int i = 0; i <= panelcount; i++) {
    if (panelX[i] == x && panelY[i] == y) {
      panelNumber = i;
      break; //skip the rest, only one panel per coordinate
    }
  }
  //Set
  SetPanel(panelNumber, red, green, blue);
}

// Sets an entire row
void SetPanelRow(int row, int red, int green, int blue) {
  //Seach for panel number with coresponding coordinates
  int panelNumber;
  for (int i = 0; i <= panelcount - 1; i++) {
    if (panelY[i] == row) {
      panelNumber = i;
      SetPanel(panelNumber, red, green, blue);
    }
  }
}

// Sets an entire column
void SetPanelColumn(int column, int red, int green, int blue) {
  int panelNumber;
  for (int i = 0; i <= panelcount - 1; i++) {
    if (panelX[i] == column) {
      panelNumber = i;
      SetPanel(panelNumber, red, green, blue);
    }
  }
}

// Fades an entire row
void FadePanelColumn(int column, int red1, int green1, int blue1, int red2, int green2, int blue2) {
  for (int col = 0; col <= fadeSteps; col++) {
    for (int i = 0; i <= panelcount - 1; i++) {
      if (panelX[i] == column) {
        SetPanel(i, ((red2 - red1)*col / fadeSteps) + red1, ((green2 - green1)*col / fadeSteps) + green1, ((blue2 - blue1)*col / fadeSteps) + blue1);
      }
    }
    strip.show();
    delay(delayTime);
  }
}

//Sets everything to one colour. Good for clearing or no animation
void Static(int red, int green, int blue) {
  for (int i = 0; i <= panelcount * ledseach - 1; i++) {
    strip.setPixelColor(i , red, green, blue);
  }
  strip.show();
}

//Pulses entire array from one colour to another and back
//Takes (delayTime*fadeSteps*2) mills to run
void Pulse(int red1, int green1, int blue1, int red2, int green2, int blue2) {
  for (int col = 0; col <= fadeSteps; col++) {
    for (int i = 0; i <= panelcount * ledseach - 1; i++) {
      strip.setPixelColor(i, ((red2 - red1)*col / fadeSteps) + red1, ((green2 - green1)*col / fadeSteps) + green1, ((blue2 - blue1)*col / fadeSteps) + blue1);
    }
    strip.show();
    delay(delayTime);
  }
  for (int col = 0; col <= fadeSteps; col++) {
    for (int i = 0; i <= panelcount * ledseach - 1; i++) {
      strip.setPixelColor(i, ((red1 - red2)*col / fadeSteps) + red2, ((green1 - green2)*col / fadeSteps) + green2, ((blue1 - blue2)*col / fadeSteps) + blue2);
    }
    strip.show();
    delay(delayTime);
  }
}

//Pulses one panel from one colour to another and back
//Takes (delayTime*fadeSteps*2) mills to run
void PulsePanel(int panelNumber, int red1, int green1, int blue1, int red2, int green2, int blue2) {
  for (int col = 0; col <= fadeSteps; col++) {
    for (int i = panelNumber * 12; i <= (panelNumber + 1) * 12 - 1; i++) {
      strip.setPixelColor(i, ((red2 - red1)*col / fadeSteps) + red1, ((green2 - green1)*col / fadeSteps) + green1, ((blue2 - blue1)*col / fadeSteps) + blue1);
    }
    strip.show();
    delay(delayTime);
  }
  for (int col = 0; col <= fadeSteps; col++) {
    for (int i = panelNumber * 12; i <= (panelNumber + 1) * 12 - 1; i++) {
      strip.setPixelColor(i, ((red1 - red2)*col / fadeSteps) + red2, ((green1 - green2)*col / fadeSteps) + green2, ((blue1 - blue2)*col / fadeSteps) + blue2);
    }
    strip.show();
    delay(delayTime);
  }
}

//Fades all panels at the same time from 1 to 2
//Takes (delayTime*fadeSteps) mills to run
void FadeAll(int red1, int green1, int blue1, int red2, int green2, int blue2) {
  for (int col = 0; col <= fadeSteps; col++) {
    for (int i = 0; i <= panelcount * ledseach - 1; i++) {
      strip.setPixelColor(i, ((red2 - red1)*col / fadeSteps) + red1, ((green2 - green1)*col / fadeSteps) + green1, ((blue2 - blue1)*col / fadeSteps) + blue1);
    }
    strip.show();
    delay(delayTime);
  }
}
