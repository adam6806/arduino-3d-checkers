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
int cube[4][4][4];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  strip.begin();
  strip.show();
  setArray();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //strobe();
  //pulseLeds();
  //inOrderCycle();
  //cubeCycle();
  cubeVertPlaneShift();
  cubeHorizPlaneShift();
  
}

void cubeHorizPlaneShift() {
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      for(int k=0;k<4;k++) {
        if(cube[j][k][i]!=32) {
          changePix(cube[j][k][i], random(1,8));
          refresh();
        }
      }
    }
    delay(200);
    allOff();
  }
  allOff();
  
}

void cubeVertPlaneShift() {
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      for(int k=0;k<4;k++) {
        if(cube[i][j][k]!=32) {
          changePix(cube[i][k][j], random(1,8));
          refresh();
        }
      }
    }
    delay(200);
    allOff();
  }
  allOff();
  
}

void cubeCycle() {
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      for(int k=0;k<4;k++) {
        if(cube[k][j][i]!=32) {
          changePix(cube[k][j][i], random(1,8));
          refresh();
          delay(100);
        }
      }
    }
  }
  allOff();
}

void setArray() {
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      for(int k=0;k<4;k++) {
        cube[i][j][k] = 32;
      }
    }
  }
  cube[0][0][0] = 0;
  cube[0][2][0] = 1;
  cube[1][3][0] = 2;
  cube[1][1][0] = 3;
  cube[2][0][0] = 4;
  cube[2][2][0] = 5;
  cube[3][3][0] = 6;
  cube[3][1][0] = 7;
  cube[3][0][1] = 8;
  cube[3][2][1] = 9;
  cube[2][3][1] = 10;
  cube[2][1][1] = 11;
  cube[1][0][1] = 12;
  cube[1][2][1] = 13;
  cube[0][3][1] = 14;
  cube[0][1][1] = 15;
  cube[0][0][2] = 16;
  cube[2][0][2] = 17;
  cube[3][1][2] = 18;
  cube[1][1][2] = 19;
  cube[0][2][2] = 20;
  cube[2][2][2] = 21;
  cube[3][3][2] = 22;
  cube[1][3][2] = 23;
  cube[0][3][3] = 24;
  cube[0][1][3] = 25;
  cube[1][2][3] = 26;
  cube[1][0][3] = 27;
  cube[2][1][3] = 28;
  cube[2][3][3] = 29;
  cube[3][2][3] = 30;
  cube[3][0][3] = 31;
}

void inOrderCycle() {
  for(int i=0;i<32;i++){
    changePix(i,3);
    refresh();
    delay(500);
    allOff();
  }
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
