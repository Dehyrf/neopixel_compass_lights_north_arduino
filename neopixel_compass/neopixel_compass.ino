/*  
  Based on code and libraries created by helscream and Adafruit

--Edited and redistributed by Dehyrf under GNU GPL v3

*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <Wire.h>
#include "compass.h"

#define NUMPIXELS      16
#define PIXPIN         6
#define FIRSTPIX       6
#define Task_t 10          // Task Time in milli seconds

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIXPIN, NEO_GRB + NEO_KHZ800);

int dt=0;
unsigned long t;
// Main code -----------------------------------------------------------------
void setup(){


  pinMode(13, OUTPUT);

// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
/*#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
 */ // End of trinket special code
  
  // Serial.begin(9600);
  // Serial.print("Setting up I2C ........\n");
  Wire.begin();
  pixels.begin(); 
  compass_x_offset = 122.17;
  compass_y_offset = 230.08;
  compass_z_offset = 389.85;
  compass_x_gainError = 1.12;
  compass_y_gainError = 1.13;
  compass_z_gainError = 1.03;
  
  compass_init(2);
  compass_debug = 1;
  compass_offset_calibration(3);

 // pixels.setPixelColor(FIRSTPIX, pixels.Color(0,150,0)); // Moderately bright green color.
 // pixels.show(); // This sends the updated pixel color to the hardware.
 
  theaterChaseRainbow(20);  
  digitalWrite(13,HIGH);
}

// Main loop 
// Main loop -----------------------------------------------------------------
void loop(){
  
  t = millis();
 
  float load;
 
   
  
 /* compass_scaled_reading();
  
  Serial.print("x = ");
  Serial.println(compass_x_scaled);
  Serial.print("y = ");
  Serial.println(compass_y_scaled);
  Serial.print("z = ");
  Serial.println(compass_z_scaled);
  
*/
  compass_heading();
 /* Serial.print ("bearing angle = ");
  Serial.print ((int)bearing);
  Serial.println(" Degrees");
*/
//lightWay(0);

if((bearing >= 0 && bearing <= 11.25) || (bearing > 348.75 && bearing <= 360))
{
  wipe();
  lightWay(0);
}
if(bearing > 11.25 && bearing <= 33.75)
{
  wipe();
  lightWay(1);
}
if(bearing > 33.75 && bearing <= 56.25)
{
  wipe();
  lightWay(2);
}
if(bearing > 56.25 && bearing <= 78.75)
{
  wipe();
  lightWay(3);
}
if(bearing > 78.75 && bearing <= 101.25)
{
  wipe();
  lightWay(4);
}
if(bearing > 101.25 && bearing <= 123.75)
{
  wipe();
  lightWay(5);
}
if(bearing > 123.75 && bearing <= 146.25)
{
  wipe();
  lightWay(6);
}
if(bearing > 146.25 && bearing <= 168.75)
{
  wipe();
  lightWay(7);
}
if(bearing > 168.75 && bearing <= 191.25)
{
  wipe();
  lightWay(8);
}
if(bearing > 191.25 && bearing <= 213.75)
{
  wipe();
  lightWay(9);
}
if(bearing > 213.75 && bearing <= 236.25)
{
  wipe();
  lightWay(10);
}
if(bearing > 236.25 && bearing <= 258.75)
{
  wipe();
  lightWay(11);
}
if(bearing > 258.75 && bearing <= 281.25)
{
  wipe();
  lightWay(12);
}
if(bearing > 281.25 && bearing <= 303.75)
{
  wipe();
  lightWay(13);
}
if(bearing > 303.75 && bearing <= 326.25)
{
  wipe();
  lightWay(14);
}
if(bearing > 326.25 && bearing <= 348.75)
{ 
  wipe();
  lightWay(15);
}


 /* dt = millis()-t;
  load = (float)dt/(Task_t/100);
  Serial.print ("Load on processor = ");
  Serial.print(load);
  Serial.println("%");
*/
  
  delay(66 * 2);
}

void lightWay(int offset) {
  int n = FIRSTPIX + offset;
    while (n > 15) {n = n - 16;}
  int w = FIRSTPIX + 4 + offset;
    while (w > 15) {w = w - 16;}
  int s = FIRSTPIX + 8 + offset;
    while (s > 15) {s = s - 16;}
  int e = FIRSTPIX + 12 + offset;
    while (e > 15) {e = e - 16;}
 pixels.setPixelColor(n, pixels.Color(255,0,0)); // Moderately bright green color.
 pixels.setPixelColor(s, pixels.Color(0,0,255)); // Moderately bright green color.  
 pixels.setPixelColor(e, pixels.Color(255,255,255)); // Moderately bright green color. 
 pixels.setPixelColor(w, pixels.Color(255,255,255)); // Moderately bright green color.  
 pixels.show(); // This sends the updated pixel color to the hardware.
}

void wipe() {
colorWipe(pixels.Color(0, 0, 0), 50);    // Black/off
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
  }
}

void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (int i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
