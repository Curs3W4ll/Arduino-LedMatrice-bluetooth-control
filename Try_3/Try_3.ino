#include "LedControl.h"

LedControl lc=LedControl(2,4,3,4);

//--Constantes alignements--//
const int DROITE = 0;
const int GAUCHE = 1;
const int CENTRE = 2;

//--Constantes affichages spécials--//
const int COEUR = 0;
const int SMILEY1 = 1;
const int SMILEY2 = 2;
const int COEUR_ANIMATE = 3;
const int DAMIER = 5;
const int PLUIE = 7;

int currentTime = 0;
int previousTime = 0;
int previousScroll = 0;

char scrolling_mot[50] = "Loon_OW";

byte animate[] =
{
  B00000000,//1 -> there is an animation | 0 -> no animation
  B00000000,//Frames number of the animation
  B00000000,//Actual frame of the animation
  B00000000,//Pos de la zone d'affichage de l'animation
  B00000000//Délai entre chaque frames de l'animation (en cs)
};
byte scrolling[] =
{
  B00000000,//1 -> there is a scrolling animation | 0 -> no scrolling animation
  B00000000,//Col numbers needed
  B00000000,//Actual col number
  B00000000,//Délai entre chaque décalage de colonne (en cs)
  B00000000//free_affichages (1 à 4)
};
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
byte ascii[][8] =
{{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
   //--espace--//
},
{
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B10000000,
   B00000000,
   B10000000,
   B00000000
   //--!--//
},
{
   B00000000,
   B10100000,
   B10100000,
   B01010000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
   //--"--//
},
{
   B00000000,
   B01010000,
   B11111000,
   B01010000,
   B01010000,
   B11111000,
   B01010000,
   B00000000
   //--#--//
},
{
   B00000000,
   B00100000,
   B01111000,
   B10100000,
   B01110000,
   B00101000,
   B11110000,
   B00100000
   //--$--//
},
{
   B00000000,
   B00000000,
   B01100100,
   B01101000,
   B00010000,
   B00101100,
   B01001100,
   B00000000
   //--%--//
},
{
   B00000000,
   B00010000,
   B00101000,
   B00101000,
   B00010000,
   B00101010,
   B00100100,
   B00011010
   //--&--//
},
{
   B00000000,
   B00010000,
   B00010000,
   B00100000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
   //--'--//
},
{
   B00100000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B00100000
   //--(--//
},
{
   B01000000,
   B00100000,
   B00100000,
   B00100000,
   B00100000,
   B00100000,
   B00100000,
   B01000000
   //--)--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B01010000,
   B00100000,
   B01010000,
   B00000000,
   B00000000
   //--*--//
},
{
   B00000000,
   B00000000,
   B00100000,
   B00100000,
   B11111000,
   B00100000,
   B00100000,
   B00000000
   //--+--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00100000,
   B00100000,
   B01000000
   //--,--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B11100000,
   B00000000,
   B00000000,
   B00000000
   //-----//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00011000,
   B00011000
   //--.--//
},
{
   B00000000,
   B00000100,
   B00001000,
   B00001000,
   B00010000,
   B00010000,
   B00100000,
   B00000000
   //--/--//
},
{
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
},
{
   B00000000,
   B00000000,
   B00011000,
   B00011000,
   B00000000,
   B00011000,
   B00011000,
   B00000000
   //--:--//
},
{
   B00000000,
   B00000000,
   B00100000,
   B00000000,
   B00100000,
   B00100000,
   B01000000,
   B00000000
   //--;--//
},
{
   B00000000,
   B00000000,
   B00010000,
   B00100000,
   B01000000,
   B00100000,
   B00010000,
   B00000000
   //--<--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B01111000,
   B00000000,
   B01111000,
   B00000000,
   B00000000
   //--=--//
},
{
   B00000000,
   B00000000,
   B01000000,
   B00100000,
   B00010000,
   B00100000,
   B01000000,
   B00000000
   //-->--//
},
{
   B00000000,
   B00111000,
   B01000100,
   B00000100,
   B00001000,
   B00010000,
   B00000000,
   B00010000
   //--?--//
},
{
   B00000000,
   B00111000,
   B01000100,
   B01011100,
   B01010100,
   B01011100,
   B01000000,
   B00111100
   //--@--//
},
{
  B00000000,
   B00111000,
   B01000100,
   B01000100,
   B01000100,
   B01111100,
   B01000100,
   B01000100
   //--A--//
},
{
   B00000000,
   B01111000,
   B01000100,
   B01000100,
   B01111000,
   B01000100,
   B01000100,
   B01111000
   //--B--//
},
{
   B00000000,
   B00111000,
   B01000100,
   B01000000,
   B01000000,
   B01000000,
   B01000100,
   B00111000
   //--C--//
},
{
   B00000000,
   B01111000,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B01111000
   //--D--//
},
{
   B00000000,
   B01111100,
   B01000000,
   B01000000,
   B01111000,
   B01000000,
   B01000000,
   B01111100
   //--E--//
},
{
   B00000000,
   B01111100,
   B01000000,
   B01000000,
   B01111000,
   B01000000,
   B01000000,
   B01000000
   //--F--//
},
{
   B00000000,
   B00111000,
   B01000100,
   B01000000,
   B01000000,
   B01001100,
   B01000100,
   B00111000
   //--G--//
},
{
   B00000000,
   B01000100,
   B01000100,
   B01000100,
   B01111100,
   B01000100,
   B01000100,
   B01000100
   //--H--//
},
{
   B00000000,
   B00111000,
   B00010000,
   B00010000,
   B00010000,
   B00010000,
   B00010000,
   B00111000
   //--I--//
},
{
   B00000000,
   B00000100,
   B00000100,
   B00000100,
   B00000100,
   B01000100,
   B01000100,
   B00111000
   //--J--//
},
{
   B00000000,
   B01000100,
   B01001000,
   B01010000,
   B01100000,
   B01010000,
   B01001000,
   B01000100
   //--K--//
},
{
   B00000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01111000
   //--L--//
},
{
   B00000000,
   B01000100,
   B01101100,
   B01010100,
   B01000100,
   B01000100,
   B01000100,
   B01000100
   //--M--//
},
{
   B00000000,
   B01000100,
   B01100100,
   B01010100,
   B01010100,
   B01001100,
   B01000100,
   B01000100
   //--N--//
},
{
   B00000000,
   B00111000,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B00111000
   //--O--//
},
{
   B00000000,
   B01111000,
   B01000100,
   B01000100,
   B01000100,
   B01111000,
   B01000000,
   B01000000
   //--P--//
},
{
   B00000000,
   B00111000,
   B01000100,
   B01000100,
   B01000100,
   B01010100,
   B01001100,
   B00111100
   //--Q--//
},
{
   B00000000,
   B01111000,
   B01000100,
   B01000100,
   B01000100,
   B01111000,
   B01000100,
   B01000100
   //--R--//
},
{
   B00000000,
   B00111000,
   B01000100,
   B01000000,
   B00111000,
   B00000100,
   B01000100,
   B00111000
   //--S--//
},
{
   B00000000,
   B01111100,
   B00010000,
   B00010000,
   B00010000,
   B00010000,
   B00010000,
   B00010000
   //--T--//
},
{
   B00000000,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B00111000
   //--U--//
},
{
   B00000000,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B00101000,
   B00010000
   //--V--//
},
{
   B00000000,
   B01000100,
   B01000100,
   B01000100,
   B01000100,
   B01010100,
   B01101100,
   B01000100
   //--W--//
},
{
   B00000000,
   B01000100,
   B01000100,
   B00101000,
   B00010000,
   B00101000,
   B01000100,
   B01000100
   //--X--//
},
{
   B00000000,
   B01000100,
   B01000100,
   B01000100,
   B00101000,
   B00010000,
   B00010000,
   B00010000
   //--Y--//
},
{
   B00000000,
   B01111100,
   B00000100,
   B00001000,
   B00010000,
   B00100000,
   B01000000,
   B01111100
   //--Z--//
},
{
   B01100000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01100000
   //--[--//
},
{
   B00000000,
   B01000000,
   B00100000,
   B00100000,
   B00010000,
   B00010000,
   B00001000,
   B00000000
   //--\--//
},
{
   B01100000,
   B00100000,
   B00100000,
   B00100000,
   B00100000,
   B00100000,
   B00100000,
   B01100000
   //--]--//
},
{
   B00010000,
   B00101000,
   B01000100,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
   //--^--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00111100
   //--_--//
},
{
   B00000000,
   B00100000,
   B00100000,
   B00010000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
   //--'--//
},
{
   B0000000,
   B0000000,
   B0000000,
   B0011000,
   B0000100,
   B0011100,
   B0100100,
   B0011100
   //--a--//
},
{
   B00000000,
   B00100000,
   B00100000,
   B00100000,
   B00111000,
   B00100100,
   B00100100,
   B00111000
   //--b--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00011000,
   B00100100,
   B00100000,
   B00100100,
   B00011000
   //--c--//
},
{
   B00000000,
   B00000100,
   B00000100,
   B00000100,
   B00011100,
   B00100100,
   B00100100,
   B00011100
   //--d--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00011000,
   B00100100,
   B00111100,
   B00100000,
   B00011100
   //--e--//
},
{
   B00000000,
   B00001100,
   B00010000,
   B00010000,
   B00111100,
   B00010000,
   B00010000,
   B00010000
   //--f--//
},
{
   B00000000,
   B00000000,
   B00011100,
   B00100100,
   B00100100,
   B00011100,
   B00000100,
   B00111000
   //--g--//
},
{
   B00000000,
   B01000000,
   B01000000,
   B01000000,
   B01110000,
   B01001000,
   B01001000,
   B01001000
   //--h--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00001000,
   B00000000,
   B00001000,
   B00001000,
   B00001000
   //--i--//
},
{
   B00000000,
   B00000100,
   B00000000,
   B00000100,
   B00000100,
   B00000100,
   B00100100,
   B00011000
   //--j--//
},
{
   B00000000,
   B00100000,
   B00100100,
   B00100100,
   B00111000,
   B00100100,
   B00100100,
   B00100100
   //--k--//
},
{
   B00000000,
   B00010000,
   B00010000,
   B00010000,
   B00010000,
   B00010000,
   B00010000,
   B00010000
   //--l--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B01111000,
   B01010100,
   B01010100,
   B01010100
   //--m--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00111000,
   B00100100,
   B00100100,
   B00100100
   //--n--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00011000,
   B00100100,
   B00100100,
   B00100100,
   B00011000
   //--o--//
},
{
   B00000000,
   B00111000,
   B00100100,
   B00100100,
   B00111000,
   B00100000,
   B00100000,
   B00100000
   //--p--//
},
{
   B00000000,
   B00011100,
   B00100100,
   B00100100,
   B00011100,
   B00000100,
   B00000100,
   B00000100
   //--q--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00011000,
   B00100100,
   B00100000,
   B00100000
   //--r--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00011100,
   B00100000,
   B00011000,
   B00000100,
   B00111000
   //--s--//
},
{
   B00000000,
   B00010000,
   B00010000,
   B00111100,
   B00010000,
   B00010000,
   B00010000,
   B00001100
   //--t--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00100100,
   B00100100,
   B00100100,
   B00011100
   //--u--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00100100,
   B00100100,
   B00100100,
   B00011000
   //--v--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B01000100,
   B01000100,
   B01010100,
   B00101000
   //--w--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00100100,
   B00100100,
   B00011000,
   B00100100,
   B00100100
   //--x--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00100100,
   B00100100,
   B00011100,
   B00000100,
   B00111000
   //--y--//
},
{
   B00000000,
   B00000000,
   B00111100,
   B00000100,
   B00001000,
   B00010000,
   B00100000,
   B00111100
   //--z--//
},
{
   B00011000,
   B00100000,
   B00100000,
   B01000000,
   B00100000,
   B00100000,
   B00100000,
   B00011000
   //--{--//
},
{
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000,
   B01000000
   //--|--//
},
{
   B01100000,
   B00010000,
   B00010000,
   B00001000,
   B00010000,
   B00010000,
   B00010000,
   B01100000
   //--}--//
},
{
   B00000000,
   B00000000,
   B00000000,
   B00110010,
   B01001100,
   B00000000,
   B00000000,
   B00000000
   //--~--//
}};
byte spe_affichage_layout[][9] =
{{
   B01100110,
   B11111111,
   B11111111,
   B11111111,
   B01111110,
   B00111100,
   B00011000,
   B00000000,
   B00000000
   //--Coeur fixe--//
},
{
   B00111100,
   B01000010,
   B10100101,
   B10000001,
   B10100101,
   B10011001,
   B01000010,
   B00111100,
   B00000000
   //--Smiley 1--//
},
{
   B00000000,
   B01100110,
   B01100110,
   B00000000,
   B00000000,
   B10000001,
   B01000010,
   B00111100,
   B00000000
   //--Smiley 2--//
},
{
   B00000000,
   B01100110,
   B11111111,
   B11111111,
   B01111110,
   B00111100,
   B00011000,
   B00000000,
   B00000010//Bit pour le nombre de frames de l'animation
   //--Coeur_animate1--//
},
{
   B01100110,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B01111110,
   B00111100,
   B00011000,
   B00110010//Bit pour le délai entre chaque frame (en cs)
   //--Coeur_animate2--//
},
{
   B10101010,
   B01010101,
   B10101010,
   B01010101,
   B10101010,
   B01010101,
   B10101010,
   B01010101,
   B00000010
   //--Damier1--//
},
{
   B01010101,
   B10101010,
   B01010101,
   B10101010,
   B01010101,
   B10101010,
   B01010101,
   B10101010,
   B00011110
   //--Damier2--//
},
{
   B01010001,
   B01000000,
   B00100000,
   B00100100,
   B00100100,
   B00000100,
   B00010001,
   B01010001,
   B00001000
   //--Pluie1--//
},
{
   B01010001,
   B01010001,
   B01000000,
   B00100000,
   B00100100,
   B00100100,
   B00000100,
   B00010001,
   B00000101
   //--Pluie2--//
},
{
   B00010001,
   B01010001,
   B01010001,
   B01000000,
   B00100000,
   B00100100,
   B00100100,
   B00000100,
   B00000000
   //--Pluie3--//
},
{
   B00000100,
   B00010001,
   B01010001,
   B01010001,
   B01000000,
   B00100000,
   B00100100,
   B00100100,
   B00000000
   //--Pluie4--//
},
{
   B00100100,
   B00000100,
   B00010001,
   B01010001,
   B01010001,
   B01000000,
   B00100000,
   B00100100,
   B00100000
   //--Pluie5--//
},
{
   B00100100,
   B00100100,
   B00000100,
   B00010001,
   B01010001,
   B01010001,
   B01000000,
   B00100000,
   B00100000
   //--Pluie6--//
},
{
   B00100000,
   B00100100,
   B00100100,
   B00000100,
   B00010001,
   B01010001,
   B01010001,
   B01000000,
   B00000000
   //--Pluie7--//
},
{
   B01000000,
   B00100000,
   B00100100,
   B00100100,
   B00000100,
   B00010001,
   B01010001,
   B01010001,
   B00000000
   //--Pluie8--//
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
  //--Most left--//
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
  //--Midle left--//
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
  //--Midle right--//
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
  //--Most right--//
}};
byte animations[][9] =
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

