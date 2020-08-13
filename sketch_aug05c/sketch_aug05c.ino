/*************************************************************
 * Ce sketch affiche toutes les lettres de l'alphabet et tous les 
 * chiffres, un apres l'autre, sur une matrice de LEDs 8 X8
 *
 * http://electroniqueamateur.blogspot.ca/2015/12/matrice-de-64-leds-max7219-et-arduino.html
 *
 **************************************************************/

#include "LedControl.h" //  bibliotheque LEDControl

LedControl lc=LedControl(9,10,8,1);

// pin 9 de l'Arduino branchée a la pin 1 (DIN) du MAX7219
// pin 10 de l'Arduino branchée a la pin 13 (CLK) du MAX7219
// pin 8 de l'Arduino branchée a la pin 12 (LOAD) du MAX7219
// 1 pour indiquer qu'il n'y a qu'un seul MAX7219

byte grille[8]; // tableau de 8 octets contenant l'état de chaque LED

int compteur = 0; // le symbole affiché dépendra de la valeur du compteur

void setup()
{
  lc.shutdown(0,false);  // interruption du mode "économie d'énergie"
  lc.setIntensity(0,8);// réglage d'intensité (0~15)
  lc.clearDisplay(0);// on éteint toutes les LEDs
}


void loop()
{
  remplissageTableau(); // mise a jour de la variable "grille"
  displaySymbol();   // allumage des LEDs
  compteur++;       // prochain symbole
  if (compteur > 35) {  // retour a zéro si dernier symbole
    compteur = 0;
  }
  delay (1000);  // chaque symbole s'affiche pendant 1 seconde

}

