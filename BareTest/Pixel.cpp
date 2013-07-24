#include "Arduino.h"
#include "Pixel.h"

Pixel::Pixel() 
{
  _r = 0;
  _g = 0;
  _b = 0;
  _brightness = 25;
}

void Pixel::setRGB(int r, int g, int b) 
{
  
  _r = r;
  _g = g;
  _b = b; 
}

void Pixel::setBrightness(int b)
{
  _brightness = b;
  if(_r!=0)_r=b;
  if(_g!=0)_g=b;
  if(_b!=0)_b=b;
}

int Pixel::getBrightness()
{
  return _brightness;
}

int Pixel::getR() 
{
  return _r; 
}

int Pixel::getG() 
{
  return _g; 
}

int Pixel::getB() 
{
  return _b; 
}

// Create a 24 bit color value from R,G,B
uint32_t Pixel::getColor()
{
  byte r = _r; 
  byte g = _g; 
  byte b = _b;
  
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

void Pixel::turnOff()
{
  _r = 0;
  _g = 0;
  _b = 0;
}

void Pixel::turnRed()
{
  _r = _brightness;
  _g = 0;
  _b = 0;
}

void Pixel::turnGreen()
{
  _r = 0;
  _g = _brightness;
  _b = 0;
}

void Pixel::turnBlue()
{
  _r = 0;
  _g = 0;
  _b = _brightness;
}

void Pixel::turnYellow()
{
  _r = _brightness;
  _g = _brightness;
  _b = 0;
}

void Pixel::turnPink()
{
  _r = _brightness;
  _g = 0;
  _b = _brightness;
}

void Pixel::turnTeal()
{
  _r = 0;
  _g = _brightness;
  _b = _brightness;
}

void Pixel::turnWhite()
{
  _r = _brightness;
  _g = _brightness;
  _b = _brightness;
}