void setup()
{
  Serial.begin(9600);
  Serial.println("New-------");
  Init_affichages(4,1);
  charge_affichage(4,"Loon_OW",CENTRE);
  //charge_affichage_special(PLUIE,3);
  affiche();
}

void loop()
{
  if (animate[0]==1) {
    affiche_animation();
  }
  if (scrolling[0]==1) {
    affiche_scrolling();
  }
}

void Init_affichages(int affichages_number, int intesity) {
  for (int i = 0; i < affichages_number; i++) {
    lc.shutdown(i,false);  // Wake up displays
    lc.setIntensity(i,intesity);  // Set intensity levels
    lc.clearDisplay(i);  // Clear Displays
  }
}

void affiche() {
  int aff = 3;
  for (int i=0;i<4;i++) {
    for (int y=0;y<8;y++) {
      lc.setRow(i,y,affichage[aff][y]);
    }
    aff--;
  }
}

void affiche_scrolling() {
  currentTime = millis();
  if (currentTime-previousScroll > scrolling[3]) {
    clear_affichage(scrolling[4]);
    int free_led = scrolling[4] * 8;
    int writen_col = scrolling[2];
    writen_col -= scrolling[1];
    int free_affichage = scrolling[4]-1;
    while (writen_col>7) {
      writen_col -= 8;
      free_affichage -= 1;
    }
    Serial.println(writen_col);
    int cara_number = strlen(scrolling_mot);
    for (int cara=cara_number-1;cara>=0;cara--) {
      int ascii_code = ((int)scrolling_mot[cara])-32;
      if (cara!=cara_number-1) {
        for (int ligne=0;ligne<8;ligne++) {
          if (writen_col > 0) {
            Serial.println(writen_col);
            bitWrite(affichage[free_affichage][ligne],writen_col,0);
          }
        }
        writen_col += 1;
        if (writen_col==8) {
          writen_col = 0;
          if (free_affichage==0) {
            cara = -1;
          } else {
            free_affichage -= 1;
          }
        }
      }
      if (cara>=0) {
        if (ascii_code == 0) {
          for (int ligne=0;ligne<8;ligne++) {
            if (writen_col >= 0) {
              bitWrite(affichage[free_affichage][ligne],writen_col,0);
            }
          }
          writen_col += 1;
          if (writen_col==8) {
            writen_col = 0;
            if (free_affichage==0) {
              cara = -1;
            } else {
              free_affichage -= 1;
            }
          }
        }
        for (int col=0;col<8;col++) {
          byte tempbyte = B00000000;
          for (int ligne=0;ligne<8;ligne++) {
            if (writen_col >= 0) {
              bitWrite(tempbyte,ligne,bitRead(ascii[ascii_code][ligne],col));
            }
          }
          if (tempbyte!=0) {
            for (int ligne=0;ligne<8;ligne++) {
              if (writen_col >= 0) {
                bitWrite(affichage[free_affichage][ligne],writen_col,bitRead(tempbyte,ligne));
              }
            }
            writen_col += 1;
            if (writen_col==8) {
              writen_col = 0;
              if (free_affichage==0) {
                col = 8;
                cara = -1;
              } else {
                free_affichage -= 1;
              }
            }
          }
        }
      }
    }
    affiche();
    if (scrolling[2]==scrolling[1]+free_led) {
      scrolling[2] = 0;
    } else {
      scrolling[2]+=1;
    }
    previousScroll = currentTime;
  }
}

