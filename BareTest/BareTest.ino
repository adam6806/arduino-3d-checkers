#include "Pixel.h"
#include "WS2801.h"

Pixel pixels[] = { Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel(), 
    Pixel() };
    
uint8_t dataPin = 2;    // Green wire
uint8_t clockPin = 3;    // Blue wire
uint16_t ledNum = 40;
WS2801 strip = WS2801(ledNum, dataPin, clockPin);
int randomIndex;
int randomColor;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  strip.begin();
  strip.show();

}

void loop() {
  // put your main code here, to run repeatedly:
  
  strobe();
  //pulseLeds();
  
  
}

void strobe() {
  randomIndex = random(ledNum);
  randomColor = random(1,8);
  changePix(randomIndex, randomColor);
  refresh();
  delay(15);
  allOff();
}

void pulseLeds() {
  randomIndex = random(ledNum);
  randomColor = random(1,8);
  for(int i=0;i<ledNum;i++)
  {
    changePix(i, randomColor);
  }
  refresh();
  
  delay(100);
  int ledsPulse[12] = {random(32),random(32),random(32),random(32),random(32),random(32),random(32),random(32), 32, 32, 32, 32};
  for(int j=0;j<5;j++)
  {
    pulse(ledsPulse);
  }
}

void allOff()
{
  for(int i=0;i<ledNum;i++)
  {
    changePix(i, 0);
  }
  refresh();
}

void pulse(int num[])
{
  #define numArray (sizeof(num)/sizeof(int)) //array size  
  int x = pixels[num[0]].getBrightness();
  int y = x;
  int sizeArray = 12;
  Serial.println(sizeArray);
  
  for(int j=1;j<x;j++)
  {
    for(int i=0;i<sizeArray;i++)
    {
      pixels[num[i]].setBrightness(y-1);
    }
    refresh();
    y--;
    delay(5);
  }
  
  for(int k=0;k<x;k++)
  {
    for(int p=0;p<sizeArray;p++)
    {
      pixels[num[p]].setBrightness(y+1);
    }
    refresh();
    y++;
    delay(5);
  }
  
}

void refresh()
{
  for(int i=0;i<40;i++)
  {
    strip.setPixelColor(i,pixels[i].getColor());
  }
  strip.show();
  
}

void changePix(int index, int color) //0-off 1-red 2-green 3-blue 4-yellow 5-pink 6-teal 7-white
{
  if(color==0) pixels[index].turnOff();
  if(color==1) pixels[index].turnRed();
  if(color==2) pixels[index].turnGreen();
  if(color==3) pixels[index].turnBlue();
  if(color==4) pixels[index].turnYellow();
  if(color==5) pixels[index].turnPink();
  if(color==6) pixels[index].turnTeal();
  if(color==7) pixels[index].turnWhite();
}
