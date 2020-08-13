 unsigned char i;

#define Max7219_pinCLK 10
#define Max7219_pinCS 9
#define Max7219_pinDIN 8

void setup() {
  pinMode(Max7219_pinCLK,OUTPUT);
  pinMode(Max7219_pinCS,OUTPUT);
  pinMode(Max7219_pinDIN,OUTPUT);
  delay(50);  //Initialiser
  Init_MAX7219();
}

void loop() {

  Write_Max7219(1,0x10);
  Write_Max7219(2,0x30);
  Write_Max7219(3,0x50);
  Write_Max7219(4,0x10);
  Write_Max7219(5,0x10);
  Write_Max7219(6,0x10);
  Write_Max7219(7,B10101010);
  Write_Max7219(8,B01010101);
  delay(500);
  Write_Max7219(8,B10101010);
  Write_Max7219(7,B01010101);
  delay(500);

}


void Init_MAX7219(void)
{
 Write_Max7219(0x09, 0x00);       //decoding ：BCD
 Write_Max7219(0x0a, 0x01);       //brightness
 Write_Max7219(0x0b, 0x07);       //scanlimit；8 LEDs
 Write_Max7219(0x0c, 0x01);       //power-down mode：0，normal mode：1
 Write_Max7219(0x0f, 0x00);       //test display：1；EOT，display：0
}



 
//Ecriture sur une rangee
void Write_Max7219(unsigned char address,unsigned char dat)
{
        digitalWrite(Max7219_pinCS,LOW);
        Write_Max7219_byte(address);           //address，code of LED
        Write_Max7219_byte(dat);               //data，figure on LED 
        digitalWrite(Max7219_pinCS,HIGH);
}

// Ecriture sur un 8x8
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