void affiche_animation() {
  currentTime = millis();
  if (currentTime-previousTime > animate[4]*10) {
    clear_one_affichage(3);
    for (int ligne=0;ligne<8;ligne++) {
      affichage[3][ligne] = animations[animate[2]][ligne];
    }
    if (animate[2]==animate[1]-1) {
      animate[2] = 0;
    } else {
      animate[2]+=1;
    }
    previousTime = currentTime;
    affiche();
  }
}

void clear_affichage(int affichage_number) {
  //affichage_number : number of affichage to clear (most left starting)
  for (int aff=0;aff<affichage_number;aff++) {
    for (int ligne=0;ligne<8;ligne++) {
      for (int biti=0;biti<8;biti++) {
        bitWrite(affichage[aff][ligne],biti,0);
      }
    }
  }
}

void clear_one_affichage(int aff_number) {
  //aff_number : zone d'affichage à clear (0 à 3), 0 -> plus à gauche
  for (int ligne=0;ligne<8;ligne++) {
    for (int biti=0;biti<8;biti++) {
      bitWrite(affichage[aff_number][ligne],biti,0);
    }
  }
}

int get_led_number(char mot[], int cara_number, int free_affichage) {
  int led_number = 0;
  for (int cara=cara_number-1;cara>=0;cara--) {
    int ascii_code = ((int)mot[cara])-32;
    if (cara!=cara_number-1) {
      led_number+=1;
    }
    if (ascii_code==0) {
      led_number+=1;
    }
    for (int col=0;col<8;col++) {
      byte tempbyte = B00000000;
      for (int ligne=0;ligne<8;ligne++) {
        bitWrite(tempbyte,ligne,bitRead(ascii[ascii_code][ligne],col));
      }
      if (tempbyte!=0) {
        led_number+=1;
      }
    }
  }
  return(led_number);
}