void remplissageTableau()
{
  switch (compteur) {
    
  case 0: // A
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01111100;
    grille[5]=B01000100;
    grille[6]=B01000100;
    grille[7]=B01000100;
    break;
    
  case 1: // B
    grille[0]=B00000000;
    grille[1]=B01111000;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01111000;
    grille[5]=B01000100;
    grille[6]=B01000100;
    grille[7]=B01111000;
    break;
    
  case 2: // C
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B01000100;
    grille[3]=B01000000;
    grille[4]=B01000000;
    grille[5]=B01000000;
    grille[6]=B01000100;
    grille[7]=B00111000;
    break;
    
  case 3: // D
    grille[0]=B00000000;
    grille[1]=B01111000;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01000100;
    grille[5]=B01000100;
    grille[6]=B01000100;
    grille[7]=B01111000;
    break;
    
  case 4: // E
    grille[0]=B00000000;
    grille[1]=B01111100;
    grille[2]=B01000000;
    grille[3]=B01000000;
    grille[4]=B01111000;
    grille[5]=B01000000;
    grille[6]=B01000000;
    grille[7]=B01111100;
    break;
    
  case 5: // F
    grille[0]=B00000000;
    grille[1]=B01111100;
    grille[2]=B01000000;
    grille[3]=B01000000;
    grille[4]=B01111000;
    grille[5]=B01000000;
    grille[6]=B01000000;
    grille[7]=B01000000;
    break;

  case 6: // G
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B01000100;
    grille[3]=B01000000;
    grille[4]=B01000000;
    grille[5]=B01001100;
    grille[6]=B01000100;
    grille[7]=B00111000;
    break;

  case 7: // H
    grille[0]=B00000000;
    grille[1]=B01000100;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01111100;
    grille[5]=B01000100;
    grille[6]=B01000100;
    grille[7]=B01000100;
    break;

  case 8: // I
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B00010000;
    grille[3]=B00010000;
    grille[4]=B00010000;
    grille[5]=B00010000;
    grille[6]=B00010000;
    grille[7]=B00111000;
    break;

  case 9: // J
    grille[0]=B00000000;
    grille[1]=B00011100;
    grille[2]=B00001000;
    grille[3]=B00001000;
    grille[4]=B00001000;
    grille[5]=B00001000;
    grille[6]=B01001000;
    grille[7]=B00110000;
    break;

  case 10: // K
    grille[0]=B00000000;
    grille[1]=B01000100;
    grille[2]=B01001000;
    grille[3]=B01010000;
    grille[4]=B01100000;
    grille[5]=B01010000;
    grille[6]=B01001000;
    grille[7]=B01000100;
    break;

  case 11: // L
    grille[0]=B00000000;
    grille[1]=B01000000;
    grille[2]=B01000000;
    grille[3]=B01000000;
    grille[4]=B01000000;
    grille[5]=B01000000;
    grille[6]=B01000000;
    grille[7]=B01111000;
    break;

  case 12: // M
    grille[0]=B00000000;
    grille[1]=B01000100;
    grille[2]=B01101100;
    grille[3]=B01010100;
    grille[4]=B01010100;
    grille[5]=B01000100;
    grille[6]=B01000100;
    grille[7]=B01000100;
    break;

  case 13: // N
    grille[0]=B00000000;
    grille[1]=B01000100;
    grille[2]=B01000100;
    grille[3]=B01100100;
    grille[4]=B01010100;
    grille[5]=B01001100;
    grille[6]=B01000100;
    grille[7]=B01000100;
    break;

  case 14: // O
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01000100;
    grille[5]=B01000100;
    grille[6]=B01000100;
    grille[7]=B00111000;
    break;

  case 15: // P
    grille[0]=B00000000;
    grille[1]=B01111000;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01111000;
    grille[5]=B01000000;
    grille[6]=B01000000;
    grille[7]=B01000000;
    break;

  case 16: // Q
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01000100;
    grille[5]=B01010100;
    grille[6]=B01001000;
    grille[7]=B00110100;
    break;

  case 17: // R
    grille[0]=B00000000;
    grille[1]=B01111000;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01111000;
    grille[5]=B01010000;
    grille[6]=B01001000;
    grille[7]=B01000100;
    break;

  case 18: // S
    grille[0]=B00000000;
    grille[1]=B00111100;
    grille[2]=B01000000;
    grille[3]=B01000000;
    grille[4]=B00111000;
    grille[5]=B00000100;
    grille[6]=B00000100;
    grille[7]=B01111000;
    break;

  case 19: // T
    grille[0]=B00000000;
    grille[1]=B01111100;
    grille[2]=B00010000;
    grille[3]=B00010000;
    grille[4]=B00010000;
    grille[5]=B00010000;
    grille[6]=B00010000;
    grille[7]=B00010000;
    break;

  case 20: // U
    grille[0]=B00000000;
    grille[1]=B01000100;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01000100;
    grille[5]=B01000100;
    grille[6]=B01000100;
    grille[7]=B00111000;
    break;

  case 21: // V

    grille[0]=B00000000;
    grille[1]=B01000100;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01000100;
    grille[5]=B00101000;
    grille[6]=B00101000;
    grille[7]=B00010000;
    break;

  case 22: // W

    grille[0]=B00000000;
    grille[1]=B01000100;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B01010100;
    grille[5]=B01010100;
    grille[6]=B01010100;
    grille[7]=B00101000;
    break;

  case 23: // X

    grille[0]=B00000000;
    grille[1]=B01000100;
    grille[2]=B01000100;
    grille[3]=B00101000;
    grille[4]=B00010000;
    grille[5]=B00101000;
    grille[6]=B01000100;
    grille[7]=B01000100;
    break;

  case 24: // Y

    grille[0]=B00000000;
    grille[1]=B01000100;
    grille[2]=B01000100;
    grille[3]=B00101000;
    grille[4]=B00010000;
    grille[5]=B00010000;
    grille[6]=B00010000;
    grille[7]=B00010000;
    break;

  case 25: // Z
    grille[0]=B00000000;
    grille[1]=B01111100;
    grille[2]=B00000100;
    grille[3]=B00001000;
    grille[4]=B00010000;
    grille[5]=B00100000;
    grille[6]=B01000000;
    grille[7]=B01111100;
    break;

  case 26: // 1
    grille[0]=B00000000;
    grille[1]=B00010000;
    grille[2]=B00110000;
    grille[3]=B00010000;
    grille[4]=B00010000;
    grille[5]=B00010000;
    grille[6]=B00010000;
    grille[7]=B00111000;
    break;

  case 27: // 2
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B01000100;
    grille[3]=B00000100;
    grille[4]=B00001000;
    grille[5]=B00010000;
    grille[6]=B00100000;
    grille[7]=B01111100;
    break;

  case 28: // 3
    grille[0]=B00000000;
    grille[1]=B01111100;
    grille[2]=B00001000;
    grille[3]=B00010000;
    grille[4]=B00001000;
    grille[5]=B00000100;
    grille[6]=B01000100;
    grille[7]=B00111000;
    break;

  case 29: // 4
    grille[0]=B00000000;
    grille[1]=B00001000;
    grille[2]=B00011000;
    grille[3]=B00101000;
    grille[4]=B01001000;
    grille[5]=B01111100;
    grille[6]=B00001000;
    grille[7]=B00001000;
    break;

  case 30: // 5
    grille[0]=B00000000;
    grille[1]=B01111100;
    grille[2]=B01000000;
    grille[3]=B01111000;
    grille[4]=B00000100;
    grille[5]=B00000100;
    grille[6]=B01000100;
    grille[7]=B00111000;
    break;

  case 31: // 6
    grille[0]=B00000000;
    grille[1]=B00011000;
    grille[2]=B00100000;
    grille[3]=B01000000;
    grille[4]=B01111000;
    grille[5]=B01000100;
    grille[6]=B01000100;
    grille[7]=B00111000;
    break;

  case 32: // 7
    grille[0]=B00000000;
    grille[1]=B01111100;
    grille[2]=B00000100;
    grille[3]=B00001000;
    grille[4]=B00010000;
    grille[5]=B00100000;
    grille[6]=B01000000;
    grille[7]=B01000000;
    break;

  case 33: // 8
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B00111000;
    grille[5]=B01000100;
    grille[6]=B01000100;
    grille[7]=B00111000;
    break;

  case 34: // 9
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B01000100;
    grille[3]=B01000100;
    grille[4]=B00111100;
    grille[5]=B00000100;
    grille[6]=B00001000;
    grille[7]=B00110000;
    break;

  case 35: // 0
    grille[0]=B00000000;
    grille[1]=B00111000;
    grille[2]=B01000100;
    grille[3]=B01001100;
    grille[4]=B01010100;
    grille[5]=B01100100;
    grille[6]=B01000100;
    grille[7]=B00111000;
    break;
  }
}

void displaySymbol()
{
  // on allume les LEDs qui doivent l'etre

  for (int ligne=0; ligne<8; ligne++)
  {
    for (int col=0; col<8; col++)
    {
      for (byte masque = 00000001; masque>0; masque <<= 1)
        lc.setLed(0,ligne,col,(B10000000 >> col & grille[ligne]));   
    }
  }
}
