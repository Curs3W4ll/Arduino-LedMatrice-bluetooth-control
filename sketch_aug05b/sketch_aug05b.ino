// Cablage du module (gnd et +V) utilise 3 pins
int Max7219_pinCLK = 10; 
int Max7219_pinCS = 9;
int Max7219_pinDIN = 8;
 
//Ecriture d'un caractere 8x8
void Write_Max7219_byte(unsigned char DATA)
{   
            unsigned char i;
       digitalWrite(Max7219_pinCS,LOW);      
       for(i=8;i>=1;i--)
          {       
             digitalWrite(Max7219_pinCLK,LOW);
             digitalWrite(Max7219_pinDIN,DATA&0x80);// Extracting a bit data
             DATA = DATA<<1;
             digitalWrite(Max7219_pinCLK,HIGH);
           }                                 
}
 
//Ecriture elementaire d une seule rangee
void Write_Max7219(unsigned char address,unsigned char dat)
{
        digitalWrite(Max7219_pinCS,LOW);
        Write_Max7219_byte(address);           //address，code of LED
        Write_Max7219_byte(dat);               //data，figure on LED
        digitalWrite(Max7219_pinCS,HIGH);
}

//Initialisation du module Max 7219
void Init_MAX7219(void)
{
 Write_Max7219(0x09, 0x00);       //decoding ：BCD
 Write_Max7219(0x0a, 0x03);       //brightness
 Write_Max7219(0x0b, 0x07);       //scanlimit；8 LEDs
 Write_Max7219(0x0c, 0x01);       //power-down mode：0，normal mode：1
 Write_Max7219(0x0f, 0x00);       //test display：1；EOT，display：0
}
 
 
//Le programme d affichage
void setup()
{
 //Pins a utiliser
  pinMode(Max7219_pinCLK,OUTPUT);
  pinMode(Max7219_pinCS,OUTPUT);
  pinMode(Max7219_pinDIN,OUTPUT);
  delay(50);  //Initialiser
  Write_Max7219(0x09, 0x00);
  Write_Max7219(0x0a, 0x03);
  Write_Max7219(0x0b, 0x07);
  Write_Max7219(0x0c, 0x01);
  Write_Max7219(0x0f, 0x00);
}
 
 
void loop()
{
   for(j=0;j<38;j++)
  {  //Faire défiler les caracteres a afficher
   for(int i=1;i<9;i++)  //Afficher un caractere à la fois
    Write_Max7219(i,disp1[j][i-1]);
   delay(500);  //Attente pour laisser le temps de lire
   
  }       
}