void charge_affichage(int free_affichage, char mot[], int align) {
  //free_affichage : Nombre de zone d'affichage à utiliser pour le texte (0 à 4);
  //mot[] : mot à afficher
  //align[] : alignement, trois valeurs possibles : 'DROITE','GAUCHE' et 'CENTRE'
  if (free_affichage==4) {
    animate[0] = 0;
  }
  clear_affichage(4);
  int writen_col = 0;
  int free_led = free_affichage * 8;
  int cara_number = strlen(mot);
  int used_led = get_led_number(mot,cara_number,free_affichage);
  if (used_led > free_led) {
    scrolling[0] = 1;
    scrolling[1] = used_led;
    scrolling[2] = 0;
    scrolling[3] = 200;
    scrolling[4] = free_affichage;
    strncpy(scrolling_mot,mot,cara_number);
    affiche_scrolling();
  } else {
    free_affichage -= 1;
    int unused_led = free_led - used_led;
    if (free_led-used_led > 0) {
      switch(align) {
        case DROITE:
          writen_col = 0;
          break;
        case GAUCHE:
          writen_col = unused_led;
          break;
        case CENTRE:
          writen_col = unused_led/2;
          break;
        default:
          writen_col = 0;
          break;
      }
    }
    for (int cara=cara_number-1;cara>=0;cara--) {
      int ascii_code = ((int)mot[cara])-32;
      if (cara!=cara_number-1) {
        for (int ligne=0;ligne<8;ligne++) {
            bitWrite(affichage[free_affichage][ligne],writen_col,0);
        }
        writen_col += 1;
        if (writen_col==8) {
          writen_col = 0;
          if (free_affichage==0) {
            cara = -1;
          } else {
            free_affichage -= 1;
          }
        }
      }
      if (cara>=0) {
        if (ascii_code == 0) {
          for (int ligne=0;ligne<8;ligne++) {
              bitWrite(affichage[free_affichage][ligne],writen_col,0);
          }
          writen_col += 1;
          if (writen_col==8) {
            writen_col = 0;
            if (free_affichage==0) {
              cara = -1;
            } else {
              free_affichage -= 1;
            }
          }
        }
        for (int col=0;col<8;col++) {
          byte tempbyte = B00000000;
          for (int ligne=0;ligne<8;ligne++) {
            bitWrite(tempbyte,ligne,bitRead(ascii[ascii_code][ligne],col));
          }
          if (tempbyte!=0) {
            for (int ligne=0;ligne<8;ligne++) {
              bitWrite(affichage[free_affichage][ligne],writen_col,bitRead(tempbyte,ligne));
            }
            writen_col += 1;
            if (writen_col==8) {
              writen_col = 0;
              if (free_affichage==0) {
                col = 8;
                cara = -1;
              } else {
                free_affichage -= 1;
              }
            }
          }
        }
      }
    }
  }
}

void charge_affichage_special(int spe_aff_number, int pos_affichage) {
  //spe_aff_number : Affichage spécial à afficher (COEUR,SMILEY1,SMILEY2,COEUR_ANIMATE,DAMIER,PLUIE)
  //pos_affichage : zone d'éclairage à utilisé (0 à 3) 0-> plus à gauche
  clear_one_affichage(3);
  if (spe_aff_number<3) {
    animate[0] = 0;
    for (int ligne=0;ligne<8;ligne++) {
      affichage[3][ligne] = spe_affichage_layout[spe_aff_number][ligne];
    }
  } else {
    int frames_number = spe_affichage_layout[spe_aff_number][8];
    animate[4] = spe_affichage_layout[spe_aff_number+1][8];
    for (int i=0;i<frames_number;i++) {
      for (int ligne=0;ligne<8;ligne++) {
        animations[i][ligne] = spe_affichage_layout[spe_aff_number][ligne];
      }
      spe_aff_number+=1;
    }
    animate[0] = 1;
    animate[1] = frames_number;
    animate[2] = 0;
    animate[3] = pos_affichage;
  }
}
