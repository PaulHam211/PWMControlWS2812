//  ___    ___             ___  __      __  __  __ 
// | _ \  / __|    ___    | _ \ \ \    / / |  \/  |
// |   / | (__    |___|   |  _/  \ \/\/ /  | |\/| |
// |_|_\  \___|___   ___  |_|_   _\_/\_/   |_|  |_|
// \ \    / / / __| |_  ) ( _ ) / | |_  )          
//  \ \/\/ /  \__ \  / /  / _ \ | |  / /           
//   \_/\_/   |___/ /___| \___/ |_| /___|                                                         
//
// RC (PWM) controlled NeoPixel strip. 
// 
// Configure a pot on your RC transmitter, connect PWM signal from receiver
// to Digital IO pin 1.
// 
// Connect Neopixel strip or singular LEDs (WS2812 RGB LED) to Digital IO pin 4
// 
// Define pixel_count to amount of LEDs on strip
// 

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    4    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 24
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);


#define CH1_PIN  1        // Digital IO pin connected to the PWM signal.
double RAWPWM_CH1;
double PWM_CH1;


void setup() {
  
  //Serial.begin(9600);   // Comment out to save Flash space
  pinMode(CH1_PIN, INPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop() {

// Get PWM data & Contrain values //

  RAWPWM_CH1 = pulseIn(CH1_PIN, HIGH);
  PWM_CH1 = map(RAWPWM_CH1,898, 2178, 1000, 2000);
  
 /* -- For debugging PWM Values, Comment out for Digispark board
  Serial.print("PWM_CH1 - ");
  Serial.print(PWM_CH1);
  Serial.print(" - ");
  Serial.print("RAWPWM_CH1 - ");
  Serial.println(RAWPWM_CH1);
*/

/*---PWM Ranges ---*/
  
if (PWM_CH1 <=1100)
  {
    Nav();
  }
  
if (PWM_CH1 >=1101 && PWM_CH1 <=1200)
  {
    knightRider(1, 32, 4, 0xFF1000);
  }

if (PWM_CH1 >=1201 && PWM_CH1 <=1300)
  {
    ALLRed();
  }
  
if (PWM_CH1 >=1301 && PWM_CH1 <=1400)
  {
    ALLGreen();
  }

if (PWM_CH1 >=1401 && PWM_CH1 <=1500)
  {
    ALLBlue();
  }
  
if (PWM_CH1 >=1501 && PWM_CH1 <=1600)
  {
    ALLRed();
  }
    
if (PWM_CH1 >=1601 && PWM_CH1 <=1700)
  {
    ALLGreen();
  }  
if (PWM_CH1 >=1701 && PWM_CH1 <=1800)
  {
    ALLBlue();
  }
    
if (PWM_CH1 >=1801 && PWM_CH1 <=1900)
  {
    ALLRed();
  }
  
if (PWM_CH1 >=1901)
  {
    ALLGreen();
  }
 
  }

/////-----VOIDS-----/////

void ALLRed() {
  for(int i=0;i<PIXEL_COUNT;i++)
  {
strip.setPixelColor(i, strip.Color(150,0,0));
  }
strip.show();
  }


void ALLGreen() {
  for(int i=0;i<PIXEL_COUNT;i++)
  {
strip.setPixelColor(i, strip.Color(0,150,0));
  }
strip.show();
  }


void ALLBlue() {
  for(int i=0;i<PIXEL_COUNT;i++)
  {
strip.setPixelColor(i, strip.Color(0,0,150));
  }
strip.show();
  }


void Nav() {
  {
    for(int i=0;i<PIXEL_COUNT;i++)
  {
strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
  }

  NavRedGreen();
  delay(75);
  NavWhite();
  delay(75);
  NavRedGreen();
  delay(75);
  NavWhite();
  delay(75);
  NavRedGreen();

//HOLD NAV Lights for 1 second
  delay(1000);
}
void NavWhite() {
  strip.setPixelColor(0, 255, 255, 255);
  strip.setPixelColor(1, 255, 255, 255);
  strip.setPixelColor(PIXEL_COUNT-2, 255, 255, 255);
  strip.setPixelColor(PIXEL_COUNT-1, 255, 255, 255);
  strip.show();
  }

void NavRedGreen() {
  strip.setPixelColor(0, 0, 255, 0);
  strip.setPixelColor(1, 0, 255, 0);
  strip.setPixelColor(PIXEL_COUNT-2, 255, 0, 0);
  strip.setPixelColor(PIXEL_COUNT-1, 255, 0, 0);
  strip.show();
  }

void knightRider(uint16_t cycles, uint16_t speed, uint8_t width, uint32_t color) {
  uint32_t old_val[PIXEL_COUNT]; // up to 256 lights!
  // Larson time baby!
 clearStrip();
  for(int i = 0; i < cycles; i++){
    for (int count = 1; count<PIXEL_COUNT; count++) {
      strip.setPixelColor(count, color);
      old_val[count] = color;
      for(int x = count; x>0; x--) {
        old_val[x-1] = dimColor(old_val[x-1], width);
        strip.setPixelColor(x-1, old_val[x-1]); 
      }
      strip.show();
      delay(speed);
    }
    for (int count = PIXEL_COUNT-1; count>=0; count--) {
      strip.setPixelColor(count, color);
      old_val[count] = color;
      for(int x = count; x<=PIXEL_COUNT ;x++) {
        old_val[x-1] = dimColor(old_val[x-1], width);
        strip.setPixelColor(x+1, old_val[x+1]);
      }
      strip.show();
      delay(speed);
  }
  }
  }

void clearStrip() {
  for( int i = 0; i<PIXEL_COUNT; i++){
    strip.setPixelColor(i, 0x000000); strip.show();
  }
  }

uint32_t dimColor(uint32_t color, uint8_t width) {
   return (((color&0xFF0000)/width)&0xFF0000) + (((color&0x00FF00)/width)&0x00FF00) + (((color&0x0000FF)/width)&0x0000FF);
  }


