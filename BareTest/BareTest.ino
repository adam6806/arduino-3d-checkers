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
  
  /*
  
  for(int i=0;i<200;i++){
    strobe();
  }
  for(int j=0;j<3;j++){
    pulseLeds();
  }
  
  inOrderCycle();
  
  
  cubeCycle();
  
  
  
  for(int k=0;k<3;k++){
    cubeVertPlaneShift();
  }
  
  
  for(int l=0;l<3;l++){
    cubeHorizPlaneShift();
  }
  */
  
  snake(1000);
  
}

void snake(int num) {
  int proposedX = 0;
  int proposedY = 0;
  int proposedZ = 0;
  int currentX = 0;
  int currentY = 0;
  int currentZ = 0;
  int previousX1 = 0;
  int previousY1 = 0;
  int previousZ1 = 0;
  int previousX2 = 0;
  int previousY2 = 0;
  int previousZ2 = 0;
  int previousX3 = 0;
  int previousY3 = 0;
  int previousZ3 = 0;
  int rand = 0;
  
  for(int i = 0;i<num;i++) {
    rand = random(1,12);
    if(rand == 1) {
      proposedY++;
      proposedZ--;
    } else if(rand == 2) {
      proposedY++;
      proposedZ++;
    } else if(rand == 3) {
      proposedX--;
      proposedY++;
    } else if(rand == 4) {
      proposedX++;
      proposedY++;
    } else if(rand == 5) {
      proposedX++;
      proposedZ++;
    } else if(rand == 6) {
      proposedX--;
      proposedZ--;
    } else if(rand == 7) {
      proposedX++;
      proposedZ--;
    } else if(rand == 8) {
      proposedX--;
      proposedZ++;
    } else if(rand == 9) {
      proposedY--;
      proposedZ--;
    } else if(rand == 10) {
      proposedY--;
      proposedZ++;
    } else if(rand == 11) {
      proposedY--;
      proposedX--;
    } else {
      proposedX++;
      proposedY--;
    }
    
    String compareNew = String(String(proposedX) + String(proposedY) + String(proposedZ));
    String compare1 = String(String(previousX1) + String(previousY1) + String(previousZ1));
    String compare2 = String(String(previousX2) + String(previousY2) + String(previousZ2));
    String compare3 = String(String(previousX3) + String(previousY3) + String(previousZ3));
    
    if(proposedX<=3 && proposedX>=0 && proposedY<=3 && proposedY>=0 && proposedZ<=3 && proposedZ>=0 && compareNew!=compare1 && compareNew!=compare2 && compareNew!=compare3) {
      
      changePix(cube[previousX3][previousY3][previousZ3], 0, 25);
      
      previousX3 = previousX2;
      previousY3 = previousY2;
      previousZ3 = previousZ2;
      previousX2 = previousX1;
      previousY2 = previousY1;
      previousZ2 = previousZ1;
      previousX1 = currentX;
      previousY1 = currentY;
      previousZ1 = currentZ;   
      currentX = proposedX;
      currentY = proposedY;
      currentZ = proposedZ;   
      
      changePix(cube[currentX][currentY][currentZ], 1);
      changePix(cube[previousX1][previousY1][previousZ1], 1, 18);
      changePix(cube[previousX2][previousY2][previousZ2], 1, 11);
      changePix(cube[previousX3][previousY3][previousZ3], 1, 4);
      
      refresh();
      delay(100);
      
    } else {
      proposedX = currentX;
      proposedY = currentY;
      proposedZ = currentZ;
    }
  }
}
    

void cubeHorizPlaneShift() {
  for(int i=0;i<4;i++) {
    for(int j=0;j<4;j++) {
      for(int k=0;k<4;k++) {
        if(cube[j][i][k]!=32) {
          changePix(cube[j][i][k], random(1,8));
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
        if(cube[i][k][j]!=32) {
          changePix(cube[i][j][k], random(1,8));
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
        if(cube[k][i][j]!=32) {
          changePix(cube[k][i][j], random(1,8));
          refresh();
          delay(300);
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
        cube[i][k][j] = 32;
      }
    }
  }
  cube[0][0][0] = 0;
  cube[0][2][0] = 22;
  cube[1][3][0] = 31;
  cube[1][1][0] = 9;
  cube[2][0][0] = 4;
  cube[2][2][0] = 18;
  cube[3][3][0] = 30;
  cube[3][1][0] = 8;
  cube[3][0][1] = 7;
  cube[3][2][1] = 17;
  cube[2][3][1] = 29;
  cube[2][1][1] = 11;
  cube[1][0][1] = 3;
  cube[1][2][1] = 21;
  cube[0][3][1] = 28;
  cube[0][1][1] = 10;
  cube[0][0][2] = 1;
  cube[2][0][2] = 5;
  cube[3][1][2] = 12;
  cube[1][1][2] = 13;
  cube[0][2][2] = 23;
  cube[2][2][2] = 19;
  cube[3][3][2] = 26;
  cube[1][3][2] = 27;
  cube[0][3][3] = 24;
  cube[0][1][3] = 14;
  cube[1][2][3] = 20;
  cube[1][0][3] = 2;
  cube[2][1][3] = 15;
  cube[2][3][3] = 25;
  cube[3][2][3] = 16;
  cube[3][0][3] = 6;
  
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

void changePix(int index, int color, int brightness) //0-off 1-red 2-green 3-blue 4-yellow 5-pink 6-teal 7-white
{
  if(color==0) pixels[index].turnOff();
  if(color==1) pixels[index].turnRed();
  if(color==2) pixels[index].turnGreen();
  if(color==3) pixels[index].turnBlue();
  if(color==4) pixels[index].turnYellow();
  if(color==5) pixels[index].turnPink();
  if(color==6) pixels[index].turnTeal();
  if(color==7) pixels[index].turnWhite();
  pixels[index].setBrightness(brightness);
}
