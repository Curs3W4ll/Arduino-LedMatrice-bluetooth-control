/* Basic example code for MAX7219 LED dot matrix display with Arduino. More info: https://www.makerguides.com */

// Include the required Arduino libraries:
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
int i = 0;
textEffect_t texteffect[] =
{
  PA_PRINT,
  PA_SCAN_HORIZ,
  PA_SCROLL_LEFT,
  PA_WIPE,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_UP,
  PA_OPENING_CURSOR,
  PA_GROW_UP,
  PA_MESH,
  PA_SCROLL_UP_RIGHT,
  PA_BLINDS,
  PA_CLOSING,
  PA_RANDOM,
  PA_GROW_DOWN,
  PA_SCAN_VERT,
  PA_SCROLL_DOWN_LEFT,
  PA_WIPE_CURSOR,
  PA_DISSOLVE,
  PA_OPENING,
  PA_CLOSING_CURSOR,
  PA_SCROLL_DOWN_RIGHT,
  PA_SCROLL_RIGHT,
  PA_SLICE,
  PA_SCROLL_DOWN
};

int rowCounter =0; // row counter
int columnCounter =0; // column counter
int foundColumn = 0;
boolean foundCol = false;
int keyValue = 0;
int noKey = 0;
boolean readKey = false;
int debounce = 300; // set this to the lowest value that gives the best result
const int row1 = 10;
const int row2 = 11;
const int row3 = 12;
const int row4 = 13;
const int colA = 6;
const int colB = 7;
const int colC = 8;
const int colD = 9;

// Define hardware type, size, and output pins:
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 3

// Create a new instance of the MD_Parola class with hardware SPI connection:
//MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Setup for software SPI:
#define DATA_PIN 2
#define CLK_PIN 4
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void scanRow(){
  for(int j =row1; j < (row4 +1); j++){
    digitalWrite(j, HIGH);
  }
  digitalWrite(rowCounter , LOW); // switch on one row
}
void readColumn(){
  foundColumn = digitalRead(columnCounter);
  if(foundColumn == 0){
    foundCol = true;
  }
  else{
    foundCol=false;
    noKey=noKey +1; // counter for number of empty columns
  }
} //[Button 4x4 matrix]

void setup() {
  /*Serial.begin(9600);
  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(row4, OUTPUT);
  pinMode(colA, INPUT_PULLUP);
  pinMode(colB, INPUT_PULLUP);
  pinMode(colC, INPUT_PULLUP);
  pinMode(colD, INPUT_PULLUP);
  myDisplay.setTextAlignment(PA_CENTER); //[Button 4x4 matrix]*/
  
  // Intialize the object:
  myDisplay.begin();
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(0);
  
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.setPause(1000);
  myDisplay.setSpeed(100); //[AllEffects]
  
  // Clear the display:
  myDisplay.displayClear();
  
  //myDisplay.displayText("Scrolling text", PA_CENTER, 10, 1000, PA_SCROLL_LEFT, PA_SCROLL_LEFT); //[Scroll]
}

void loop() {
  /*if(noKey == 16){ // no keys were pressed
    readKey = true; // keyboard is ready to accept a new keypress
  }
  noKey = 0;
  for(rowCounter=row1; rowCounter<(row4 +1); rowCounter++){
    scanRow(); // switch on one row at a time
    for(columnCounter = colA; columnCounter <colD +1; columnCounter++){
      readColumn(); // read the switch pressed
      if (foundCol== true){
        keyValue =(rowCounter-row1) +4*(columnCounter - colA);
      }
    }
  }
  if(readKey==true && noKey == 15){ // a key has been pressed
    Serial.println(keyValue); // used for debug
  }
  myDisplay.print(keyValue);
  readKey = false; // rest the flag
  delay(debounce); //[Button 4x4 matrix]*/
  
  if (myDisplay.displayAnimate()) {
    if (i < sizeof(texteffect)) {
      i++;
    }
    else {
      i = 0;
    }
    myDisplay.displayText("Hello", myDisplay.getTextAlignment(), myDisplay.getSpeed(), myDisplay.getPause(), texteffect[i], texteffect[i]);
    myDisplay.displayReset();
  } //[AllEffects]
  
  /*if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  } //[Scroll]*/
  
  /*[Basic_displays] myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.print("Center");
  delay(2000);
  myDisplay.setTextAlignment(PA_LEFT);
  myDisplay.print("Left");
  delay(2000);
  myDisplay.setTextAlignment(PA_RIGHT);
  myDisplay.print("Right");
  delay(2000);
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.setInvert(true);
  myDisplay.print("Invert");
  delay(2000);
  myDisplay.setInvert(false);
  myDisplay.print(1234);
  delay(2000);*/
}
