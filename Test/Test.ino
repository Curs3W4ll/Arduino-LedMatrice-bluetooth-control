#include "LedControl.h"

LedControl lc=LedControl(2,4,3,4);

byte testing[] =
{
   B0,
   B0,
   B0,
   B0,
   B0,
   B0,
   B0,
   B0
};
byte chiffres[][8] =
{{
   B00000000,
   B11111000,
   B10001000,
   B10001000,
   B10001000,
   B10001000,
   B10001000,
   B11111000
   //--0--//
},
{
   B00000000,
   B01000000,
   B11000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000
   //--1--//
},
{
   B00000000,
   B01111100,
   B00000100,
   B00000100,
   B01111100,
   B01000000,
   B01000000,
   B01111100
   //--2--//
},
{
   B00000000,
   B00111100,
   B00000100,
   B00000100,
   B00111100,
   B00000100,
   B00000100,
   B00111100
   //--3--//
},
{
   B00000000,
   B01000100,
   B01000100,
   B01000100,
   B01111100,
   B00000100,
   B00000100,
   B00000100
   //--4--//
},
{
   B00000000,
   B01111100,
   B01000000,
   B01000000,
   B01111100,
   B00000100,
   B00000100,
   B01111100
   //--5--//
},
{
   B00000000,
   B01111100,
   B01000000,
   B01000000,
   B01111100,
   B01000100,
   B01000100,
   B01111100
   //--6--//
},
{
   B00000000,
   B01111100,
   B00000100,
   B00000100,
   B00001000,
   B00010000,
   B00010000,
   B00010000
   //--7--//
},
{
   B00000000,
   B01111100,
   B01000100,
   B01000100,
   B01111100,
   B01000100,
   B01000100,
   B01111100
   //--8--//
},
{
   B00000000,
   B01111100,
   B01000100,
   B01000100,
   B01111100,
   B00000100,
   B00000100,
   B01111100
   //--9--//
}};
byte affichage[][8] =
{{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
},
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
}};

char mot[] = "01a";

void setup()
{
  Serial.begin(9600);
  Serial.println("New-------");
  for (int i = 0; i < 4; i++) {
    lc.shutdown(i,false);  // Wake up displays
    lc.setIntensity(i,1);  // Set intensity levels
    lc.clearDisplay(i);  // Clear Displays
  }
}

void loop()
{
  int writen_col = 0;
  int used_affichage = 3;
  for (int cara=0;mot[cara]!='\0';cara++) {
    int number = (int)mot[cara];
    Serial.print("char : ");
    Serial.println(mot[cara]);
    Serial.print("int : ");
    Serial.println(number);
    if (writen_col != 0) {
      for (int ligne=0;ligne<8;ligne++) {
          bitWrite(affichage[3][ligne],writen_col,0);
        }
        writen_col += 1;
    }
    for (int col=0;col<8;col++) {
      byte tempbyte = B00000000;
      for (int ligne=0;ligne<8;ligne++) {
        bitWrite(tempbyte,ligne,bitRead(chiffres[cara][ligne],col));
      }
      //Serial.println(tempbyte,BIN);
      if (tempbyte!=0) {
        //Serial.println(tempbyte,BIN);
        for (int ligne=0;ligne<8;ligne++) {
          bitWrite(affichage[3][ligne],writen_col,bitRead(tempbyte,ligne));
          //Serial.println(affichage[0][j],BIN);
        }
      writen_col += 1;
      }
    }
  }
  for (int i=0;i<4;i++) {
    for (int y=0;y<8;y++) {
      lc.setRow(i,y,affichage[i][y]);
    }
  }
  delay(60000);
}
