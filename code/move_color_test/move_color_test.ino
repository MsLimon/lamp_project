#include <Adafruit_WS2801.h>

#include "Adafruit_WS2801.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif

/****************************************************************************** 
This code is a modification of the strandtest example of the Adafruit WS2801 
library (https://github.com/adafruit/Adafruit-WS2801-Library).

Written by Marta Timon.
Feb 16, 2018.
BSD license, all text above must be included in any redistribution

*****************************************************************************/
/****************************************************************************** 
 Example sketch for driving Adafruit WS2801 pixels!


  Designed specifically to work with the Adafruit RGB Pixels!
  12mm Bullet shape ----> https://www.adafruit.com/products/322
  12mm Flat shape   ----> https://www.adafruit.com/products/738
  36mm Square shape ----> https://www.adafruit.com/products/683

  These pixels use SPI to transmit the color data, and have built in
  high speed PWM drivers for 24 bit color per pixel
  2 pins are required to interface

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution

*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
// The colors of the wires may be totally different so
// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
uint8_t dataPin  = 6;    // Yellow wire on Adafruit Pixels(2)
uint8_t clockPin = 7;    // Green wire on Adafruit Pixels(3)

//Define led matrices


const int rows = 12;
const int lrows = 6;
const int cols = 5;
int LedMatrix[rows][cols] = {
{100,100,3,2,1},
{100,4,5,6,7},
{12,11,10,9,8},
{13,14,15,16,17},
{21,20,19,18,100},
{22,23,24,100,100},
{100,100,27,28,29},
{100,33,32,31,30},
{34,35,36,37,38},
{43,42,41,40,39},
{44,45,46,47,100},
{50,49,48,100,100}
};


//Middle
int m [2] = {25,26};


// Don't forget to connect the ground wire to Arduino ground,
// and the +5V wire to a +5V supply

// Set the first variable to the NUMBER of pixels. 50 = 50 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(50, dataPin, clockPin);

void setup() {
 #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
#endif

  strip.begin();
 startColor(50);
  // Update LED contents, to start they are all in rainbow color
  strip.show();
  Serial.begin(9600);

}

void loop() {
 rainbowStripesMove(100);
 rainbowStripesMoveRight(100);
 rainbowStripesMoveDown(100);
 rainbowStripesMoveUp(100);
 
}

void rainbowStripes(){
  int i;
  int j;
  int pixelNum;
  for (i=0; i < rows; i++){
    for (j=0; j < cols; j++){
      // subtract 1 to the pixel number in the matrix (matrix indices start with zero). TODO -change matrix to fix this
      pixelNum = LedMatrix[i][j]-1;
      if (pixelNum != 99){
      strip.setPixelColor(pixelNum, Wheel( ((i * 256 / rows)) % 256) );
    }
  }
  
}
  strip.show();   // write all the pixels out
  //delay(wait);
}

void rainbowStripesMove(uint8_t wait){
  int i;
  int j;
  int k;
  int pixelNum;
  for (k=0; k < rows; k++){
  for (i=0; i < rows; i++){
    for (j=0; j < cols; j++){
      pixelNum = LedMatrix[i][j]-1;
      if (pixelNum != 99){
      strip.setPixelColor(pixelNum, Wheel( (((i+k)%rows * 256 / rows)) % 256) );
    }
  }
  
}
  strip.show();   // write all the pixels out
  delay(wait);
  }
}

void rainbowStripesMoveRight(uint8_t wait){
  int i;
  int i_prime;
  int j;
  int k;
  int pixelNum;
  for (k=0; k < rows; k++){
  for (i=0; i < rows; i++){
    for (j=0; j < cols; j++){
      pixelNum = LedMatrix[i][j]-1;
      if (pixelNum != 99){
        i_prime = i - k;
        if (i_prime < rows){
      strip.setPixelColor(pixelNum, Wheel( (((i_prime+rows) * 256 / rows)) % 256) );
     }
     else{
      strip.setPixelColor(pixelNum, Wheel( (((i_prime) * 256 / rows)) % 256) );
     }
    }
  }
  
}
  strip.show();   // write all the pixels out
  delay(wait);
  }
}

void rainbowStripesMoveDown(uint8_t wait){
  int i;
  int j_prime;
  int j;
  int k;
  int pixelNum;
  for (k=0; k < cols; k++){
  for (i=0; i < rows; i++){
    for (j=0; j < cols; j++){
      pixelNum = LedMatrix[i][j]-1;
      if (pixelNum != 99){
        j_prime = j - k;
        if (j_prime < rows){
      strip.setPixelColor(pixelNum, Wheel( (((j_prime+cols) * 256 / cols)) % 256) );
     }
     else{
      strip.setPixelColor(pixelNum, Wheel( (((j_prime) * 256 / cols)) % 256) );
     }
    }
  }
  
}
  strip.show();   // write all the pixels out
  delay(wait);
  }
}

void rainbowStripesMoveUp(uint8_t wait){
  int i;
  int j;
  int k;
  int pixelNum;
  for (k=0; k < cols; k++){
  for (i=0; i < rows; i++){
    for (j=0; j < cols; j++){
      pixelNum = LedMatrix[i][j]-1;
      if (pixelNum != 99){
      strip.setPixelColor(pixelNum, Wheel( (((j+k)%cols * 256 / cols)) % 256) );
    }
  }
  
}
  strip.show();   // write all the pixels out
  delay(wait);
  }
}


void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel (this created the movement)
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}

byte GetRed(uint32_t c)
{
  byte r;
  uint32_t red;
  red = c;
  red >>= 16;
  r = red & 0xFF;
  return r;
  }

byte GetGreen(uint32_t c)
{
  byte g;
  uint32_t green;
  green = c;
  green >>= 8;
  g = green & 0xFF;
  return g;
  }

byte GetBlue(uint32_t c)
{
  byte b;
  uint32_t blue;
  blue = c;
  b = blue & 0xFF;
  return b;
  }
  
//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


void startColor(uint8_t wait) {
  int i;
  for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 256-color wheel
      // (thats the i / strip.numPixels() part)
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels())) % 256) );
    }
       strip.show();   // write all the pixels out50
     delay(wait);
      
}

void displayColors(){
  // Some example procedures showing how to display to the pixels
  int i;
  for (i=0; i < strip.numPixels(); i++) {
    uint32_t c;
    byte r;
    byte g;
    byte b;
      c = strip.getPixelColor(i);
      Serial.print("  pixel number: ");
      Serial.println(i);
      Serial.print("  32-bit color: ");
      Serial.println(c);
      r = GetRed(c);
      Serial.print("  red color: ");
      Serial.println(r);
      g = GetGreen(c);
      Serial.print("  green color: ");
      Serial.println(g);
      b = GetBlue(c);
      Serial.print("  blue color: ");
      Serial.println(b);
      delay(1000); // repeat once per second (change as you wish!)
  }
}
