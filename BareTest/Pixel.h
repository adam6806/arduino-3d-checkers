/*
  Pixel.h - Library for altering WS2801 pixels
  Created by Adam D. Smith, July 10, 2013.
*/
#ifndef Pixel_h
#define Pixel_h

#include "Arduino.h"

class Pixel
{
  public:
    Pixel();
    void setRGB(int r, int g, int b);
    void setBrightness(int b);
    int getBrightness();
    uint32_t getColor();
    int getR();
    int getG();
    int getB();
    void turnOff();
    void turnRed();
    void turnGreen();
    void turnBlue();
    void turnYellow();
    void turnPink();
    void turnTeal();
    void turnWhite();
  private:
    int _brightness;
    int _r;
    int _g;
    int _b;
};

#endif
